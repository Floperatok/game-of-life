
#include "game_of_life.h"

void user_input(data_t *data) {
	// KEYBOARD
	if (data->inputs->keys[32]) { // space
		next_generation(data->chunks);
	}

	// MOUSE
	
}
