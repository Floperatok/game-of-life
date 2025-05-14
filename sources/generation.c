
#include "game_of_life.h"

void next_generation(data_t *data) {
	chunk_t *chunk = get_chunk(data->chunks, 0, 0);
	memcpy(chunk->tmp, chunk->cells, sizeof(chunk->cells)); // copies chunks into temporary memory
	memset(chunk->cells, 0, sizeof(chunk->cells)); // clear chunk
	// print_chunk(chunk->tmp);

	int celly = -1;
	while (++celly < CHUNK_SIZE) {
		int cellx = -1;
		while (++cellx < CHUNK_SIZE) {
			int neighbor_count = 0;
			int neighbory = -2;
			while (++neighbory < 2 && neighbor_count < 4) {
				int posy = celly + neighbory;
				// overflow
				if (posy < 0 || posy >= CHUNK_SIZE) {
					continue ;
				}
				int neighborx = -2;
				while (++neighborx < 2 && neighbor_count < 4) {
					int posx = cellx + neighborx;
					// overflow
					if (posx < 0 || posx >= CHUNK_SIZE) {
						continue ;
					}
					// the cell itself
					if (posx == cellx && posy == celly) {
						continue ;
					}
					if (get_cell(chunk->tmp, posx, posy)) {
						neighbor_count++;
					}
				}
			}
			if (get_cell(chunk->tmp, cellx, celly)) {
				if (neighbor_count == 2 || neighbor_count == 3) {
					new_cell(chunk->cells, cellx, celly);
				}
			} else if (neighbor_count == 3) {
				new_cell(chunk->cells, cellx, celly);
			}
		}
	}
}
