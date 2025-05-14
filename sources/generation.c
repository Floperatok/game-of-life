
#include "game_of_life.h"

chunk_t *get_neighbor_chunk(chunk_t *neighbor_chunks[], int posx, int posy) {
	if (posy < 0) {
		if (posx < 0) {
			return (neighbor_chunks[0]);
		} else if (posx >= CHUNK_SIZE) {
			return (neighbor_chunks[2]);
		} else {
			return (neighbor_chunks[1]);
		}
	} else if (posy >= CHUNK_SIZE) {
		if (posx < 0) {
			return (neighbor_chunks[6]);
		} else if (posx >= CHUNK_SIZE) {
			return (neighbor_chunks[8]);
		} else {
			return (neighbor_chunks[7]);
		}
	} else {
		if (posx < 0) {
			return (neighbor_chunks[3]);
		} else if (posx >= CHUNK_SIZE) {
			return (neighbor_chunks[5]);
		} else {
			return (neighbor_chunks[4]);
		}
	}
}

int count_neighbor(chunk_t *neighbor_chunks[], int cellx, int celly) {
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
			chunk_t *chunk = get_neighbor_chunk(neighbor_chunks, posx, posy);
			if (!chunk) {
				continue;
			}
			neighbor_count += get_cell(chunk->backup, \
				(posx%CHUNK_SIZE + CHUNK_SIZE) % CHUNK_SIZE, \
				(posy%CHUNK_SIZE + CHUNK_SIZE) % CHUNK_SIZE);
		}
	}
	return (neighbor_count);
}

void chunk_generation(chunk_t *neighbor_chunks[], chunk_t *hash_table[], int cellx, int celly) {
	chunk_t *current_chunk = neighbor_chunks[4];
	if (celly == 0 && !neighbor_chunks[1]) {
		neighbor_chunks[1] = new_chunk(hash_table, current_chunk->x, current_chunk->y - 1);
	} else if (celly == CHUNK_SIZE - 1 && !neighbor_chunks[7]) {
		neighbor_chunks[7] = new_chunk(hash_table, current_chunk->x, current_chunk->y + 1);
	}
	if (cellx == 0 && !neighbor_chunks[3]) {
		neighbor_chunks[3] = new_chunk(hash_table, current_chunk->x - 1, current_chunk->y);
	} else if (cellx == CHUNK_SIZE - 1 && !neighbor_chunks[5]) {
		neighbor_chunks[5] = new_chunk(hash_table, current_chunk->x + 1, current_chunk->y);
	}
}

void chunk_next_generation(chunk_t *hash_table[], chunk_t *chunk) {
	
	chunk_t *neighbor_chunks[9];
	neighbor_chunks[0] = get_chunk(hash_table, chunk->x - 1, chunk->y - 1);
	neighbor_chunks[1] = get_chunk(hash_table, chunk->x    , chunk->y - 1);
	neighbor_chunks[2] = get_chunk(hash_table, chunk->x + 1, chunk->y - 1);
	neighbor_chunks[3] = get_chunk(hash_table, chunk->x - 1, chunk->y    );
	neighbor_chunks[4] = chunk;
	neighbor_chunks[5] = get_chunk(hash_table, chunk->x + 1, chunk->y    );
	neighbor_chunks[6] = get_chunk(hash_table, chunk->x - 1, chunk->y + 1);
	neighbor_chunks[7] = get_chunk(hash_table, chunk->x    , chunk->y + 1);
	neighbor_chunks[8] = get_chunk(hash_table, chunk->x + 1, chunk->y + 1);

	int celly = -1;
	while (++celly < CHUNK_SIZE) {
		int cellx = -1;
		while (++cellx < CHUNK_SIZE) {
			int neighbor_count = count_neighbor(neighbor_chunks, cellx, celly);


			if (get_cell(chunk->backup, cellx, celly)) {
				chunk_generation(neighbor_chunks, hash_table, cellx, celly);
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
