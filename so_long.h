/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 13:45:52 by amyroshn          #+#    #+#             */
/*   Updated: 2022/01/28 14:00:17 by amyroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef SO_LONG_H
# define SO_LONG_H
# include "libs/libft/libft.h"
# include "libs/minilibx-linux/mlx.h"
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# define BLOCK_SIZE 75
# define UP 119
# define DOWN 115
# define LEFT 97
# define RIGHT 100
# define ESC 65307

typedef struct s_map {
	int				width;
	int				height;
	int				collect_count;
	int				moves_count;
	struct s_elem	*player;
	struct s_elem	*elem_list;
}				t_map;

typedef struct s_elem {
	int				x;
	int				y;
	char			elem;
	struct s_elem	*next;
}	t_elem;

typedef struct s_window {
	void			*mlx;
	void			*mlx_win;	
	void			*img_wall;
	void			*img_player;
	void			*img_collect;
	void			*img_exit;
	void			*img_backgr;
	struct s_map	*map;
}	t_window;

t_bool		is_map_char(char c);
//structs
t_map		*map_init(void);
t_bool		add_elem(t_map *map, char elem, int x, int y);
void		free_map(t_map *map);
void		free_gnl(char *line, int fd);
//window
void		free_window(t_window *w);
t_window	*window_init(t_map *map);
void		draw_map(t_window *w, t_map *map);
int			red_cross(t_window *w);
//parsing
t_bool		parse_args(t_map *map, int ac, char **av);
#endif
