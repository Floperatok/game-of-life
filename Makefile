####################################################################
#                            CONFIG                                #
####################################################################

CC				=	gcc
CFLAGS			=	-Wall -Werror -Wextra -g -std=gnu11
NAME			=	game_of_life

####################################################################
#                            FILES                                 #
####################################################################

SRC				=	main.c \
					init.c \
					render.c \
					frame.c \
					chunk.c \
					input.c \
					hooks.c \
					cell.c \
					generation.c \

MLX				=	libmlx.a

OBJ				=	$(SRC:.c=.o)

####################################################################
#                            PATHS                                 #
####################################################################

OBJ_PATH		=	objects/
SRC_PATH		=	sources/
MLX_PATH		=	minilibx-linux/

SRCS			=	$(addprefix $(SRC_PATH), $(SRC))
OBJS			=	$(addprefix $(OBJ_PATH), $(OBJ))
MLXS			=	$(addprefix $(MLX_PATH), $(MLX))

INC				=	includes/


####################################################################
#                            RULES                                 #
####################################################################

all:	$(NAME)

$(NAME):	$(OBJS)
	make -s -C $(MLX_PATH)

	$(CC) $(CFLAGS) $(OBJS) -L./minilibx-linux -lmlx -L/usr/lib -lXext -lX11 -lm -o $(NAME) 

$(OBJ_PATH)%.o:	$(SRC_PATH)%.c
	mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INC) -I $(MLX_PATH)

clean:
	rm -rf $(OBJ_PATH)
	make -sC $(MLX_PATH) clean

fclean:
	rm -rf $(OBJ_PATH)
	rm -f $(NAME)
	make -sC $(MLX_PATH) clean

re: fclean all

####################################################################
#                            COLORS                                #
####################################################################

COM_COLOR   = \033[0;34m
OK_COLOR    = \033[0;32m
NO_COLOR    = \033[m