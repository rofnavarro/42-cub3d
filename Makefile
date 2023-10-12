# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:     #
#                                                     +:+ +:+         +:+      #
#    By: rinacio <rinacio@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/05 13:15:28 by rferrero          #+#    #+#              #
#    Updated: 2023/09/12 17:05:19 by rinacio          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME					=				cub3D

NAME_BONUS				=				cub3D_bonus

CC						=				cc
CCFLAGS					=				-Wall -Werror -Wextra

LIBFT_PATH				=				./libft
LIBFT					=				$(LIBFT_PATH)/libft.a

LIBX					=				-lmlx -lX11 -lXext -lm

RM						=				rm -rf

SRC						=				cub3d.c \
										$(addprefix utils/, ft_class.c \
															ft_config_validation.c \
															ft_draw_background.c \
															ft_draw.c \
										 					ft_finish.c \
															ft_handle_keypress.c \
															ft_map_validation.c \
															ft_math.c \
															ft_matrix.c \
															ft_minimap.c \
															ft_movement_validation.c \
															ft_movement.c \
															ft_player.c \
															ft_preparation.c \
															ft_rays_check.c \
															ft_read_map.c \
															ft_textures.c \
															ft_walls.c \
															)

SRC_BONUS				=				bonus/cub3d.c \
										$(addprefix bonus/utils/, ft_class.c \
															ft_config_validation.c \
															ft_draw_background.c \
															ft_draw.c \
										 					ft_finish.c \
															ft_handle_keypress.c \
															ft_map_validation.c \
															ft_math.c \
															ft_matrix.c \
															ft_minimap.c \
															ft_movement_validation.c \
															ft_movement.c \
															ft_player.c \
															ft_preparation.c \
															ft_rays_check.c \
															ft_read_map.c \
															ft_textures.c \
															ft_walls.c \
															)

OBJ						=				$(SRC:%.c=%.o)

OBJ_BONUS				= 				$(SRC_BONUS:%.c=%.o)

all:					$(NAME)

$(NAME):				$(OBJ)
						$(MAKE) -C $(LIBFT_PATH)
						$(CC) $(CCFLAGS) $(OBJ) $(LIBFT) $(LIBX) -o $(NAME)

$(NAME_BONUS):			$(OBJ_BONUS)
						$(MAKE) -C $(LIBFT_PATH)
						$(CC) $(CCFLAGS) $(OBJ_BONUS) $(LIBFT) $(LIBX) -o $(NAME_BONUS)			

clean:
						$(MAKE) -C $(LIBFT_PATH) clean
						$(RM) $(OBJ) $(OBJ_BONUS)

fclean:					clean
						$(MAKE) -C $(LIBFT_PATH) fclean
						$(RM) $(NAME) $(NAME_BONUS)

bonus:					$(NAME_BONUS)

re:						fclean all

.PHONY:					all clean fclean re bonus