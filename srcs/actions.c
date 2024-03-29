/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 13:49:29 by amyroshn          #+#    #+#             */
/*   Updated: 2022/01/28 13:52:24 by amyroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../so_long.h"

t_elem	*get_requested_pos(int keycode, t_map *map)
{
	t_elem	*tmp;
	int		req_x;
	int		req_y;

	tmp = map->elem_list;
	while (tmp->elem != 'P')
		tmp = tmp->next;
	req_x = tmp->x;
	req_y = tmp->y;
	map->player = tmp;
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

int	action_handler(int keycode, t_window *w)
{
	t_elem	*req_pos;

	req_pos = get_requested_pos(keycode, w->map);
	if (req_pos->elem == '0' || req_pos->elem == 'C')
	{
		mlx_put_image_to_window(w->mlx, w->mlx_win, w->img_backgr,
			w->map->player->x * BLOCK_SIZE, w->map->player->y * BLOCK_SIZE);
		mlx_put_image_to_window(w->mlx, w->mlx_win, w->img_player,
			req_pos->x * BLOCK_SIZE, req_pos->y * BLOCK_SIZE);
		if (req_pos->elem == 'C')
			w->map->collect_count--;
		w->map->player->elem = '0';
		req_pos->elem = 'P';
		return (1);
	}
	if (req_pos->elem == 'E' && w->map->collect_count == 0)
		return (-1);
	return (0);
}

void	put_moves_count(t_window *w)
{
	char		*str;

	mlx_put_image_to_window(w->mlx, w->mlx_win, w->img_wall, 0, 0);
	str = ft_itoa(w->map->moves_count);
	mlx_string_put(w->mlx, w->mlx_win, BLOCK_SIZE / 2, BLOCK_SIZE / 2,
		0x00000000, str);
	free(str);
}

int	ft_close(int keycode, t_window *w)
{
	int			action_res;

	if (keycode == ESC)
		mlx_loop_end(w->mlx);
	else if (keycode == LEFT || keycode == RIGHT
		|| keycode == UP || keycode == DOWN)
	{
		action_res = action_handler(keycode, w);
		if (action_res == -1)
		{
			ft_printf("Final result is %d\n", w->map->moves_count + 1);
			mlx_loop_end(w->mlx);
		}
		if (action_res)
		{
			w->map->moves_count++;
			put_moves_count(w);
		}
	}
	return (0);
}

void	draw_map(t_window *w, t_map *map)
{
	t_elem		*tmp;
	void		*img_pointer;

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
		mlx_put_image_to_window(w->mlx, w->mlx_win, img_pointer,
			tmp->x * BLOCK_SIZE, tmp->y * BLOCK_SIZE);
		tmp = tmp->next;
	}
	put_moves_count(w);
	mlx_hook(w->mlx_win, 2, 1L << 0, ft_close, w);
	mlx_hook(w->mlx_win, 33, 1L << 17, red_cross, w);
	mlx_loop(w->mlx);
}
