
#ifndef GAME_OF_LIFE_H
#define GAME_OF_LIFE_H

#include "mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define HASH_TABLE_SIZE 3

#define CHUNK_SIZE 64
#define CHUNK_BITS (CHUNK_SIZE * CHUNK_SIZE) / 8 + 7

#define BACKGROUND_COLOR 0x000000
#define CELL_COLOR 0xffffff

#define WIN_H 360
#define WIN_W 480

typedef struct chunk_s
{
	int 			x;
	int				y;
	unsigned char	cells[CHUNK_BITS];
	unsigned char	tmp[CHUNK_BITS];
	struct chunk_s	*next;
}	chunk_t;

typedef struct
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		line_length;
	int		bpp;
	int		endian;
}	mlx_t;

typedef struct
{
	mlx_t			*mlx;
	chunk_t			*chunks[HASH_TABLE_SIZE];
}	data_t;

int		init_mlx(data_t *data);
int		init_chunks(data_t *data);
void 	destroy_chunks(chunk_t *hash_table[]);
int		new_chunk(chunk_t *hash_table[], int x, int y);
chunk_t	*get_chunk(chunk_t *hash_table[], int x, int y);
int		frame(void *arg);
void	render(data_t *data);
int		key_pressed(int keycode, data_t *data);
int		exit_handling(data_t *data);
void	new_cell(unsigned char *data, int x, int y);
void	kill_cell(unsigned char *data, int x, int y);
int		get_cell(const unsigned char *data, int x, int y);


#endif