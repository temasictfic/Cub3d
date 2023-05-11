/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sciftci <sciftci@student.42kocaeli.com.tr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 04:13:39 by sciftci           #+#    #+#             */
/*   Updated: 2023/05/11 19:17:00 by sciftci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	read_map(t_map *map, int fd)
{
	char	*line;
	int		empty_line;

	map->map = ft_calloc(1, sizeof(char *));
	if (map->map == NULL)
		return (0);
	empty_line = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (*line)
		{
			if (ft_arrlen(map->map) && empty_line)
				return (printf("Error\nInvalid map.\n"), ft_free(line), 0);
			map->map = ft_push_str(map->map, line);
			if (map->map == NULL)
				return (ft_free(line), 0);
		}
		else if (ft_arrlen(map->map))
			empty_line = 1;
		line = ft_free(line);
	}
	return (1);
}

static int	check_component(t_map *map, int i, int j, t_content *content)
{
	if (!ft_strchr(" 0123NSEWC", map->map[i][j]))
	{
		printf("Error\nInvalid map: Invalid component [%c]."
			"\nLine: %d, Column: %d\n", map->map[i][j], i + 1, j + 1);
		return (0);
	}
	else if (map->map[i][j] == WALL)
		content->wall ++;
	else if (map->map[i][j] == P_NORTH || map->map[i][j] == P_SOUTH
			|| map->map[i][j] == P_EAST || map->map[i][j] == P_WEST)
		content->player ++;
	return (1);
}

static int	check_map_content(t_map *map)
{
	t_content	content;
	int			i;
	int			j;

	content.wall = 0;
	content.player = 0;
	i = 0;
	while (map->map[i])
	{
		j = -1;
		while (map->map[i][++j])
			if (!check_component(map, i, j, &content))
				return (0);
		i ++;
	}
	if (!content.wall)
		return (printf("Error\nInvalid map: Map not closed.\n"), 0);
	else if (content.player < 1)
		return (printf("Error\nInvalid map: Missing player.\n"), 0);
	else if (content.player > 1)
		return (printf("Error\nInvalid map: Too many players.\n"), 0);
	return (1);
}

static int	is_map_closed(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			if (ft_strchr(" 023NSEWC", map->map[i][j]))
			{
				if (!component_surroundings(map->map, i, j))
					return (0);
			}
			j ++;
		}
		i ++;
	}
	return (1);
}

int	parse_map(t_map *map, int fd)
{
	if (!read_map(map, fd))
		return (0);
	if (!ft_arrlen(map->map))
		return (printf("Error\nInvalid map.\n"), 0);
	if (!check_map_content(map))
		return (0);
	if (!is_map_closed(map))
		return (0);
	return (1);
}
