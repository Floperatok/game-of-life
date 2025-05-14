
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

	// glider
	new_cell(get_chunk(data.chunks, 0, 0)->cells, 41, 40);
	new_cell(get_chunk(data.chunks, 0, 0)->cells, 42, 41);
	new_cell(get_chunk(data.chunks, 0, 0)->cells, 40, 42);
	new_cell(get_chunk(data.chunks, 0, 0)->cells, 41, 42);
	new_cell(get_chunk(data.chunks, 0, 0)->cells, 42, 42);

	
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
	printf("hello\n");
	mlx_loop_hook(data.mlx->mlx, &frame, &data);
	
	render(&data);
	mlx_loop(data.mlx->mlx);
	
	return (0);
}