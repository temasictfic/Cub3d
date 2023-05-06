# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sciftci <sciftci@student.42kocaeli.com.tr> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/06 04:09:11 by sciftci           #+#    #+#              #
#    Updated: 2023/05/06 04:10:01 by sciftci          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -O3 -Ofast -flto -march=native#-O3 -Ofast -flto -march=native#-g -ggdb -fsanitize=address -fno-omit-frame-pointer -fsanitize=undefined 
RM = rm -f
NAME = cub3d
FILES	=			utils/utils.c\
					utils/list_fns.c\
					utils/exit_game.c\
					parsing/import_map.c\
					parsing/parse_textures.c\
					parsing/get_textures.c\
					parsing/parse_map.c\
					parsing/component_surroundings.c\
					movements/get_player_position.c\
					movements/player_movement.c\
					rendering/get_hit_wall.c\
					rendering/frame_rendering.c\
					rendering/door_opening.c\
					rendering/render_minimap.c\
					rendering/draw.c\
					rendering/render_scene.c\
					rendering/render_sprites.c\
					main.c\

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
					@$(CC) $(CFLAGS) -Ilibft -Imlx_macos -c $< -o $@

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
					
re:					libsclean fclean all

.PHONY:				all clean fclean libsclean re