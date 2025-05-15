
#include "game_of_life.h"

void new_cell(unsigned char *data, int x, int y) {
	int bit_index = y * CHUNK_SIZE + x;
    data[bit_index / 8] |= (1 << (bit_index % 8));
}

void kill_cell(unsigned char *data, int x, int y) {
	int bit_index = y * CHUNK_SIZE + x;
	data[bit_index / 8] &= ~(1 << (bit_index % 8));
}

int get_cell(const unsigned char *data, int x, int y) {
	int bit_index = y * CHUNK_SIZE + x;
    return (data[bit_index / 8] >> (bit_index % 8)) & 1;
}

void mouse_cell_edit(data_t *data, int mouse_posx, int mouse_posy, char draging) {
	int chunk_size = data->cam->cell_size * CHUNK_SIZE;
	int posx_chunk = (-data->cam->x + mouse_posx) / chunk_size;
	int posy_chunk = (-data->cam->y + mouse_posy) / chunk_size;
	chunk_t *chunk = get_chunk(data->chunks, posx_chunk, posy_chunk);
	if (!chunk) {
		return ;
	}
	int posx_cell = (-data->cam->x + mouse_posx) / data->cam->cell_size % CHUNK_SIZE;
	int posy_cell = (-data->cam->y + mouse_posy) / data->cam->cell_size % CHUNK_SIZE;
	if (!draging) {
		data->inputs->creating_cells = !get_cell(chunk->cells, posx_cell, posy_cell);
	}
	if (data->inputs->creating_cells) {
		new_cell(chunk->cells, posx_cell, posy_cell);
	} else {
		kill_cell(chunk->cells, posx_cell, posy_cell);
	}
}
