/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sciftci <sciftci@student.42kocaeli.com.tr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 04:10:53 by sciftci           #+#    #+#             */
/*   Updated: 2023/05/06 05:36:49 by sciftci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

double	rad(double degree)
{
	return (degree * (M_PI / 180.0));
}

double	get_dist(t_coor point1, t_coor point2)
{
	t_coor	dist;

	dist.x = powf(point2.x - point1.x, 2);
	dist.y = powf(point2.y - point1.y, 2);
	return (sqrtf(dist.x + dist.y));
}

int	is_in_circle(double x, double y, t_circle circle)
{
	double	distance_to_center;

	distance_to_center = sqrtf(powf(x - circle.x, 2) + powf(y - circle.y, 2));
	if (distance_to_center <= circle.radius)
	{
		if (distance_to_center <= circle.radius - 1)
			return (1);
		return (2);
	}
	return (0);
}

double	rad_op(double radian, double amount)
{
	radian += amount;
	while (radian > 2 * M_PI)
		radian -= 2 * M_PI;
	while (radian < 0)
		radian += 2 * M_PI;
	return (radian);
}
