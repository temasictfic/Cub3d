/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_radian_operations.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sciftci <sciftci@student.42kocaeli.com.tr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 13:05:36 by hel-makh          #+#    #+#             */
/*   Updated: 2023/04/15 16:53:26 by sciftci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

double	ft_radian_operations(double radian, double amout)
{
	radian += amout;
	while (radian > 2 * M_PI)
		radian -= 2 * M_PI;
	while (radian < 0)
		radian += 2 * M_PI;
	return (radian);
}
