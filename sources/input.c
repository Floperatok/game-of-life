
#include "game_of_life.h"

int key_pressed(int keycode, data_t *data) {
	if (keycode == 65307) {
		exit_handling(data);
	} else if (keycode == 32) {
		next_generation(data->chunks);
		render(data);
	} else {
		printf("KEYCODE: %d\n", keycode);
	}
	return (0);
}

int mouse_pressed(int mouse_code, int x, int y, data_t *data) {
	(void)x;
	(void)y;
	if (mouse_code == 4) {
		data->cell_size++;
	} else if (mouse_code == 5 && data->cell_size > 1) {
		data->cell_size--;
	} else {
		printf("MOUSE CODE: %d\n", mouse_code);
		return (0);
	}
	render(data);
	return (0);
}