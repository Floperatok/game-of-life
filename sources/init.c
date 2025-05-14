
#include "game_of_life.h"

int init_mlx(data_t *data) {
	if (!(data->mlx->mlx = mlx_init())) {
		return (0);
	}
	if (!(data->mlx->win = mlx_new_window(data->mlx->mlx, WIN_W, WIN_H, "Game of Life"))) {
		return (0);
	}
	if (!(data->mlx->img = mlx_new_image(data->mlx->mlx, WIN_W, WIN_H))) {
		return (0);
	}
	data->mlx->addr = mlx_get_data_addr(data->mlx->img, \
		&data->mlx->bpp, \
		&data->mlx->line_length, \
		&data->mlx->endian);
	return (1);
}

int init_chunks(data_t *data) {
	int i = -1;
	while (++i < HASH_TABLE_SIZE) {
		data->chunks[i] = NULL;
	}
	return (1);
}
