/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sciftci <sciftci@student.42kocaeli.com.tr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 04:13:23 by sciftci           #+#    #+#             */
/*   Updated: 2023/05/06 04:13:26 by sciftci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	is_parsed(t_map *map)
{
	if (map->north.img && map->south.img && map->west.img && map->east.img
		&& map->collectible.img && map->door.img
		&& map->fl_color != -1 && map->ce_color != -1)
		return (1);
	return (0);
}

static int	is_duplicated(t_map *map, char **info)
{
	if ((!ft_strcmp(info[0], "NO") && map->north.img)
		|| (!ft_strcmp(info[0], "SO") && map->south.img)
		|| (!ft_strcmp(info[0], "WE") && map->west.img)
		|| (!ft_strcmp(info[0], "EA") && map->east.img)
		|| (!ft_strcmp(info[0], "CO") && map->collectible.img)
		|| (!ft_strcmp(info[0], "DO") && map->door.img)
		|| (!ft_strcmp(info[0], "F") && map->fl_color != -1)
		|| (!ft_strcmp(info[0], "C") && map->ce_color != -1))
		return (perror("Error\nDuplicated textures [%s].\n"), 1);
	return (0);
}

static int	is_valid_format(char **info)
{
	if ((!ft_strcmp(info[0], "NO") && ft_arrlen(info) != 2)
		|| (!ft_strcmp(info[0], "SO") && ft_arrlen(info) != 2)
		|| (!ft_strcmp(info[0], "WE") && ft_arrlen(info) != 2)
		|| (!ft_strcmp(info[0], "EA") && ft_arrlen(info) != 2)
		|| (!ft_strcmp(info[0], "CO") && ft_arrlen(info) < 2)
		|| (!ft_strcmp(info[0], "DO") && ft_arrlen(info) < 2)
		|| (!ft_strcmp(info[0], "F") && ft_arrlen(info) != 2)
		|| (!ft_strcmp(info[0], "C") && ft_arrlen(info) != 2))
		return (perror("Error\nInvalid texture format.\n"), 0);
	return (1);
}

int	parse_textures(t_vars *vars, int fd)
{
	char	*line;
	char	**info;

	while (!is_parsed(&vars->map))
	{
		line = get_next_line(fd);
		if (!line)
			return (perror("Error\nMissing textures.\n"), 0);
		if (*line)
		{
			info = ft_split(line, ' ');
			if (!is_valid_format(info)
				|| is_duplicated(&vars->map, info)
				|| !get_textures(vars, info))
				return (ft_free_2d(info), 0);
			info = ft_free_2d(info);
		}
		line = ft_free(line);
	}
	return (1);
}
