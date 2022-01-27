#include "libs/minilibx-linux/mlx.h"
#include "so_long.h"

void print_map(t_map *map)
{
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
