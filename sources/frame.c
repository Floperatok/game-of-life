
#include "game_of_life.h"

int frame(data_t *data) {
	
	user_input(data);
	// next_generation(data->chunks);
	render(data);
	

	struct timeval time;
	gettimeofday(&time, NULL);
	unsigned int frame_time = (time.tv_usec - data->mlx->last_frame_time->tv_usec) + (time.tv_sec - data->mlx->last_frame_time->tv_sec) * 1000000;

	char buff[64];
	sprintf(buff, "Total Frame Time: %.3fms", frame_time / 1000.0f);
	mlx_string_put(data->mlx->mlx, data->mlx->win, 20, 80, 0xffffff, buff);
	data->mlx->last_frame_time->tv_sec = time.tv_sec;
	data->mlx->last_frame_time->tv_usec = time.tv_usec;

	return (0);
}
