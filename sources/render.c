
#include "game_of_life.h"

void	putpixel(mlx_t *mlx, int x, int y, int color)
{
	if (x < 0 || x > WIN_W || y < 0 || y > WIN_H) {
		return ;
	}
	char *dst = (char *)mlx->addr + (y * mlx->line_length + x * (mlx->bpp / 8));
	*(unsigned int *)dst = color;
}

void fill_screen(mlx_t *mlx, int color) {
	int y = -1;
	while (++y < WIN_H) {
		int x = -1;
		while (++x < WIN_W) {
			putpixel(mlx, x, y, color);
		}
	}
}

void display_cell(mlx_t *mlx, int posx, int posy, int size) {
	int y = -1;
	while (++y < size) {
		int x = -1;
		while (++x < size) {
			putpixel(mlx, x + posx, y + posy, CELL_COLOR);
		}
	}
}

#define CELL_SIZE 5
void display_chunk(mlx_t *mlx, chunk_t *chunk) {
	if (!chunk || !mlx) {
		return ;
	}
	int chunk_posx = chunk->x * CHUNK_SIZE * CELL_SIZE;
	int chunk_posy = chunk->y * CHUNK_SIZE * CELL_SIZE;
	int y = -1;
	while (++y < CHUNK_SIZE) {
		int x = -1;
		while (++x < CHUNK_SIZE) {
			if (get_cell(chunk->cells, x, y)) {

				int size = CELL_SIZE;
				display_cell(mlx, \
					chunk_posx + x * CELL_SIZE, \
					chunk_posy + y * CELL_SIZE, \
					size);
			}
			if (x == 0 || x == CHUNK_SIZE-1 || y == 0 || y == CHUNK_SIZE-1)
				putpixel(mlx, chunk_posx+x*CELL_SIZE, chunk_posy+y*CELL_SIZE, 0xffffff);
		}
	}
}

// void display_all_chunks() {
// 	(void)
// }

void render(data_t *data) {
	fill_screen(data->mlx, BACKGROUND_COLOR);
	display_chunk(data->mlx, get_chunk(data->chunks, 0, 0));
	display_chunk(data->mlx, get_chunk(data->chunks, 1, 1));
}
