/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_opening.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sciftci <sciftci@student.42kocaeli.com.tr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 04:13:09 by sciftci           #+#    #+#             */
/*   Updated: 2023/05/11 18:40:09 by sciftci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	door_frame(t_list *lst, int x, int y)
{
	t_obj	*obj;

	while (lst)
	{
		obj = lst->obj;
		if (obj->x == x && obj->y == y)
			return ((int)obj->frame);
		lst = lst->next;
	}
	return (0);
}

void	door_animation(t_vars *vars)
{
	t_list	*holder;
	t_list	*next_holder;
	t_obj	*obj;
	double	new_frame;

	holder = vars->map.doors;
	while (holder)
	{
		obj = holder->obj;
		if (vars->map.map[obj->y][obj->x] == O_DOOR)
			new_frame = obj->frame + D_FRAME;
		else
			new_frame = obj->frame - D_FRAME;
		if ((int)new_frame < vars->map.door.frames)
			obj->frame = new_frame;
		if (obj->frame <= 0)
		{
			next_holder = holder->next;
			list_remove(&vars->map.doors, obj->x, obj->y);
			holder = next_holder;
			continue ;
		}
		holder = holder->next;
	}
}

void	open_close_door(t_vars *vars)
{
	t_coor	door;

	door = get_hit_wall(vars, vars->player.pos, vars->player.angle, NULL);
	if (!ft_strchr(DOORS, vars->map.map[(int)door.y][(int)door.x]))
		return ;
	door.x = (double)((int)door.x) + 0.5;
	door.y = (double)((int)door.y) + 0.5;
	if (get_dist(vars->player.pos, door) > 2.0)
		return ;
	if (vars->map.map[(int)door.y][(int)door.x] == C_DOOR
		&& door_frame(vars->map.doors, door.x, door.y) == 0)
	{
		list_add_front(&vars->map.doors, list_new(obj_new(door.x, door.y, 0)));
		vars->map.map[(int)door.y][(int)door.x] = O_DOOR;
	}
	else if (vars->map.map[(int)door.y][(int)door.x] == O_DOOR
			&& door_frame(vars->map.doors, door.x,
				door.y) == vars->map.door.frames - 1)
	{
		vars->map.map[(int)door.y][(int)door.x] = C_DOOR;
	}
}
