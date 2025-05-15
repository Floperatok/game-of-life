
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
		data->cam->x += (data->cam->x - x) / data->cam->cell_size;
		data->cam->y += (data->cam->y - y) / data->cam->cell_size;
		data->cam->cell_size++;
	} else if (mouse_code == 5 && data->cam->cell_size > 1) { // scroll down
		data->cam->x -= (data->cam->x - x) / data->cam->cell_size;
		data->cam->y -= (data->cam->y - y) / data->cam->cell_size;
		data->cam->cell_size--;
	} else if (mouse_code == 1) { // left click
		mouse_cell_edit(data, x, y, 0);
	} else if (mouse_code == 3) { // right click
		data->inputs->mouse_press_x = x - data->cam->x;
		data->inputs->mouse_press_y = y - data->cam->y;
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
	(void)x;
	(void)y;
	if (mouse_code >= 0 && mouse_code < MAX_BUTTONS) {
		data->inputs->buttons[mouse_code] = 0;
	}

	printf("MOUSE: %d released\n", mouse_code);
	return (0);
}

int mouse_move(int x, int y, data_t *data) {
	if (data->inputs->buttons[3]) { // right click
		data->cam->x = x - data->inputs->mouse_press_x;
		data->cam->y = y - data->inputs->mouse_press_y;
	} else if (data->inputs->buttons[1]) { // left click
		mouse_cell_edit(data, x, y, 1);
	}
	return (0);
}