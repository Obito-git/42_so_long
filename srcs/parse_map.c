#include "../so_long.h"
t_bool is_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'C'
			|| c == 'E' || c == 'P' || c == '\n');
}

t_bool	is_cor_objectives_count(t_map *map, int player, int exit)
{
	if (map->width == map->height || player != 1 || exit < 1
		|| map->collect_count < 1)
	{
		ft_printf("Error\n");
		if (map->width == map->height)
			ft_printf("Squared map detected\n");
		if (player == 0)
			ft_printf("You dont have player\n");
		if (player > 1)
			ft_printf("It's not multiplayer game\n");
		if (exit < 1)
			ft_printf("You dont have exit\n");
		if (map->collect_count < 1)
			ft_printf("You dont have collectibles items\n");
		return (FALSE);
	}
	return (TRUE);
}

t_bool	is_correct_map(t_map *map)
{
	t_elem	*tmp;
	int		player_count;
	int		exit_count;

	player_count = 0;
	exit_count = 0;
	tmp = map->elem_list;
	while (tmp)
	{
		if ((tmp->x == 0 || tmp->x == map->width - 1
			|| tmp->y == 0 || tmp->y == map->height - 1)
			&& tmp->elem != '1')
		{
			ft_printf("Error\nIncorrect walls\n");
			return (FALSE);
		}
		if (tmp->elem == 'P')
			player_count++;
		if (tmp->elem == 'E')
			exit_count++;
		tmp = tmp->next;
	}
	return (is_cor_objectives_count(map, player_count, exit_count));
} 

t_bool	parse_coords(t_map *map, char *s)
{
	int	i;

	i = 0;
	if (map->width < 3 || ft_strlen(s) != (size_t) map->width)
	{
		ft_printf("Error\nWrong width of the map!\n");
		return (FALSE);
	}
	while (s[i] != '\n')
	{
		if (!is_map_char(s[i]) || !add_elem(map, s[i], i, map->height))
		{
			if (!is_map_char(s[i]))
				ft_printf("Error\nUnknown char: \"%c\"\n", s[i]);
			else if (!add_elem(map, s[i], i, map->height))
				ft_printf("Error\nMalloc returned NULL\n");
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}

t_bool parse_map(t_map *map, int fd)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
	{
		ft_printf("Error\nEmpty file detected\n");
		return (FALSE);
	}
	map->width = ft_strlen(line);
	while (line)
	{
		if (!parse_coords(map, line))
		{
			free_gnl(line, fd);
			return (FALSE);
		}
		free(line);
		line = get_next_line(fd);
		map->height++;
	}
	map->width--;
	close(fd);
	return (is_correct_map(map));
}

t_bool parse_args(t_map *map, int ac, char **av)
{
	int	fd;

	if (ac != 2 || ft_strlen(av[1]) < 5
		|| ft_strcmp(".ber", &av[1][ft_strlen(av[1]) - 4]) != 0)
	{
		if (ac == 1)
			ft_printf("Error\nYou heven't added any map!\n");
		else if (ac > 2)
			ft_printf("Error\nYou need to add only one map!\n");
		else
			ft_printf("Error\nYour map must have *.ber extantion!\n");
		return (FALSE);
	}
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Error\nCan't open %s\n", av[1]);
		return (FALSE);
	}
	if (!parse_map(map, fd))
	{
		close(fd);
		return (FALSE);
	}
	return (TRUE);
}
