
#include "game_of_life.h"

unsigned int compute_framerate(struct timeval *last_frame_time) {
	struct timeval time;
	float delta_time;
	gettimeofday(&time, NULL);

	delta_time = time.tv_sec - last_frame_time->tv_sec + (time.tv_usec - last_frame_time->tv_usec) / 1000000.0f;

	if (delta_time) {
		return (1 / delta_time);
	} else {
		return (9999999);
	}
}

int frame(data_t *data) {
	user_input(data);
	// next_generation(data->chunks);
	render(data);
	

	if (data->mlx->frame_count % 10 == 0) {
		data->mlx->framerate = compute_framerate(data->mlx->last_frame_time);
	}
	struct timeval time;
	gettimeofday(&time, NULL);
	data->mlx->last_frame_time->tv_sec = time.tv_sec;
	data->mlx->last_frame_time->tv_usec = time.tv_usec;

	char buff[15];
	sprintf(buff, "fps: %u", data->mlx->framerate);
	mlx_string_put(data->mlx->mlx, data->mlx->win, 20, 40, 0xffffff, buff);


	data->mlx->frame_count++;
	return (0);
}
