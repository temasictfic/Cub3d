/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render_minimap.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sciftci <sciftci@student.42kocaeli.com.tr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 19:53:41 by hel-makh          #+#    #+#             */
/*   Updated: 2023/05/05 22:59:45 by sciftci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	ft_draw_circle(int *data, t_circle circle, int color)
{
	int	edge;
	int	x;
	int	y;

	edge = CENTER - circle.radius;
	y = edge;
	while (y <= edge + (circle.radius * 2))
	{
		x = edge;
		while (x <= edge + (circle.radius * 2))
		{
			if (is_in_circle(x, y, circle))
				data[y * WIDTH + x] = color;
			x ++;
		}
		y ++;
	}
}

static void	ft_draw_square(int *data, t_coor coor, t_circle minimap, int color)
{
	int	x;
	int	y;

	y = coor.y + 1;
	while (y < coor.y + C_SIDE_LEN - 1)
	{
		x = coor.x + 1;
		while (x < coor.x + C_SIDE_LEN - 1)
		{
			if (is_in_circle(x, y, minimap) == 1)
				data[y * WIDTH + x] = color;
			x ++;
		}
		y ++;
	}
}

static void	ft_draw_map_components(t_vars *vars, t_circle minimap)
{
	t_coor	coor;
	int		i;
	int		j;

	i = ft_max(0, vars->player.pos.y - (C_VISIBLE / 2));
	while (vars->map.map[i] && i <= vars->player.pos.y + (C_VISIBLE / 2))
	{
		j = ft_max(0, vars->player.pos.x - (C_VISIBLE / 2));
		while (vars->map.map[i][j] && j <= vars->player.pos.x + (C_VISIBLE / 2))
		{
			coor.y = (i * C_SIDE_LEN)
				- (vars->player.pos.y * C_SIDE_LEN) + CENTER;
			coor.x = (j * C_SIDE_LEN)
				- (vars->player.pos.x * C_SIDE_LEN) + CENTER;
			if (vars->map.map[i][j] == C_DOOR)
				ft_draw_square(vars->mlx.img.data, coor, minimap,
					create_trgb(0, 118, 84, 16));
			else if (!ft_strchr("03NSEWC", vars->map.map[i][j]))
				ft_draw_square(vars->mlx.img.data, coor, minimap,
					create_trgb(0, 60, 60, 60));
			j ++;
		}
		i ++;
	}
}

void	ft_render_minimap(t_vars *vars)
{
	t_circle	minimap;
	t_circle	player;

	minimap.x = CENTER;
	minimap.y = CENTER;
	minimap.radius = RADIUS - 1;
	ft_draw_circle(vars->mlx.img.data, minimap,
		create_trgb(0, 255, 255, 255));
	ft_draw_map_components(vars, minimap);
	ft_draw_rays(vars, minimap);
	player.x = CENTER;
	player.y = CENTER;
	player.radius = PL_RADIUS;
	ft_draw_circle(vars->mlx.img.data, player,
		create_trgb(0, 255, 0, 0));
}
