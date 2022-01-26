#include "libs/minilibx-linux/mlx.h"
#include "so_long.h"

void print_map(t_map *map)
{
	if (!map)
	{
		ft_printf("map == NULL\n");
		return ;
	}

	if (!map->elem_list)
	{
		ft_printf("elem_list == NULL\n");
		return ;
	}
	ft_printf("height %d, width %d\n", map->height, map->width);
	t_elem *tmp = map->elem_list;
	while (tmp)
	{
		int x = tmp->x;
		ft_printf("%c(%d,%d) ", tmp->elem, tmp->x, tmp->y);
		tmp = tmp->next;
		if (tmp && tmp->x < x)
			ft_printf("\n");
		else if (!tmp)
			ft_printf("\n");
	}
}

int	main(int ac, char **av)
{
	t_map *map;

	map = NULL;
	if (!parse_args(&map, ac, av))
	{
		ft_printf("Not parsed\n");
		free_map(map);
		return (0);
	}
	print_map(map);
	free_map(map);
}
