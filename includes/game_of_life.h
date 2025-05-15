
#ifndef GAME_OF_LIFE_H
#define GAME_OF_LIFE_H

#include "mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>

#define HASH_TABLE_SIZE 1024
#define MAX_KEYS 256
#define MAX_BUTTONS 16

#define CHUNK_BORDER 1
#define CHUNK_SIZE 64
#define CHUNK_BITS (CHUNK_SIZE * CHUNK_SIZE) / 8 + 7

#define BACKGROUND_COLOR 0x000000
#define CELL_COLOR 0xffffff

#define WIN_H 720
#define WIN_W 1280

// temporary


typedef struct chunk_s
{
	int 			x;
	int				y;
	unsigned char	cells[CHUNK_BITS];
	unsigned char	backup[CHUNK_BITS];
	char			is_backup;
	struct chunk_s	*next;
}	chunk_t;

typedef struct
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*addr;
	int				line_length;
	int				bpp;
	int				endian;
	struct timeval	*last_frame_time;
}	mlx_t;

typedef struct 
{
	int	cell_size;
	int				x;
	int				y;
}	camera_t;

typedef struct 
{
	char		keys[MAX_KEYS];
	char		buttons[MAX_BUTTONS];
	int			mouse_x;
	int			mouse_y;
	int			mouse_press_x;
	int			mouse_press_y;
	char		mouse_has_moved;
}	input_t;

typedef struct
{
	mlx_t			*mlx;
	chunk_t			*chunks[HASH_TABLE_SIZE];
	camera_t		*cam;
	input_t			*inputs;
	unsigned int	generation_count;
	unsigned int	generation_time;
}	data_t;

int				init_mlx(data_t *data);
int				init_chunks(data_t *data);
void 			destroy_chunks(chunk_t *hash_table[]);
chunk_t			*new_chunk(chunk_t *hash_table[], int x, int y);
chunk_t			*get_chunk(chunk_t *hash_table[], int x, int y);
void			print_chunk(const unsigned char *cells);
int				frame(data_t *data);
void			render(data_t *data);
void			user_input(data_t *data);
int				exit_handling(data_t *data);
void			new_cell(unsigned char *data, int x, int y);
void			kill_cell(unsigned char *data, int x, int y);
int				get_cell(const unsigned char *data, int x, int y);
unsigned int	next_generation(chunk_t *chunks[]);
int				focus_in(data_t *data);
int				focus_out(data_t *data);
int				key_pressed(int keycode, data_t *data);
int				key_released(int keycode, data_t *data);
int				button_pressed(int mouse_code, int x, int y, data_t *data);
int				button_released(int mouse_code, int x, int y, data_t *data);
int				mouse_move(int x, int y, data_t *data);

#endif