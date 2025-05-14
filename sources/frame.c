
#include "game_of_life.h"

int frame(data_t *data) {
	user_input(data);
	// next_generation(data->chunks);
	render(data);

	return (0);
}
