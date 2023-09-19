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

CC						=				cc
CCFLAGS					=				-Wall -Werror -Wextra

LIBFT_PATH				=				./libft
LIBFT					=				$(LIBFT_PATH)/libft.a

LIBX					=				-lmlx -lX11 -lXext -lm

RM						=				rm -rf

SRC						=				cub3d.c \
										$(addprefix utils/, ft_class.c \
															ft_config_validation.c \
															ft_draw.c \
															ft_draw_background.c \
										 					ft_finish.c \
															ft_handle_keypress.c \
															ft_map_validation.c \
															ft_math.c \
															ft_matrix.c \
															ft_movement.c \
															ft_player.c \
															ft_preparation.c \
															ft_read_map.c \
															)

OBJ						=				$(SRC:%.c=%.o)

all:					$(NAME)

$(NAME):				$(OBJ)
						$(MAKE) -C $(LIBFT_PATH)
						$(CC) $(CCFLAGS) $(OBJ) $(LIBFT) $(LIBX) -o $(NAME)

clean:
						$(MAKE) -C $(LIBFT_PATH) clean
						$(RM) $(OBJ)

fclean:					clean
						$(MAKE) -C $(LIBFT_PATH) fclean
						$(RM) $(NAME)

re:						fclean all

.PHONY:					all clean fclean re