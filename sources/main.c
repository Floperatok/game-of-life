
#include "game_of_life.h"

int exit_handling(data_t *data) {
	mlx_destroy_image(data->mlx->mlx, data->mlx->img);
	mlx_destroy_window(data->mlx->mlx, data->mlx->win);
	mlx_destroy_display(data->mlx->mlx);
	free(data->mlx->mlx);
	destroy_chunks(data->chunks);
	exit(EXIT_SUCCESS);
}

int main(void) {
	data_t data;
	mlx_t mlx;
	data.mlx = &mlx;

	if (!init_mlx(&data) || !init_chunks(&data)) {
		exit_handling(&data);
	}

	new_chunk(data.chunks, 0, 0);
	new_chunk(data.chunks, 1, 1);
	new_cell(get_chunk(data.chunks, 0, 0)->cells, 5, 5);
	new_cell(get_chunk(data.chunks, 1, 1)->cells, 0, 0);


	mlx_hook(data.mlx->win, 17, 0L, &exit_handling, &data);
	mlx_hook(data.mlx->win, 2, 1L << 0, &key_pressed, &data);
	
	render(&data);
	mlx_put_image_to_window(data.mlx->mlx, data.mlx->win, data.mlx->img, 0, 0);
	mlx_loop(data.mlx->mlx);
	
	return (0);
}