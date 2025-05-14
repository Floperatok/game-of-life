
#include "game_of_life.h"

int key_pressed(int keycode, data_t *data) {
	if (keycode == 65307) {
		exit_handling(data);
	} else if (keycode == 32) {
		next_generation(data);
		render(data);
	} else {
		printf("KEYCODE: %d\n", keycode);
	}
	return (0);
}
