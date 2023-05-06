/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sciftci <sciftci@student.42kocaeli.com.tr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 04:11:08 by sciftci           #+#    #+#             */
/*   Updated: 2023/05/06 04:51:33 by sciftci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	destroy_image(t_vars *vars, t_img *img)
{
	if (img->img)
		mlx_destroy_image(vars->mlx.mlx, img->img);
}

static void	destroy_sprite(t_vars *vars, t_spr *spr)
{
	int	i;

	i = 0;
	while (i < spr->frames)
	{
		destroy_image(vars, &spr->img[i]);
		i++;
	}
	spr->img = ft_free(spr->img);
}

int	exit_game(t_vars *vars, int exit_status)
{
	if (vars->mlx.win)
		mlx_destroy_window(vars->mlx.mlx, vars->mlx.win);
	destroy_image(vars, &vars->mlx.img);
	destroy_image(vars, &vars->map.north);
	destroy_image(vars, &vars->map.south);
	destroy_image(vars, &vars->map.west);
	destroy_image(vars, &vars->map.east);
	destroy_sprite(vars, &vars->map.collectible);
	list_clear(&vars->map.collectibles);
	destroy_sprite(vars, &vars->map.door);
	list_clear(&vars->map.doors);
	vars->map.map = ft_free_2d(vars->map.map);
	exit(exit_status);
}
