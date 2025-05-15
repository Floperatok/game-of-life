
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
	int real_mouse_posx = -data->cam->x + mouse_posx;
	int real_mouse_posy = -data->cam->y + mouse_posy;
	int chunk_posx = real_mouse_posx / chunk_size;
	int chunk_posy = real_mouse_posy / chunk_size;
	if (real_mouse_posx < 0) {
		chunk_posx--;
	}
	if (real_mouse_posy < 0) {
		chunk_posy--;
	}
	chunk_t *chunk = get_chunk(data->chunks, chunk_posx, chunk_posy);
	if (!chunk) {
		return ;
	}
	int posx_cell = (real_mouse_posx - chunk_posx * CHUNK_SIZE * data->cam->cell_size) / data->cam->cell_size % CHUNK_SIZE;
	int posy_cell = (real_mouse_posy - chunk_posy * CHUNK_SIZE * data->cam->cell_size) / data->cam->cell_size % CHUNK_SIZE;
	if (!draging) {
		data->inputs->creating_cells = !get_cell(chunk->cells, posx_cell, posy_cell);
	}
	if (data->inputs->creating_cells) {
		new_cell(chunk->cells, posx_cell, posy_cell);
	} else {
		kill_cell(chunk->cells, posx_cell, posy_cell);
	}
}
