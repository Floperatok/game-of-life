
#include "game_of_life.h"

int check_neighbor(chunk_t *chunk, chunk_t *neighbor_chunks[], int posx, int posy) {
	if (posy < 0) {
		if (posx < 0) {
			return (neighbor_chunks[0] && get_cell(neighbor_chunks[0]->backup, CHUNK_SIZE-1, CHUNK_SIZE-1));
		} else if (posx >= CHUNK_SIZE) {
			return (neighbor_chunks[2] && get_cell(neighbor_chunks[2]->backup, 0, CHUNK_SIZE-1));
		} else {
			return (neighbor_chunks[1] && get_cell(neighbor_chunks[1]->backup, posx, CHUNK_SIZE-1));
		}
	} else if (posy >= CHUNK_SIZE) {
		if (posx < 0) {
			return (neighbor_chunks[5] && get_cell(neighbor_chunks[5]->backup, CHUNK_SIZE-1, 0));
		} else if (posx >= CHUNK_SIZE) {
			return (neighbor_chunks[7] && get_cell(neighbor_chunks[7]->backup, 0, 0));
		} else {
			return (neighbor_chunks[6] && get_cell(neighbor_chunks[6]->backup, posx, 0));
		}
	} else {
		if (posx < 0) {
			return (neighbor_chunks[3] && get_cell(neighbor_chunks[3]->backup, CHUNK_SIZE-1, posy));
		} else if (posx >= CHUNK_SIZE) {
			return (neighbor_chunks[4] && get_cell(neighbor_chunks[4]->backup, 0, posy));
		} else {
			return (get_cell(chunk->backup, posx, posy));
		}
	}
	return (0);
}

void chunk_next_generation(chunk_t *hash_table[], chunk_t *chunk) {
	
	chunk_t *neighbor_chunks[8];
	neighbor_chunks[0] = get_chunk(hash_table, chunk->x - 1, chunk->y - 1);
	neighbor_chunks[1] = get_chunk(hash_table, chunk->x    , chunk->y - 1);
	neighbor_chunks[2] = get_chunk(hash_table, chunk->x + 1, chunk->y - 1);
	neighbor_chunks[3] = get_chunk(hash_table, chunk->x - 1, chunk->y    );
	neighbor_chunks[4] = get_chunk(hash_table, chunk->x + 1, chunk->y    );
	neighbor_chunks[5] = get_chunk(hash_table, chunk->x - 1, chunk->y + 1);
	neighbor_chunks[6] = get_chunk(hash_table, chunk->x    , chunk->y + 1);
	neighbor_chunks[7] = get_chunk(hash_table, chunk->x + 1, chunk->y + 1);

	int celly = -1;
	while (++celly < CHUNK_SIZE) {
		int cellx = -1;
		while (++cellx < CHUNK_SIZE) {
			int neighbor_count = 0;
			int offset_y = -2;
			while (++offset_y < 2 && neighbor_count < 4) {
				int posy = celly + offset_y;
				int offset_x = -2;
				while (++offset_x < 2 && neighbor_count < 4) {
					if (!offset_x && !offset_y) {
						continue ;
					}
					int posx = cellx + offset_x;
					neighbor_count += check_neighbor(chunk, neighbor_chunks, posx, posy);
				}
			}
			if (get_cell(chunk->backup, cellx, celly)) {
				if (neighbor_count == 2 || neighbor_count == 3) {
					new_cell(chunk->cells, cellx, celly);
				}
			} else if (neighbor_count == 3) {
				new_cell(chunk->cells, cellx, celly);
			}
		}
	}
}

void backup_chunks(chunk_t *hash_table[], chunk_t *chunk) {
	if (!chunk || chunk->is_backup) {
		return ;
	}
	memcpy(chunk->backup, chunk->cells, sizeof(chunk->cells)); // copies chunks into temporary memory
	memset(chunk->cells, 0, sizeof(chunk->cells)); // clear chunk
	chunk->is_backup = 1;
	backup_chunks(hash_table, get_chunk(hash_table, chunk->x + 1, chunk->y));
	backup_chunks(hash_table, get_chunk(hash_table, chunk->x - 1, chunk->y));
	backup_chunks(hash_table, get_chunk(hash_table, chunk->x, chunk->y + 1));
	backup_chunks(hash_table, get_chunk(hash_table, chunk->x, chunk->y - 1));
}

void compute_next_generation(chunk_t *hash_table[], chunk_t *chunk) {
	if (!chunk || !chunk->is_backup) {
		return ;
	}

	chunk_next_generation(hash_table, chunk);
	chunk->is_backup = 0;
	
	compute_next_generation(hash_table, get_chunk(hash_table, chunk->x + 1, chunk->y));
	compute_next_generation(hash_table, get_chunk(hash_table, chunk->x - 1, chunk->y));
	compute_next_generation(hash_table, get_chunk(hash_table, chunk->x, chunk->y + 1));
	compute_next_generation(hash_table, get_chunk(hash_table, chunk->x, chunk->y - 1));
}


void next_generation(chunk_t *chunks[]) 
{
	backup_chunks(chunks, get_chunk(chunks, 0, 0));
	compute_next_generation(chunks, get_chunk(chunks, 0, 0));
}
