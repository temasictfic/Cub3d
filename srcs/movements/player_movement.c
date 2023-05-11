/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sciftci <sciftci@student.42kocaeli.com.tr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 04:14:09 by sciftci           #+#    #+#             */
/*   Updated: 2023/05/11 18:37:17 by sciftci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	mouse_rotation(int x, int y, t_vars *vars)
{
	double	diff;

	(void)y;
	diff = x - (WIDTH / 2);
	vars->player.angle = rad_op(vars->player.angle, (diff / 360.0));
	mlx_mouse_move(vars->mlx.win, WIDTH / 2, HEIGHT / 2);
	return (0);
}

static void	get_player_direction(t_vars *vars)
{
	double	direction_angle;

	if (vars->player.rotate)
		vars->player.angle = rad_op(vars->player.angle,
				vars->player.rotate * DEG_INC);
	direction_angle = vars->player.angle;
	if (vars->player.move.y == -1)
		direction_angle = rad_op(direction_angle, M_PI);
	else if (vars->player.move.x)
		direction_angle = rad_op(direction_angle,
				-vars->player.move.x * M_PI_2);
	if (vars->player.move.x && vars->player.move.y)
		direction_angle = rad_op(direction_angle,
				vars->player.move.x * M_PI_4);
	vars->player.dir.x = cos(direction_angle);
	vars->player.dir.y = sin(direction_angle);
}

void	move_player(t_vars *vars)
{
	t_coor	new_pos;

	get_player_direction(vars);
	if (!(int)vars->player.move.x && !(int)vars->player.move.y)
		return ;
	new_pos.x = vars->player.pos.x + vars->player.dir.x * STEP;
	if (!ft_strchr(WALLS,
			vars->map.map[(int)vars->player.pos.y][(int)new_pos.x]))
		vars->player.pos.x = new_pos.x;
	new_pos.y = vars->player.pos.y + vars->player.dir.y * STEP;
	if (!ft_strchr(WALLS,
			vars->map.map[(int)new_pos.y][(int)vars->player.pos.x]))
		vars->player.pos.y = new_pos.y;
	if (vars->map.map[(int)vars->player.pos.y][(int)vars->player.pos.x]
			== COLLECTIBLE)
	{
		vars->map.map[(int)vars->player.pos.y][(int)vars->player.pos.x]
			= EMPTY_SPACE;
		list_remove(&vars->map.collectibles, vars->player.pos.x,
			vars->player.pos.y);
	}
}

int	key_press(int keycode, t_vars *vars)
{
	if (keycode == KEY_A)
		vars->player.move.x = -1;
	else if (keycode == KEY_D)
		vars->player.move.x = 1;
	else if (keycode == KEY_W)
		vars->player.move.y = -1;
	else if (keycode == KEY_S)
		vars->player.move.y = 1;
	else if (keycode == KEY_Q)
		vars->player.rotate = -1;
	else if (keycode == KEY_E)
		vars->player.rotate = 1;
	else if (keycode == KEY_F)
		open_close_door(vars);
	else if (keycode == KEY_ESC)
		exit_game(vars, EXIT_SUCCESS);
	return (0);
}

int	key_release(int keycode, t_vars *vars)
{
	if (keycode == KEY_A || keycode == KEY_D)
		vars->player.move.x = 0;
	else if (keycode == KEY_W || keycode == KEY_S)
		vars->player.move.y = 0;
	else if (keycode == KEY_Q || keycode == KEY_E)
		vars->player.rotate = 0;
	return (0);
}
