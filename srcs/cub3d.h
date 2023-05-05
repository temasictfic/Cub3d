/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sciftci <sciftci@student.42kocaeli.com.tr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 11:43:14 by hel-makh          #+#    #+#             */
/*   Updated: 2023/05/06 00:20:29 by sciftci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include <errno.h>
# include <sys/time.h>
# include "../libft/libft.h"
# include "../mlx_macos/mlx.h"

# define USAGE			"Usage: ./cub3d <file.cub>"
# define DEG_INC	0.06

/************************[ Components ]***********************/
# define SPACE			' '
# define EMPTY_SPACE	'0'
# define WALL			'1'
# define C_DOOR			'2' //Closed door
# define O_DOOR			'3' //Open door
# define P_NORTH		'N'
# define P_SOUTH		'S'
# define P_EAST			'E'
# define P_WEST			'W'
# define COLLECTIBLE	'C'
# define HIT_WALLS		"123"
# define WALLS			"12"
# define DOORS			"23"

/**********************[ Events ]**********************/
# define EVENT_ON_KEYDOWN 2
# define EVENT_ON_KEYUP 3
# define EVENT_ON_MOUSEMOVE 6
# define EVENT_ON_DESTROY 17
# define NO_MASK 0

/**********************[ Configuration ]**********************/

enum e_keycodes {
	KEY_ESC = 53,
	KEY_A = 0,
	KEY_W = 13,
	KEY_D = 2,
	KEY_S = 1,
	KEY_E = 14,
	KEY_F = 3,
	KEY_Q = 12,
};

enum e_window {
	WIDTH = 850,
	HEIGHT = 500,
	FPS_X = 5,
	FPS_Y = 15
};

enum e_minimap {
	BORDER = 10,
	RADIUS = 60,
	CENTER = BORDER + RADIUS,
	C_VISIBLE = 10,
	C_SIDE_LEN = (RADIUS * 2) / C_VISIBLE,
	PL_RADIUS = 2
};

enum e_player {
	SPEED = 4,
	ROT_SPEED = 3,
	MOUSE_ROT_SPEED = 5,
	FOV	= 75
};

/************************[ Structers ]************************/
//24
typedef struct s_circle {
	double	x;
	double	y;
	double	radius;
}	t_circle;

//16
typedef struct s_dim {
	double	width;
	double	height;
}	t_dim;

//16
typedef struct s_coor {
	double	x;
	double	y;
}	t_coor;

//16
typedef struct s_obj {
	int				x;
	int				y;
	double			frame;
}	t_obj;

//8
typedef struct s_content {
	int	wall;
	int	player;
}	t_content;

//80
typedef struct s_render {
	double			degree;
	double			angle;
	t_coor			hit_wall;
	t_dim			wall_dim;
	double			dist;
	double			wall_orig_height;
	int				direc;
	int				ty;
}	t_render;

//16
typedef struct s_list
{
    void *strct;
    struct s_list *next;
} t_list;

//64
typedef struct s_rend_spr {
	t_coor	sc;
	t_coor	col;
	t_coor	tex;
	t_dim	spr;
}	t_rend_spr;

//64
typedef struct s_player {
	t_coor	pos;
	t_coor	dir;
	t_coor move;
	double	angle;
	double	rotate;
}	t_player;

//40
typedef struct s_img {
	void	*img;
	int		*data;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_img;

//16
typedef struct s_spr {
	t_img	*img;
	int		frames;
}	t_spr;

//240 + depth
typedef struct s_map {
	t_img	north;
	t_img	south;
	t_img	west;
	t_img	east;
	t_coor	spr;
	t_spr	collectible;
	t_spr	door;
	t_list   *collectibles;
	t_list	*doors;
	char	**map;
	int		ce_color;
	int		fl_color;
	double	depth[WIDTH];
}	t_map;

//72
typedef struct s_mlx {
	t_img	img;
	void	*mlx;
	void	*win;
	double	fspeed;
	int		fps;
}	t_mlx;

typedef struct s_vars {
	t_map		map;
	t_mlx		mlx;
	t_player	player;
}	t_vars;

/**************************[ Utils ]**************************/
int			create_trgb(int t, int r, int g, int b);
double		get_distance(t_coor poin1, t_coor point2);
int			is_in_circle(double x, double y, t_circle circle);
double		deg_to_rad(double degree);
double		radian_operations(double radian, double amout);


int			door_frame(t_list *lst, int x, int y);

/*************************[ Parsing ]*************************/
int			import_map(t_vars *vars, char *file);
int			parse_textures(t_vars *vars, int fd);
int			get_textures(t_vars *vars, char **info);
int			parse_map(t_map *map, int fd);
int			component_surroundings(char **map, int i, int j);

/************************[ Movements ]************************/
void		get_player_position(t_vars *vars);
int			key_press(int keycode, t_vars *vars);
int			key_release(int keycode, t_vars *vars);
int			mouse_rotation(int x, int y, t_vars *vars);
void		move_player(t_vars *vars);

/************************[ Rendering ]************************/
int			init_images(t_vars *vars);
t_coor		get_hit_wall(t_vars *vars, t_coor start_pos,
				double angle, int *direction);
int			frame_rendering(t_vars *vars);
void		render_minimap(t_vars *vars);
void		draw_rays(t_vars *vars, t_circle minimap);
void		render_scene(t_vars *vars);
void		render_sprites(t_vars *vars);
void		draw_floor_ceilling(t_vars *vars);
void		door_animation(t_vars *vars);
void		open_close_door(t_vars *vars);

/**************************[ Utils ]**************************/
int			exit_game(t_vars *vars, int exit_status);
t_obj	*obj_new(int x, int y, int frame);
t_list	*list_new(void *strct);
void	list_add_front(t_list **lst, t_list *new);
void	list_clear(t_list **lst);
void	list_remove(t_list **lst, int x, int y);

#endif