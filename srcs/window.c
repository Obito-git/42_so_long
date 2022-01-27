#include "../so_long.h"

void		free_window(t_window *w)
{
	if (!w)
		return ;

	mlx_destroy_image(w->mlx, w->img_wall);
	mlx_destroy_image(w->mlx, w->img_player);
	mlx_destroy_image(w->mlx, w->img_collect);
	mlx_destroy_image(w->mlx, w->img_exit);
	mlx_destroy_image(w->mlx, w->img_backgr);
	mlx_destroy_window(w->mlx, w->mlx_win);
	mlx_destroy_display(w->mlx);
	free(w->mlx);
	free(w);
}

/*
t_elem *get_requested_pos(int keycode, t_map *map)
{
	t_elem	*tmp;
	int		req_x;
	int		req_y;

	tmp = map->elem_list;
	while (tmp->elem != 'P')
		tmp = tmp->next;
	req_x = tmp->x;
	req_y = tmp->y;
	map->player_x = tmp->x;
	map->player_y = tmp->y;
	if (keycode == LEFT)
		req_x--;
	else if (keycode == RIGHT)
		req_x++;
	else if (keycode == UP)
		req_y--;
	else
		req_y++;
	tmp = map->elem_list;
	while (req_x != tmp->x || req_y != tmp->y)
		tmp = tmp->next;
	return (tmp);
}

t_bool action_handler(int keycode, t_window *w)
{
	t_elem	*req_pos;

	req_pos = get_requested_pos(keycode, w->map);
	if (req_pos->elem == '1')
		ft_printf("Wall\n");
	if (req_pos->elem == '0')
	{
		mlx_put_image_to_window(w->mlx, w->mlx_win, w->img_backgr,
						w->map->player_x * BLOCK_SIZE, 
						w->map->player_y * BLOCK_SIZE);
		mlx_put_image_to_window(w->mlx, w->mlx_win, w->img_player,
						req_pos->x * BLOCK_SIZE, 
						req_pos->y * BLOCK_SIZE);
		w->map->player_x = req_pos->x;
		w->map->player_y = req_pos->y;
	}
	if (req_pos->elem == 'C')
		ft_printf("Ramen\n");
	if (req_pos->elem == 'E')
		ft_printf("Exit\n");
	return (TRUE);
} */

int ft_close(int keycode, t_window *w)
{
	ft_printf("%d\n", keycode);
	if (keycode == ESC)
		mlx_loop_end(w->mlx);
	//else if (keycode == LEFT || keycode == RIGHT
	//		|| keycode == UP || keycode == DOWN)
	//	action_handler(keycode, w);
	return (0);
}

t_window	*window_init(t_map *map)
{
	t_window	*w;
	int			size;

	size = BLOCK_SIZE;
	w = (t_window *) malloc(sizeof(t_window));
	if (!w)
		return (NULL);
	w->mlx = mlx_init();
	w->mlx_win = mlx_new_window(w->mlx, BLOCK_SIZE * map->width,
								BLOCK_SIZE * map->height, "so_long");
	w->img_wall = mlx_xpm_file_to_image(w->mlx, "./img/1.xpm", &size, &size);
	w->img_player = mlx_xpm_file_to_image(w->mlx, "./img/P.xpm", &size, &size);
	w->img_collect = mlx_xpm_file_to_image(w->mlx, "./img/C.xpm", &size, &size);
	w->img_backgr = mlx_xpm_file_to_image(w->mlx, "./img/0.xpm", &size, &size);
	w->img_exit = mlx_xpm_file_to_image(w->mlx, "./img/E.xpm", &size, &size);
	//w->map = map;
	if (!w->mlx || !w->mlx_win || !w->img_wall || !w->img_player
		|| !w->img_collect || !w->img_backgr || !w->img_exit)
	{
		ft_printf("Error\nCan't parse xpm file or initialisate mlx\n");
		free_window(w);
		return (NULL);
	}
	return (w);
}

void	draw_map(t_map *map)
{
	t_window	*w;
	t_elem		*tmp;
	void		*img_pointer;

	w = window_init(map);
	tmp = map->elem_list;
	while (tmp)
	{
		if (tmp->elem == '1')
			img_pointer = w->img_wall;
		if (tmp->elem == '0')
			img_pointer = w->img_backgr;
		if (tmp->elem == 'P')
			img_pointer = w->img_player;
		if (tmp->elem == 'C')
			img_pointer = w->img_collect;
		if (tmp->elem == 'E')
			img_pointer = w->img_exit;
		mlx_put_image_to_window(w->mlx, w->mlx_win, img_pointer, tmp->x 
								* BLOCK_SIZE, tmp->y * BLOCK_SIZE);
		tmp = tmp->next;
	}
	mlx_hook(w->mlx_win, 2, 1L<<0, ft_close, w);
	mlx_loop(w->mlx);
	free_window(w);
}
