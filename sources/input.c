
#include "game_of_life.h"

void user_input(data_t *data) {
	// KEYBOARD
	if (data->inputs->keys[32]) { // space
		data->generation_time = next_generation(data->chunks);
		data->generation_count++;
	}

	// MOUSE
	
}
