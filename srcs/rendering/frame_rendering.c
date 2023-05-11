/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_rendering.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sciftci <sciftci@student.42kocaeli.com.tr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 04:12:32 by sciftci           #+#    #+#             */
/*   Updated: 2023/05/11 19:18:29 by sciftci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	init_images(t_vars *vars)
{
	vars->mlx.img.img = mlx_new_image(vars->mlx.mlx, WIDTH, HEIGHT);
	if (!vars->mlx.img.img)
		return (printf("Error\nCouldn't create images.\n"), 0);
	vars->mlx.img.data = (int *)mlx_get_data_addr(vars->mlx.img.img,
			&vars->mlx.img.bpp, &vars->mlx.img.line_len,
			&vars->mlx.img.endian);
	return (1);
}

int	frame_rendering(t_vars *vars)
{
	move_player(vars);
	door_animation(vars);
	render_scene(vars);
	render_sprites(vars);
	render_minimap(vars);
	mlx_clear_window(vars->mlx.mlx, vars->mlx.win);
	mlx_put_image_to_window(vars->mlx.mlx, vars->mlx.win,
		vars->mlx.img.img, 0, 0);
	return (1);
}
