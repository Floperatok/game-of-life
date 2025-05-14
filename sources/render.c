
#include "game_of_life.h"

void	putpixel(mlx_t *mlx, int x, int y, int color)
{
	if (x < 0 || x >= WIN_W || y < 0 || y >= WIN_H) {
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

void display_chunk_border(mlx_t *mlx, chunk_t *chunk) {
	int chunk_pixel_size = CHUNK_SIZE * CELL_SIZE;
	int chunk_posx = chunk->x * chunk_pixel_size;
	int chunk_posy = chunk->y * chunk_pixel_size;
	int i = -1;
	while (++i <= CHUNK_SIZE) {
		int posx = i * CELL_SIZE + chunk_posx;
		int posy = i * CELL_SIZE + chunk_posy;
		putpixel(mlx, posx, chunk_posy, 0xffffff);
		putpixel(mlx, posx, chunk_posy + chunk_pixel_size, 0xffffff);
		putpixel(mlx, chunk_posx, posy, 0xffffff);
		putpixel(mlx, chunk_posx + chunk_pixel_size, posy, 0xffffff);
	}
}

void display_chunk(mlx_t *mlx, chunk_t *chunk) {
	if (!chunk) {
		return ;
	}
	if (CHUNK_BORDER) {
		display_chunk_border(mlx, chunk);
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
		}
	}
}


void display_visible_chunks(mlx_t *mlx, chunk_t *hash_table[], int cam_pos_x, int cam_pos_y) {
	const int chunk_pixel_size = CHUNK_SIZE * CELL_SIZE;

	int min_x = cam_pos_x / chunk_pixel_size;
	int min_y = cam_pos_y / chunk_pixel_size;
	
	int max_x = (cam_pos_x + WIN_W) / chunk_pixel_size;
	int max_y = (cam_pos_y + WIN_H) / chunk_pixel_size;

	int y = min_y - 1;
	while (++y <= max_y) {
		int x = min_x - 1;
		while (++x <= max_x) {
			display_chunk(mlx, get_chunk(hash_table, x, y));
		}
	}
}

void render(data_t *data) {
	fill_screen(data->mlx, BACKGROUND_COLOR);
	display_visible_chunks(data->mlx, data->chunks, 0, 0);
	mlx_put_image_to_window(data->mlx->mlx, data->mlx->win, data->mlx->img, 0, 0);
}
