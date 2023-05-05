/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_import_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sciftci <sciftci@student.42kocaeli.com.tr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 14:03:39 by hel-makh          #+#    #+#             */
/*   Updated: 2023/05/05 23:48:50 by sciftci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	init_map_vars(t_map *map)
{
	map->map = NULL;
	map->ce_color = -1;
	map->fl_color = -1;
	map->north.img = NULL;
	map->south.img = NULL;
	map->west.img = NULL;
	map->east.img = NULL;
	map->collectible.img = NULL;
	map->collectible.frames = 0;
	map->door.img = NULL;
	map->door.frames = 0;
	map->collectibles = NULL;
	map->doors = NULL;
}

int	import_map(t_vars *vars, char *file)
{
	char	*extension;
	int		fd;

	init_map_vars(&vars->map);
	extension = ft_strrstr(file, ".cub");
	if (!extension || (extension && ft_strcmp(extension, ".cub")))
		return (printf("Error\nInvalid file extension.\n%s\n", USAGE), 0);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (printf("Error\nCouldn't open <%s> file.\n", file), 0);
	if (!parse_textures(vars, fd) || !parse_map(&vars->map, fd))
		return (0);
	close(fd);
	get_player_position(vars);
	return (1);
}
