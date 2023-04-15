/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_radian_degree.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sciftci <sciftci@student.42kocaeli.com.tr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 16:13:11 by hel-makh          #+#    #+#             */
/*   Updated: 2023/04/15 16:53:29 by sciftci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

double	ft_rtod(double radian)
{
	return (radian * (180.0 / M_PI));
}

double	ft_dtor(double degree)
{
	return (degree * (M_PI / 180.0));
}
