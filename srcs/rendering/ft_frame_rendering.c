/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_frame_rendering.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sciftci <sciftci@student.42kocaeli.com.tr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 16:44:23 by hel-makh          #+#    #+#             */
/*   Updated: 2023/05/05 21:18:39 by sciftci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_init_images(t_vars *vars)
{
	vars->mlx.img.img = mlx_new_image(vars->mlx.mlx, WIDTH, HEIGHT);
	if (!vars->mlx.img.img)
		return (printf("Error\nCouldn't create images.\n"), 0);
	vars->mlx.img.data = (int *)mlx_get_data_addr(vars->mlx.img.img,
			&vars->mlx.img.bpp, &vars->mlx.img.line_len,
			&vars->mlx.img.endian);
	return (1);
}

// static void	ft_fps_counter(t_vars *vars)
// {
// 	static long	prev_timestamp;
// 	static long	counter;
// 	static int	frames;

// 	if (!prev_timestamp)
// 		prev_timestamp = ft_get_current_time();
// 	vars->mlx.fspeed = (ft_get_current_time() - prev_timestamp) / 1000.0;
// 	prev_timestamp = ft_get_current_time();
// 	if (!counter)
// 		counter = ft_get_current_time() + 1000;
// 	if (counter <= ft_get_current_time())
// 	{
// 		counter = ft_get_current_time() + 1000;
// 		vars->mlx.fps = frames;
// 		frames = 0;
// 	}
// 	frames ++;
// 	//dprintf(2, "%d $", vars->mlx.fps);
// 	dprintf(2, "%f $", vars->mlx.fspeed);
// }

int	frame_rendering(t_vars *vars)
{
	//char	*fps;

	//ft_fps_counter(vars);
	vars->mlx.fspeed = 0.045;
	vars->mlx.fps = 40;
	ft_move_player(vars);
	ft_door_animation(vars);
	ft_render_3d_scene(vars);
	ft_render_sprites(vars);
	ft_render_minimap(vars);
	mlx_clear_window(vars->mlx.mlx, vars->mlx.win);
	mlx_put_image_to_window(vars->mlx.mlx, vars->mlx.win,
		vars->mlx.img.img, 0, 0);
	// fps = ft_itoa(vars->mlx.fps);
	// mlx_string_put(vars->mlx.mlx, vars->mlx.win, FPS_X, FPS_Y,
	// 	ft_create_trgb(0, 0, 255, 0), fps);
	// fps = ft_free(fps);
	return (1);
}
