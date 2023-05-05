/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sciftci <sciftci@student.42kocaeli.com.tr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 11:49:49 by hel-makh          #+#    #+#             */
/*   Updated: 2023/05/06 00:24:49 by sciftci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_mlx(t_vars *vars)
{
	vars->mlx.win = NULL;
	vars->mlx.img.img = NULL;
	vars->mlx.fps = 0;
	vars->mlx.mlx = mlx_init();
	if (!vars->mlx.mlx)
	{
		printf("Error\nCouldn't initialize mlx.\n");
		exit(EXIT_FAILURE);
	}
}

static void	start_game(t_vars *vars)
{
	vars->mlx.win = mlx_new_window(vars->mlx.mlx, WIDTH, HEIGHT, "cub3d");
	if (!vars->mlx.win)
	{
		printf("Error\nCouldn't open window.\n");
		exit_game(vars, EXIT_FAILURE);
	}
	vars->player.move.x = 0;
	vars->player.move.y = 0;
	vars->player.rotate = 0;
	mlx_mouse_hide();
	mlx_hook(vars->mlx.win, EVENT_ON_KEYDOWN, NO_MASK, key_press, vars);
	mlx_hook(vars->mlx.win, EVENT_ON_KEYUP, NO_MASK, key_release, vars);
	mlx_hook(vars->mlx.win, EVENT_ON_MOUSEMOVE, NO_MASK, mouse_rotation, vars);
	mlx_hook(vars->mlx.win, EVENT_ON_DESTROY, NO_MASK, exit_game, vars);
	mlx_loop_hook(vars->mlx.mlx, frame_rendering, vars);
	mlx_loop(vars->mlx.mlx);
}

int	main(int argc, char **argv)
{
	t_vars	vars;

	if (argc < 2)
		return (printf("Error\nMissing map file.\n%s\n", USAGE), EXIT_FAILURE);
	else if (argc > 2)
		return (printf("Error\nInvalid arguments.\n%s\n", USAGE), EXIT_FAILURE);
	init_mlx(&vars);
	if (!import_map(&vars, argv[1]))
		exit_game(&vars, EXIT_FAILURE);
	if (!init_images(&vars))
		exit_game(&vars, EXIT_FAILURE);
	start_game(&vars);
	return (EXIT_SUCCESS);
}
