/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 13:57:42 by amyroshn          #+#    #+#             */
/*   Updated: 2022/01/28 13:58:52 by amyroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../so_long.h"

int	red_cross(t_window *w)
{
	mlx_loop_end(w->mlx);
	return (0);
}

void	free_window(t_window *w)
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

t_window	*window_init(t_map *map)
{
	t_window	*w;
	int			size;

	size = BLOCK_SIZE;
	w = (t_window *) malloc(sizeof(t_window));
	if (!w || !map)
		return (NULL);
	w->mlx = mlx_init();
	w->mlx_win = mlx_new_window(w->mlx, BLOCK_SIZE * map->width,
			BLOCK_SIZE * map->height, "so_long");
	w->img_wall = mlx_xpm_file_to_image(w->mlx, "./img/1.xpm", &size, &size);
	w->img_player = mlx_xpm_file_to_image(w->mlx, "./img/P.xpm", &size, &size);
	w->img_collect = mlx_xpm_file_to_image(w->mlx, "./img/C.xpm", &size, &size);
	w->img_backgr = mlx_xpm_file_to_image(w->mlx, "./img/0.xpm", &size, &size);
	w->img_exit = mlx_xpm_file_to_image(w->mlx, "./img/E.xpm", &size, &size);
	w->map = map;
	if (!w->mlx || !w->mlx_win || !w->img_wall || !w->img_player
		|| !w->img_collect || !w->img_backgr || !w->img_exit)
	{
		ft_printf("Error\nCan't parse xpm file or initialisate mlx\n");
		free_window(w);
		return (NULL);
	}
	return (w);
}
