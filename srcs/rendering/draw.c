/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sciftci <sciftci@student.42kocaeli.com.tr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 11:06:14 by hel-makh          #+#    #+#             */
/*   Updated: 2023/05/06 00:01:13 by sciftci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	draw_line(t_vars *vars, t_coor dest, t_circle minimap)
{
	int		steps;
	t_coor	inc;
	t_coor	coor;

	dest.x -= vars->player.pos.x;
	dest.y -= vars->player.pos.y;
	steps = (int)fmax(fabs(dest.x), fabs(dest.y));
	if (!steps)
		steps = 1;
	inc.x = dest.x / steps;
	inc.y = dest.y / steps;
	steps *= C_SIDE_LEN;
	coor.x = minimap.x;
	coor.y = minimap.y;
	while (steps >= 0 && is_in_circle(coor.x, coor.y, minimap) == 1)
	{
		vars->mlx.img.data
		[(int)round(coor.y) * WIDTH + (int)round(coor.x)]
			= create_trgb(0, 0, 255, 0);
		coor.x += inc.x;
		coor.y += inc.y;
		steps --;
	}
}

void	draw_rays(t_vars *vars, t_circle minimap)
{
	double	degree;
	double	angle;
	t_coor	hit_wall;

	degree = 0;
	while (degree <= FOV)
	{
		angle = radian_operations(vars->player.angle,
				deg_to_rad(degree - (FOV / 2)));
		hit_wall = get_hit_wall(vars, vars->player.pos, angle, NULL);
		while (vars->map.map[(int)hit_wall.y][(int)hit_wall.x] == O_DOOR)
			hit_wall = get_hit_wall(vars, hit_wall, angle, NULL);
		draw_line(vars, hit_wall, minimap);
		degree += 2;
	}
}

void	draw_floor_ceilling(t_vars *vars)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (y < HEIGHT / 2)
				vars->mlx.img.data[y * WIDTH + x] = vars->map.ce_color;
			else
				vars->mlx.img.data[y * WIDTH + x] = vars->map.fl_color;
			x ++;
		}
		y ++;
	}
}