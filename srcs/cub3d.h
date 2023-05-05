/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sciftci <sciftci@student.42kocaeli.com.tr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 11:43:14 by hel-makh          #+#    #+#             */
/*   Updated: 2023/05/05 19:37:26 by sciftci          ###   ########.fr       */
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

/**********************[ Sound Effects ]**********************/
# define DOOR_OPEN		"bonus/sound/door_open.wav"
# define DOOR_CLOSE		"bonus/sound/door_close.wav"
# define COIN_COLLECT	"bonus/sound/coin_collect.wav"

/************************[ Components ]***********************/
# define SPACE			' '
# define EMPTY_SPACE	'0'
# define WALL			'1'
# define C_DOOR			'2'
# define O_DOOR			'3'
# define P_NORTH		'N'
# define P_SOUTH		'S'
# define P_EAST			'E'
# define P_WEST			'W'
# define COLLECTIBLE	'C'
# define HIT_WALLS		"123"
# define WALLS			"12"
# define DOORS			"23"

/**********************[ Configuration ]**********************/
# if defined(__linux__)

enum e_keycodes {
	KEY_ESC = 65307,
	KEY_A = 97,
	KEY_W = 119,
	KEY_D = 100,
	KEY_S = 115,
	KEY_E = 101,
	KEY_LEFT = 65361,
	KEY_UP = 65362,
	KEY_RIGHT = 65363,
	KEY_DOWN = 65364
};

# elif defined(__APPLE__) && defined(__MACH__)

enum e_keycodes {
	KEY_ESC = 53,
	KEY_A = 0,
	KEY_W = 13,
	KEY_D = 2,
	KEY_S = 1,
	KEY_E = 14,
	KEY_F = 3,
	KEY_Q = 12,
	KEY_LEFT = 123,
	KEY_UP = 126,
	KEY_RIGHT = 124,
	KEY_DOWN = 125
};

# endif

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
typedef struct s_circle {
	double	x;
	double	y;
	double	radius;
}	t_circle;

typedef struct s_dim {
	double	width;
	double	height;
}	t_dim;

typedef struct s_coor {
	double	x;
	double	y;
}	t_coor;

typedef struct s_obj {
	int				x;
	int				y;
	double			frame;
}	t_obj;

typedef struct s_content {
	int	wall;
	int	player;
}	t_content;

typedef struct s_render {
	double			degree;
	double			angle;
	t_coor			hit_wall;
	int				direc;
	double			dist;
	t_dim			wall_dim;
	double			wall_orig_height;
	int				ty;
}	t_render;

struct s_list
{
    void *strct;
    struct s_list *next;
}typedef t_list;

typedef struct s_rend_spr {
	t_coor	sc;
	t_coor	col;
	t_coor	tex;
	t_dim	spr;
}	t_rend_spr;

typedef struct s_player {
	t_coor	pos;
	double	angle;
	t_coor	dir;
	t_coor move;
	double	rotate;
}	t_player;

typedef struct s_img {
	void	*img;
	int		*data;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_spr {
	t_img	*img;
	int		frames;
}	t_spr;

typedef struct s_map {
	char	**map;
	int		ce_color;
	int		fl_color;
	t_img	north;
	t_img	south;
	t_img	west;
	t_img	east;
	t_spr	collectible;
	//t_col	*collectibles;
	t_list   *collectibles;
	t_spr	door;
	//t_door	*doors;
	t_list	*doors;
	t_coor	spr;
	double	depth[WIDTH];
}	t_map;

typedef struct s_mlx {
	void	*mlx;
	void	*win;
	t_img	img;
	int		fps;
	double	fspeed;
}	t_mlx;

typedef struct s_vars {
	t_mlx		mlx;
	t_map		map;
	t_player	player;
}	t_vars;

/**************************[ Utils ]**************************/
long		ft_get_current_time(void);
int			ft_create_trgb(int t, int r, int g, int b);
double		ft_get_distance(t_coor poin1, t_coor point2);
int			ft_is_in_circle(double x, double y, t_circle circle);
double		ft_rtod(double radian);
double		ft_dtor(double degree);
double		ft_radian_operations(double radian, double amout);
void		ft_play_sound(char *path);

//int			ft_collectible_frame(t_obj *lst, int x, int y);

int			ft_door_frame(t_list *lst, int x, int y);

/*************************[ Parsing ]*************************/
int			ft_import_map(t_vars *vars, char *file);
int			ft_parse_textures(t_vars *vars, int fd);
int			ft_get_textures(t_vars *vars, char **info);
int			ft_parse_map(t_map *map, int fd);
int			ft_component_surroundings(char **map, int i, int j);

/************************[ Movements ]************************/
void		ft_get_player_position(t_vars *vars);
int			key_press(int keycode, t_vars *vars);
int			key_release(int keycode, t_vars *vars);
int			mouse_rotation(int x, int y, t_vars *vars);
void		ft_move_player(t_vars *vars);

/************************[ Rendering ]************************/
int			ft_init_images(t_vars *vars);
t_coor		ft_get_hit_wall(t_vars *vars, t_coor start_pos,
				double angle, int *direction);
int			frame_rendering(t_vars *vars);
void		ft_render_minimap(t_vars *vars);
void		ft_draw_rays(t_vars *vars, t_circle minimap);
void		ft_render_3d_scene(t_vars *vars);
void		ft_render_sprites(t_vars *vars);
void		ft_draw_floor_ceilling(t_vars *vars);
void		ft_door_animation(t_vars *vars);
void		ft_open_close_door(t_vars *vars);

/**************************[ Other ]**************************/
int			ft_exit_game(t_vars *vars, int exit_status);


t_obj	*ft_obj_new(int x, int y, int frame);
t_render	*ft_render_new(void);

t_list	*list_new(void *strct);
void	list_add_front(t_list **lst, t_list *new);
void	list_clear(t_list **lst);
void	list_remove(t_list **lst, int x, int y);

#endif