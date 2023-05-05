# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sciftci <sciftci@student.42kocaeli.com.tr> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/05 11:42:59 by hel-makh          #+#    #+#              #
#    Updated: 2023/05/05 19:36:38 by sciftci          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -ggdb#-O3 -Ofast -flto -march=native#-g -ggdb -fsanitize=address -fno-omit-frame-pointer -fsanitize=undefined 
RM = rm -f
#-O3 -Ofast -flto -march=native
NAME = cub3d
FILES	=			utils/ft_get_current_time.c\
					utils/ft_create_trgb.c\
					utils/ft_get_distance.c\
					utils/ft_is_in_circle.c\
					utils/ft_radian_degree.c\
					utils/ft_radian_operations.c\
					utils/ft_play_sound.c\
					utils/list_fns.c\
					parsing/ft_import_map.c\
					parsing/ft_parse_textures.c\
					parsing/ft_get_textures.c\
					parsing/ft_parse_map.c\
					parsing/ft_component_surroundings.c\
					movements/ft_get_player_position.c\
					movements/ft_player_movement.c\
					rendering/ft_get_hit_wall.c\
					rendering/ft_frame_rendering.c\
					rendering/ft_door_opening.c\
					rendering/ft_render_minimap.c\
					rendering/ft_draw_rays.c\
					rendering/ft_render_3d_scene.c\
					rendering/ft_render_sprites.c\
					rendering/ft_draw_floor_ceilling.c\
					other/ft_exit_game.c\
					main.c

SRCS_DIR		=	srcs/
SRCS			=	$(addprefix $(SRCS_DIR), $(FILES))

OBJS_DIR	=	objs/
OBJS		=	$(patsubst %.c, %.o, $(addprefix $(OBJS_DIR), $(FILES)))


LIBFT_DIR		=	./libft
LIBFT			=	$(LIBFT_DIR)/libft.a

MLX_DIR		=	mlx_macos
MLX			=	$(MLX_DIR)/libmlx.a
MLX_LFLAGS	=	-framework OpenGL -framework AppKit


$(OBJS_DIR)%.o:$(SRCS_DIR)%.c
					@mkdir -p $(shell dirname $@)
					@$(CC) $(CFLAGS) -ILibft -Imlx_macos -c $< -o $@

$(NAME):			$(OBJS) $(LIBFT) $(MLX)
					@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX) $(MLX_LFLAGS) -o $(NAME)
					@echo "Compiled cub3d"

all:				$(NAME)

$(LIBFT):
					make -C $(LIBFT_DIR)

$(MLX):
					make -C $(MLX_DIR)

clean:
					rm -rf $(OBJS_DIR)
					make clean -C $(LIBFT_DIR)

fclean:				clean
					rm -rf $(NAME)

libsclean:
					make fclean -C $(LIBFT_DIR)
					make clean -C $(MLX_DIR)
					
re:					fclean all

.PHONY:				all clean fclean libsclean re