/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render_3d_scene.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sciftci <sciftci@student.42kocaeli.com.tr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 11:04:10 by hel-makh          #+#    #+#             */
/*   Updated: 2023/05/05 23:12:41 by sciftci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

#define DEG_INC	0.06

static int
	ft_get_texture_pixel(t_img img, t_render *render)
{
	int		tx;
	int		ty;
	double	ty_step;
	double	ty_off;

	if (render->direc == 'h')
		tx = img.width * (render->hit_wall.x - (int)render->hit_wall.x);
	else
		tx = img.width * (render->hit_wall.y - (int)render->hit_wall.y);
	ty_step = img.height / render->wall_orig_height;
	ty_off = 0;
	if (render->wall_orig_height > HEIGHT)
		ty_off = (render->wall_orig_height - HEIGHT) / 2;
	ty = (ty_off * ty_step) + ((render->ty - 1) * ty_step);
	return (img.data[abs(ty) * img.width + abs(tx)]);
}

static void
	ft_draw_pixel(t_vars *vars, t_render *render, int x, int y)
{
	t_img	*img;
	int		color;

	if (ft_strchr(DOORS, vars->map.map[(int)render->hit_wall.y]
			[(int)render->hit_wall.x]))
		img = &vars->map.door.img[ft_door_frame(vars->map.doors,
				render->hit_wall.x, render->hit_wall.y)];
	else if (render->direc == 'h' && render->angle < M_PI)
		img = &vars->map.north;
	else if (render->direc == 'h' && render->angle < 2 * M_PI)
		img = &vars->map.south;
	else if (render->direc == 'v'
		&& (render->angle < M_PI_2 || render->angle > M_PI + M_PI_2))
		img = &vars->map.west;
	else
		img = &vars->map.east;
	color = ft_get_texture_pixel(*img, render);
	if (color != create_trgb(255, 0, 0, 0))
		vars->mlx.img.data[y * WIDTH + x] = color;
	if (ft_strchr(WALLS, vars->map.map[(int)render->hit_wall.y]
			[(int)render->hit_wall.x]))
		vars->map.depth[x] = render->dist;
}

static void	ft_draw_walls(t_vars *vars, t_list *scene)
{
	int	x;
	int	y;
	t_render *render;

	while (scene)
	{
		render = scene->strct;
		render->ty = 0;
		y = (HEIGHT / 2) - (render->wall_dim.height / 2);
		while (y < (HEIGHT / 2) - (render->wall_dim.height / 2)
			+ render->wall_dim.height && y < HEIGHT)
		{
			x = (render->degree / DEG_INC) * render->wall_dim.width;
			while (x < ((render->degree / DEG_INC) * render->wall_dim.width)
				+ render->wall_dim.width && x < WIDTH)
			{
				ft_draw_pixel(vars, render, x, y);
				x ++;
			}
			(render->ty)++;
			y ++;
		}
		scene = scene->next;
	}
}

static void	ft_get_wall_dims(t_vars *vars, t_render *render,
	t_coor start_pos, double degree)
{
	render->degree = degree;
	render->hit_wall = ft_get_hit_wall(vars, start_pos,
			render->angle, &render->direc);
	render->dist = get_distance(vars->player.pos, render->hit_wall)
		* cos(radian_operations(vars->player.angle, -render->angle));
	render->wall_dim.width = WIDTH / (FOV / DEG_INC);
	render->wall_dim.height = HEIGHT;
	if (render->dist > 0)
		render->wall_dim.height = HEIGHT / render->dist;
	render->wall_orig_height = render->wall_dim.height;
	if (render->wall_dim.height > HEIGHT)
		render->wall_dim.height = HEIGHT;
}

void	ft_render_3d_scene(t_vars *vars)
{
	t_render	*temp;
	t_list		*scene;
	double		degree;

	ft_draw_floor_ceilling(vars);
	scene = NULL;
	degree = 0;
	while (degree <= FOV)
	{
		while (!scene|| (scene && vars->map.map[(int)((t_render *)(scene->strct))->hit_wall.y][(int)((t_render *)(scene->strct))->hit_wall.x] != WALL))
		{
			temp = ft_render_new();
			temp->angle = radian_operations(vars->player.angle,
					deg_to_rad(degree - (FOV / 2)));
			if (!scene)
				ft_get_wall_dims(vars, temp, vars->player.pos, degree);		
			else
				ft_get_wall_dims(vars, temp, ((t_render *)(scene->strct))->hit_wall, degree);								
			list_add_front(&scene, list_new(temp));
		}
		ft_draw_walls(vars, scene);
		list_clear(&scene);
		degree += DEG_INC;
	}
}
