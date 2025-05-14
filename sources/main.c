
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
	new_chunk(data.chunks, 0, 1);
	new_chunk(data.chunks, 1, 0);
	new_chunk(data.chunks, 2, 0);
	new_chunk(data.chunks, 1, 1);
	new_chunk(data.chunks, 2, 1);

	// glider
	// new_cell(get_chunk(data.chunks, 0, 0)->cells, 60, 60);
	// new_cell(get_chunk(data.chunks, 0, 0)->cells, 59, 60);
	// new_cell(get_chunk(data.chunks, 0, 0)->cells, 58, 60);
	// new_cell(get_chunk(data.chunks, 0, 0)->cells, 58, 61);
	// new_cell(get_chunk(data.chunks, 0, 0)->cells, 59, 62);

	// blinker
	// new_cell(get_chunk(data.chunks, 0, 0)->cells, 20, 20);
	// new_cell(get_chunk(data.chunks, 0, 0)->cells, 20, 21);
	// new_cell(get_chunk(data.chunks, 0, 0)->cells, 20, 22);

	// LWSS
	new_cell(get_chunk(data.chunks, 0, 0)->cells, 20, 20);
	new_cell(get_chunk(data.chunks, 0, 0)->cells, 20, 19);
	new_cell(get_chunk(data.chunks, 0, 0)->cells, 20, 18);
	new_cell(get_chunk(data.chunks, 0, 0)->cells, 19, 17);
	new_cell(get_chunk(data.chunks, 0, 0)->cells, 19, 20);
	new_cell(get_chunk(data.chunks, 0, 0)->cells, 18, 20);
	new_cell(get_chunk(data.chunks, 0, 0)->cells, 17, 20);
	new_cell(get_chunk(data.chunks, 0, 0)->cells, 16, 19);
	new_cell(get_chunk(data.chunks, 0, 0)->cells, 16, 17);



	mlx_hook(data.mlx->win, 17, 0L, &exit_handling, &data);
	mlx_hook(data.mlx->win, 2, 1L << 0, &key_pressed, &data);
	
	render(&data);
	mlx_loop(data.mlx->mlx);
	
	return (0);
}