
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
