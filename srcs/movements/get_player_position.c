/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_player_position.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sciftci <sciftci@student.42kocaeli.com.tr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 04:14:15 by sciftci           #+#    #+#             */
/*   Updated: 2023/05/11 19:03:51 by sciftci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	get_player_angle(t_vars *vars)
{
	int	x;
	int	y;

	x = vars->player.pos.x;
	y = vars->player.pos.y;
	if (vars->map.map[y][x] == 'N')
		vars->player.angle = M_PI_2;
	else if (vars->map.map[y][x] == 'S')
		vars->player.angle = M_PI + M_PI_2;
	else if (vars->map.map[y][x] == 'E')
		vars->player.angle = M_PI;
	else if (vars->map.map[y][x] == 'W')
		vars->player.angle = 0;
}

void	get_player_position(t_vars *vars)
{
	int	i;
	int	j;

	i = 0;
	while (vars->map.map[i])
	{
		j = 0;
		while (vars->map.map[i][j])
		{
			if (ft_strchr("NSEW", vars->map.map[i][j]))
			{
				vars->player.pos.x = (double)j;
				vars->player.pos.y = (double)i;
				get_player_angle(vars);
			}
			else if (vars->map.map[i][j] == COLLECTIBLE)
				list_add_front(&vars->map.collectibles, list_new(obj_new(j, i,
							1)));
			else if (vars->map.map[i][j] == O_DOOR)
				list_add_front(&vars->map.doors, list_new(obj_new(j, i,
							vars->map.door.frames - 1)));
			j++;
		}
		i++;
	}
}
