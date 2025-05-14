
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
void display_chunk_border(mlx_t *mlx, chunk_t *chunk) {
	int chunk_posx = chunk->x * CHUNK_SIZE * CELL_SIZE;
	int chunk_posy = chunk->y * CHUNK_SIZE * CELL_SIZE;
	int chunk_pixel_size = CHUNK_SIZE * CELL_SIZE;
	int i = -1;
	while (++i < CHUNK_SIZE) {
		int posx = i * CELL_SIZE + chunk_posx;
		int posy = i * CELL_SIZE + chunk_posy;
		putpixel(mlx, posx, 0, 0xffffff);
		putpixel(mlx, posx, chunk_pixel_size + chunk_posy, 0xffffff);
		putpixel(mlx, 0, posy, 0xffffff);
		putpixel(mlx, chunk_pixel_size + chunk_posy, posy, 0xffffff);
	}
}

void display_chunk(mlx_t *mlx, chunk_t *chunk) {
	if (!chunk || !mlx) {
		return ;
	}
	display_chunk_border(mlx, chunk);
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
		}
	}
}

// void display_all_chunks() {
// 	(void)
// }

void render(data_t *data) {
	fill_screen(data->mlx, BACKGROUND_COLOR);
	display_chunk(data->mlx, get_chunk(data->chunks, 0, 0));
	mlx_put_image_to_window(data->mlx->mlx, data->mlx->win, data->mlx->img, 0, 0);
}
