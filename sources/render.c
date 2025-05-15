
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

void display_chunk_border(data_t *data, chunk_t *chunk) {
	int chunk_pixel_size = CHUNK_SIZE * data->cam->cell_size;
	int chunk_posx = chunk->x * chunk_pixel_size + data->cam->x;
	int chunk_posy = chunk->y * chunk_pixel_size + data->cam->y;
	int i = -1;
	while (++i <= CHUNK_SIZE) {
		int posx = i * data->cam->cell_size + chunk_posx;
		int posy = i * data->cam->cell_size + chunk_posy;
		putpixel(data->mlx, posx, chunk_posy, 0xffffff);
		putpixel(data->mlx, posx, chunk_posy + chunk_pixel_size, 0xffffff);
		putpixel(data->mlx, chunk_posx, posy, 0xffffff);
		putpixel(data->mlx, chunk_posx + chunk_pixel_size, posy, 0xffffff);
	}
}

void display_chunk(data_t *data, chunk_t *chunk) {
	if (!chunk) {
		return ;
	}
	if (CHUNK_BORDER) {
		display_chunk_border(data, chunk);
	}
	int chunk_posx = chunk->x * CHUNK_SIZE * data->cam->cell_size + data->cam->x;
	int chunk_posy = chunk->y * CHUNK_SIZE * data->cam->cell_size + data->cam->y;
	int y = -1;
	while (++y < CHUNK_SIZE) {
		int x = -1;
		while (++x < CHUNK_SIZE) {
			if (get_cell(chunk->cells, x, y)) {

				int size = data->cam->cell_size;
				display_cell(data->mlx, \
					chunk_posx + x * data->cam->cell_size, \
					chunk_posy + y * data->cam->cell_size, \
					size);
			}
		}
	}
}


void display_visible_chunks(data_t *data) {
	const int chunk_pixel_size = CHUNK_SIZE * data->cam->cell_size;

	int min_x = -data->cam->x / chunk_pixel_size - 1;
	int min_y = -data->cam->y / chunk_pixel_size - 1;
	
	int max_x = (-data->cam->x + WIN_W) / chunk_pixel_size;
	int max_y = (-data->cam->y + WIN_H) / chunk_pixel_size;

	int y = min_y - 1;
	while (++y <= max_y) {
		int x = min_x - 1;
		while (++x <= max_x) {
			display_chunk(data, get_chunk(data->chunks, x, y));
		}
	}
}

void render(data_t *data) {
	fill_screen(data->mlx, BACKGROUND_COLOR);
	display_visible_chunks(data);
	mlx_put_image_to_window(data->mlx->mlx, data->mlx->win, data->mlx->img, 0, 0);
	char buff[22];
	sprintf(buff, "Generation: %d", data->generation_count);
	mlx_string_put(data->mlx->mlx, data->mlx->win, 20, 20, 0xffffff, buff);
}
