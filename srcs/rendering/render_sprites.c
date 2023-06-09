/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprites.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sciftci <sciftci@student.42kocaeli.com.tr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 04:11:48 by sciftci           #+#    #+#             */
/*   Updated: 2023/05/11 18:40:29 by sciftci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	collectibles_animation(t_vars *vars, t_obj *collectible)
{
	double	new_frame;

	new_frame = collectible->frame + C_FRAME;
	if ((int)new_frame < vars->map.collectible.frames)
		collectible->frame = new_frame;
	else
		collectible->frame = 0;
}

static int	is_visible(t_vars *vars, t_obj *holder, int x)
{
	t_coor	spr;

	spr.x = (double)holder->x + 0.5;
	spr.y = (double)holder->y + 0.5;
	if (get_dist(vars->player.pos, spr) < vars->map.depth[x])
		return (1);
	return (0);
}

static void	draw_sprite(t_vars *vars, t_rend_spr *rend, t_img *img,
						t_obj *holder)
{
	int	i;
	int	j;
	int	c;

	i = rend->sc.x;
	while (i < rend->sc.x + rend->spr.width && i < WIDTH)
	{
		j = rend->sc.y;
		while (i >= 0 && j < rend->sc.y + rend->spr.height && j < HEIGHT
			&& is_visible(vars, holder, i))
		{
			rend->tex.x = (i - rend->sc.x) * (img->width / rend->spr.width);
			rend->tex.y = (j - rend->sc.y) * (img->height / rend->spr.height);
			if (j >= 0 && rend->tex.x >= 0 && rend->tex.x < img->width
				&& rend->tex.y >= 0 && rend->tex.y < img->height)
			{
				c = img->data[(int)rend->tex.y * img->width + (int)rend->tex.x];
				if (c != create_trgb(255, 0, 0, 0))
					vars->mlx.img.data[j * WIDTH + i] = c;
			}
			j++;
		}
		i++;
	}
}

void	render_sprites(t_vars *vars)
{
	t_rend_spr	rend;
	t_list		*holder;
	t_obj		*obj;
	double		angle;

	holder = vars->map.collectibles;
	while (holder)
	{
		obj = holder->obj;
		collectibles_animation(vars, obj);
		rend.col.x = (double)obj->x + 0.5;
		rend.col.y = (double)obj->y + 0.5;
		rend.sc.x = vars->player.pos.x - rend.col.x;
		rend.sc.y = vars->player.pos.y - rend.col.y;
		angle = rad_op(vars->player.angle,
				rad(FOV / 2.0) - atan2(rend.sc.y, rend.sc.x));
		rend.spr.height = (HEIGHT / 2) / get_dist(vars->player.pos, rend.col);
		rend.spr.width = (HEIGHT / 2) / get_dist(vars->player.pos, rend.col);
		rend.sc.x = WIDTH - (angle * WIDTH / rad(FOV)) - (rend.spr.width
				/ 2);
		rend.sc.y = (HEIGHT / 2);
		draw_sprite(vars, &rend, &vars->map.collectible.img[(int)obj->frame],
			obj);
		holder = holder->next;
	}
}
