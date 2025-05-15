
#include "game_of_life.h"

int focus_in(data_t *data)
{
	mlx_do_key_autorepeatoff(data->mlx->mlx);
	return (0);
}

int focus_out(data_t *data)
{
	memset(data->inputs->keys, 0, sizeof(data->inputs->keys));
	mlx_do_key_autorepeaton(data->mlx->mlx);
	return (0);
}

int key_pressed(int keycode, data_t *data)
{
	if (keycode == 65307)
		exit_handling(data);
	if (keycode < 0 || keycode >= MAX_KEYS)
		return (0);

	if (data->inputs->keys[keycode] == 1)
		return (0);

	data->inputs->keys[keycode] = 1;

	printf("KEYBOARD: %d pressed\n", keycode);
	return (0);
}

int key_released(int keycode, data_t *data)
{
	if (keycode >= 0 && keycode < MAX_KEYS)
		data->inputs->keys[keycode] = 0;

	printf("KEYBOARD: %d released\n", keycode);
	return (0);
}

int button_pressed(int mouse_code, int x, int y, data_t *data) {
	if (mouse_code == 4) { // scroll up
		data->cam->x += (data->cam->x - data->inputs->mouse_x) / data->cam->cell_size;
		data->cam->y += (data->cam->y - data->inputs->mouse_y) / data->cam->cell_size;
		data->cam->cell_size++;
	} else if (mouse_code == 5 && data->cam->cell_size > 1) { // scroll down
		data->cam->x -= (data->cam->x - data->inputs->mouse_x) / data->cam->cell_size;
		data->cam->y -= (data->cam->y - data->inputs->mouse_y) / data->cam->cell_size;
		data->cam->cell_size--;
	} else if (mouse_code == 1) { // left click
		data->inputs->mouse_has_moved = 0;
		data->inputs->mouse_press_x = x - data->cam->x;
		data->inputs->mouse_press_y = y - data->cam->y;
	} else if (mouse_code == 3) { // right click
		next_generation(data->chunks);
		data->generation_count++;
		char buff[22];
		sprintf(buff, "Generation: %d", data->generation_count);
		mlx_string_put(data->mlx->mlx, data->mlx->win, 20, 20, 0xffffff, buff);
	}
	if (mouse_code < 0 || mouse_code >= MAX_BUTTONS)
		return (0);
	if (data->inputs->buttons[mouse_code] == 1)
		return (0);

	data->inputs->buttons[mouse_code] = 1;

	printf("MOUSE: %d pressed\n", mouse_code);
	return (0);
}

int button_released(int mouse_code, int x, int y, data_t *data)
{
	if (mouse_code >= 0 && mouse_code < MAX_BUTTONS) {
		data->inputs->buttons[mouse_code] = 0;
		if (mouse_code == 1 && !data->inputs->mouse_has_moved) { // mouse left
			int chunk_size = data->cam->cell_size * CHUNK_SIZE;
			int posx_chunk = (-data->cam->x + x) / chunk_size;
			int posy_chunk = (-data->cam->y + y) / chunk_size;
			printf("CHUNK CLICKED POS: %d,%d\n", posx_chunk, posy_chunk);
			chunk_t *chunk = get_chunk(data->chunks, posx_chunk, posy_chunk);
			if (!chunk) {
				return (0);
			}
			int posx_cell = (-data->cam->x + x) / data->cam->cell_size % CHUNK_SIZE;
			int posy_cell = (-data->cam->y + y) / data->cam->cell_size % CHUNK_SIZE;
			printf("CLICKED CELL: %d,%d\n", posx_cell, posy_cell);
			if (get_cell(chunk->cells, posx_cell, posy_cell)) {
				kill_cell(chunk->cells, posx_cell, posy_cell);
			} else {
				new_cell(chunk->cells, posx_cell, posy_cell);
			}
		}
	}

	printf("MOUSE: %d released\n", mouse_code);
	return (0);
}

int mouse_move(int x, int y, data_t *data) {
	if (data->inputs->buttons[1]) { // mouse left
		data->inputs->mouse_has_moved = 1;
		data->cam->x = x - data->inputs->mouse_press_x;
		data->cam->y = y - data->inputs->mouse_press_y;
	}
	data->inputs->mouse_x = x;
	data->inputs->mouse_y = y;
	return (0);
}