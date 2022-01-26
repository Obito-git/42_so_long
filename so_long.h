#ifndef SO_LONG_H
# define SO_LONG_H

#include "libs/libft/libft.h"
#include "libs/minilibx-linux/mlx.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

typedef struct s_map {
	int				width;
	int				height;
	int				collect_count;
	struct s_elem	*elem_list;
} t_map;

typedef struct s_elem {
	int				x;
	int				y;
	char			elem;
	struct s_elem	*next;
} t_elem;

//structs
t_map	*map_init(void);
t_bool	add_elem(t_map *map, char elem, int x, int y);
void	free_map(t_map *map);

t_bool parse_args(t_map **map, int ac, char **av);
#endif
