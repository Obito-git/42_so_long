NAME = so_long
CC = gcc
CFLAGS = -Wall -Werror -Wextra
MLX_FLAGS = -I -g -L /usr/X11/lib -L./$(MLX_PATH) -lmlx -Imlx -lXext -lX11 -lz -lm

#LIBFT
LIBS=libs/

MLX_PATH=$(LIBS)minilibx-linux/
MLX_NAME=libmlx_Linux.a
MLX = $(addprefix $(MLX_PATH), $(MLX_NAME))

#LIBFT
LIBFT_PATH=$(LIBS)libft/
LIBFT_NAME=libft.a
LIBFT  = $(addprefix $(LIBFT_PATH), $(LIBFT_NAME))

SRCS = so_long.c srcs/parse_map.c srcs/structs.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)
	
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): lib mlx $(OBJS)
		$(CC) -o $(NAME) $(OBJS) $(CFLAGS) $(MLX_FLAGS) $(LIBFT) $(MLX)

fsan:
		$(CC) -o $(NAME) $(OBJS) -g3 -fsanitize=address $(CFLAGS) $(MLX_FLAGS) $(LIBFT) $(MLX)

mlx:
	@$(MAKE) -C $(MLX_PATH)

lib:
	@git submodule init
	@git submodule update
	@$(MAKE) -C $(LIBFT_PATH)

clean:
	@rm -f $(OBJS)
	@rm -f .*.swp
	@rm -f *.so
	@rm -f a.out
	@$(MAKE) clean -C $(LIBFT_PATH)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus

