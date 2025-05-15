
#include "game_of_life.h"

void destroy_chunks(chunk_t *hash_table[]) {
	int i = -1;
	while (++i < HASH_TABLE_SIZE) {
		chunk_t *chunk = hash_table[i];
		while (chunk) {
			chunk_t *next = chunk->next;
			free(chunk);
			chunk = next;
		}
	}
}

unsigned int hash_chunk(int x, int y) {
	return abs(x + y * 73856093) % HASH_TABLE_SIZE;
}

chunk_t *new_chunk(chunk_t *hash_table[], int x, int y) {
	unsigned int index = hash_chunk(x, y);
	chunk_t *chunk = malloc(sizeof(chunk_t));
	if (!chunk) {
		return (NULL);
	}
	chunk->x = x;
	chunk->y = y;
	memset(chunk->cells, 0, sizeof(chunk->cells));
	memset(chunk->backup, 0, sizeof(chunk->backup));
	chunk->next = hash_table[index];
	hash_table[index] = chunk;
	printf("NEW CHUNK: %d,%d\n", x, y);
	return (chunk);
}

chunk_t	*get_chunk(chunk_t *hash_table[], int x, int y) {
	unsigned int index = hash_chunk(x, y);
	chunk_t	*current = hash_table[index];
	while (current) {
		if (current->x == x && current->y == y) {
			return (current);
		}
		current = current->next;
	}
	return (NULL);
}

// debug
void print_chunk(const unsigned char *cells) {
	printf("\nCHUNK:\n");
	int y = -1;
	while (++y < CHUNK_SIZE) {
		int x = -1;
		while (++x < CHUNK_SIZE) {
			if (get_cell(cells, x, y)) {
				printf("# ");
			} else {
				printf(". ");
			}
		}
		printf("\n");
	}
}
