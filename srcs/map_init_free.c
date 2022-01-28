/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 13:57:18 by amyroshn          #+#    #+#             */
/*   Updated: 2022/01/28 13:57:21 by amyroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../so_long.h"

t_map	*map_init(void)
{
	t_map	*map;

	map = (t_map *) malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->width = 0;
	map->height = 0;
	map->collect_count = 0;
	map->moves_count = 0;
	map->elem_list = NULL;
	return (map);
}

t_bool	add_elem(t_map *map, char elem, int x, int y)
{
	t_elem	*e;
	t_elem	*tmp;

	if (!map)
		return (FALSE);
	e = (t_elem *) malloc(sizeof(t_elem));
	if (!e)
		return (FALSE);
	e->x = x;
	e->y = y;
	e->elem = elem;
	if (elem == 'C')
		map->collect_count++;
	e->next = NULL;
	if (!map->elem_list)
	{
		map->elem_list = e;
		return (TRUE);
	}
	tmp = map->elem_list;
	while (tmp && tmp->next)
		tmp = tmp->next;
	tmp->next = e;
	return (TRUE);
}

void	free_map(t_map *map)
{
	t_elem	*e_list;

	if (!map)
		return ;
	while (map->elem_list)
	{
		e_list = map->elem_list;
		map->elem_list = map->elem_list->next;
		free(e_list);
	}
	free(map);
}

void	free_gnl(char *line, int fd)
{
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
}
