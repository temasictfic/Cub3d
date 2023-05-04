/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_game.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sciftci <sciftci@student.42kocaeli.com.tr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 17:24:09 by hel-makh          #+#    #+#             */
/*   Updated: 2023/04/15 16:54:43 by sciftci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	ft_destroy_image(t_vars *vars, t_img *img)
{
	if (img->img)
		mlx_destroy_image(vars->mlx.mlx, img->img);
}

static void	ft_destroy_sprite(t_vars *vars, t_spr *spr)
{
	int	i;

	i = 0;
	while (i < spr->frames)
	{
		ft_destroy_image(vars, &spr->img[i]);
		i ++;
	}
	spr->img = ft_free(spr->img);
}

int	ft_exit_game(t_vars *vars, int exit_status)
{
	if (vars->mlx.win)
		mlx_destroy_window(vars->mlx.mlx, vars->mlx.win);
	ft_destroy_image(vars, &vars->mlx.img);
	ft_destroy_image(vars, &vars->map.north);
	ft_destroy_image(vars, &vars->map.south);
	ft_destroy_image(vars, &vars->map.west);
	ft_destroy_image(vars, &vars->map.east);
	ft_destroy_sprite(vars, &vars->map.collectible);
	ft_collectible_lstclear(&vars->map.collectibles);
	ft_destroy_sprite(vars, &vars->map.door);
	ft_door_lstclear(&vars->map.doors);
	vars->map.map = ft_free_2d(vars->map.map);
	exit(exit_status);
}