/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_distance.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sciftci <sciftci@student.42kocaeli.com.tr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 15:15:56 by hel-makh          #+#    #+#             */
/*   Updated: 2023/04/15 16:53:38 by sciftci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

double	ft_get_distance(t_coor point1, t_coor point2)
{
	t_coor	dist;

	dist.x = powf(point2.x - point1.x, 2);
	dist.y = powf(point2.y - point1.y, 2);
	return (sqrtf(dist.x + dist.y));
}
