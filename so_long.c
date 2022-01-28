/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 13:48:21 by amyroshn          #+#    #+#             */
/*   Updated: 2022/01/28 13:54:32 by amyroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

t_bool	is_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'C'
		|| c == 'E' || c == 'P' || c == '\n');
}

int	main(int ac, char **av)
{
	t_map		*map;
	t_window	*w;

	map = map_init();
	if (!map || !parse_args(map, ac, av))
	{
		if (!map)
			ft_printf("Error\nMalloc returned NULL\n");
		free_map(map);
		return (0);
	}
	w = window_init(map);
	if (w)
		draw_map(w, map);
	free_map(map);
	free_window(w);
}
