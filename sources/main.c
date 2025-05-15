
#include "game_of_life.h"

int exit_handling(data_t *data) {
	mlx_do_key_autorepeaton(data->mlx->mlx);
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
	camera_t cam;
	input_t inputs;
	struct timeval last_frame_time;
	data.mlx = &mlx;
	data.cam = &cam;
	data.inputs = &inputs;
	data.cam->cell_size = 5;
	data.cam->x = WIN_W / 2 - CHUNK_SIZE * data.cam->cell_size / 2;
	data.cam->y = WIN_H / 2 - CHUNK_SIZE * data.cam->cell_size / 2;
	memset(data.inputs->keys, 0, sizeof(data.inputs->keys));
	memset(data.inputs->buttons, 0, sizeof(data.inputs->buttons));
	data.inputs->mouse_press_x = 0;
	data.inputs->mouse_press_y = 0;
	data.inputs->creating_cells = 1;
	data.generation_count = 0;
	data.generation_time = 0;
	data.mlx->last_frame_time = &last_frame_time;


	if (!init_mlx(&data) || !init_chunks(&data)) {
		exit_handling(&data);
	}

	new_chunk(data.chunks, 0, 0);

	// waa
	new_cell(get_chunk(data.chunks, 0, 0)->cells, 10, 10);
	new_cell(get_chunk(data.chunks, 0, 0)->cells, 10, 11);
	new_cell(get_chunk(data.chunks, 0, 0)->cells, 10, 12);
	new_cell(get_chunk(data.chunks, 0, 0)->cells, 11, 12);
	new_cell(get_chunk(data.chunks, 0, 0)->cells, 9, 11);


	// glider
	// new_cell(get_chunk(data.chunks, 0, 0)->cells, 41, 40);
	// new_cell(get_chunk(data.chunks, 0, 0)->cells, 42, 41);
	// new_cell(get_chunk(data.chunks, 0, 0)->cells, 40, 42);
	// new_cell(get_chunk(data.chunks, 0, 0)->cells, 41, 42);
	// new_cell(get_chunk(data.chunks, 0, 0)->cells, 42, 42);

	
	// blinker
	// new_cell(get_chunk(data.chunks, 0, 0)->cells, 20, 20);
	// new_cell(get_chunk(data.chunks, 0, 0)->cells, 20, 21);
	// new_cell(get_chunk(data.chunks, 0, 0)->cells, 20, 22);

	// LWSS
	// new_cell(get_chunk(data.chunks, 0, 0)->cells, 20, 20);
	// new_cell(get_chunk(data.chunks, 0, 0)->cells, 20, 19);
	// new_cell(get_chunk(data.chunks, 0, 0)->cells, 20, 18);
	// new_cell(get_chunk(data.chunks, 0, 0)->cells, 19, 17);
	// new_cell(get_chunk(data.chunks, 0, 0)->cells, 19, 20);
	// new_cell(get_chunk(data.chunks, 0, 0)->cells, 18, 20);
	// new_cell(get_chunk(data.chunks, 0, 0)->cells, 17, 20);
	// new_cell(get_chunk(data.chunks, 0, 0)->cells, 16, 19);
	// new_cell(get_chunk(data.chunks, 0, 0)->cells, 16, 17);

	gettimeofday(data.mlx->last_frame_time, NULL);
	mlx_hook(data.mlx->win, 9, 1L << 21, &focus_in, &data);
	mlx_hook(data.mlx->win, 10, 1L << 21, &focus_out, &data);
	mlx_hook(data.mlx->win, 17, 0L, &exit_handling, &data);
	mlx_hook(data.mlx->win, 2, 1L << 0, &key_pressed, &data);
	mlx_hook(data.mlx->win, 3, 1L << 1, &key_released, &data);
	mlx_hook(data.mlx->win, 4, 1L << 2, &button_pressed, &data);
	mlx_hook(data.mlx->win, 5, 1L << 3, &button_released, &data);
	mlx_hook(data.mlx->win, 6, 1L << 6, &mouse_move, &data);
	mlx_loop_hook(data.mlx->mlx, &frame, &data);

	mlx_loop(data.mlx->mlx);
	
	return (0);
}