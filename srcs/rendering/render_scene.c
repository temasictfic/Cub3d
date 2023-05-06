/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sciftci <sciftci@student.42kocaeli.com.tr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 04:11:58 by sciftci           #+#    #+#             */
/*   Updated: 2023/05/06 05:12:45 by sciftci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	get_texture_pixel(t_img img, t_rend *render)
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

static void	draw_pixel(t_vars *vars, t_rend *render, int x, int y)
{
	t_img	*img;
	int		color;

	if (ft_strchr(DOORS,
			vars->map.map[(int)render->hit_wall.y][(int)render->hit_wall.x]))
		img = &vars->map.door.img[door_frame(vars->map.doors,
				render->hit_wall.x, render->hit_wall.y)];
	else if (render->direc == 'h' && render->angle < M_PI)
		img = &vars->map.north;
	else if (render->direc == 'h' && render->angle < 2 * M_PI)
		img = &vars->map.south;
	else if (render->direc == 'v' && (render->angle < M_PI_2
			|| render->angle > M_PI + M_PI_2))
		img = &vars->map.west;
	else
		img = &vars->map.east;
	color = get_texture_pixel(*img, render);
	if (color != create_trgb(255, 0, 0, 0))
		vars->mlx.img.data[y * WIDTH + x] = color;
	if (ft_strchr(WALLS,
			vars->map.map[(int)render->hit_wall.y][(int)render->hit_wall.x]))
		vars->map.depth[x] = render->dist;
}

static void	draw_walls(t_vars *vars, t_list *scene)
{
	int			x;
	int			y;
	t_rend		*render;

	while (scene)
	{
		render = scene->obj;
		render->ty = 0;
		y = (HEIGHT / 2) - (render->wall_dim.height / 2);
		while (y < (HEIGHT / 2) - (render->wall_dim.height / 2)
			+ render->wall_dim.height && y < HEIGHT)
		{
			x = (render->degree / DEG_INC) * render->wall_dim.width;
			while (x < ((render->degree / DEG_INC) * render->wall_dim.width)
				+ render->wall_dim.width && x < WIDTH)
			{
				draw_pixel(vars, render, x, y);
				x++;
			}
			(render->ty)++;
			y++;
		}
		scene = scene->next;
	}
}

static void	get_wall_dims(t_vars *vars, t_rend *render, t_coor start_pos,
		double degree)
{
	render->degree = degree;
	render->hit_wall = get_hit_wall(vars, start_pos, render->angle,
			&render->direc);
	render->dist = get_dist(vars->player.pos, render->hit_wall)
		* cos(rad_op(vars->player.angle, -render->angle));
	render->wall_dim.width = WIDTH / (FOV / DEG_INC);
	render->wall_dim.height = HEIGHT;
	if (render->dist > 0)
		render->wall_dim.height = HEIGHT / render->dist;
	render->wall_orig_height = render->wall_dim.height;
	if (render->wall_dim.height > HEIGHT)
		render->wall_dim.height = HEIGHT;
}

void	render_scene(t_vars *vars)
{
	t_rend		*r;
	t_list		*rend;
	double		deg;

	draw_floor_ceilling(vars);
	rend = NULL;
	deg = 0;
	while (deg <= FOV)
	{
		while (!rend || (rend
				&& vars->map.map[(int)((t_rend *)(rend->obj))->hit_wall.y]
				[(int)((t_rend *)(rend->obj))->hit_wall.x] != WALL))
		{
			r = malloc(1 * sizeof(t_rend));
			r->angle = rad_op(vars->player.angle, rad(deg - (FOV / 2)));
			if (!rend)
				get_wall_dims(vars, r, vars->player.pos, deg);
			else
				get_wall_dims(vars, r, ((t_rend *)(rend->obj))->hit_wall, deg);
			list_add_front(&rend, list_new(r));
		}
		draw_walls(vars, rend);
		list_clear(&rend);
		deg += DEG_INC;
	}
}
