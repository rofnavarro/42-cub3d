/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinacio <rinacio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 13:29:03 by rferrero          #+#    #+#             */
/*   Updated: 2023/09/12 16:31:07 by rinacio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

//	math
# include <math.h>
//	open()
# include <fcntl.h>
//	close(), read(), write()
# include <unistd.h>
//	printf(), perror()
# include <stdio.h>
//	malloc(), free(), exit()
# include <stdlib.h>
//	strerror()
# include <string.h>
//	minilibX
# include <mlx.h>
//	libft
# include "./libft/libft.h"

//	defines
# define WIN_W	1024
# define WIN_H	512

//	structs
typedef struct s_player
{
	float	x;
	float	y;
	float	dx;
	float	dy;
	float	angle;
	char	direction;
}	t_player;

typedef struct s_map
{
	int		x;
	int		y;
	char	**config;
	char	**map;
	char	**textures;
	int		*floor_color;
	int		*ceiling_color;
}	t_map;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_player	player;
	t_map		map;
}	t_game;

typedef enum e_direction
{
	NO,
	SO,
	EA,
	WE
}	t_direction;

//	utils/ft_finish.c
void	ft_finish(t_game *game);
//	utils/ft_map_validation.c
void	ft_check_characters(t_game *game);
void	ft_map_is_closed(t_game *game);
//	utils/ft_matrix.c
void	ft_free_matrix(char **matrix);
int		ft_matrix_size(char **matrix);
char	**ft_matrix_calloc(int size);
int		ft_is_numeric(char **matrix);
//	utils/ft_player.c
void	ft_player_position(t_player *player, char **map);
void	ft_player_to_zero(t_player *player, char **map);
void	ft_player_to_direction(t_player *player, char **map);
//	utils/ft_preparation.c
void	ft_map_validation(t_game *game);
void	ft_preparation(t_game *game, int argc, char **argv);
//	utils/ft_read_map.c
char	*ft_read_map(t_game *game, char argv[]);
char	**ft_map_config(char **matrix);
char	**ft_map_map(char **matrix);
// utils/ft_config_validation.c
void	ft_config_validation(t_game *game);
void	ft_get_map_config(t_game *game, char **line);
void	ft_check_valid_texture_path(t_game *game, char **path);
void	ft_check_rgb(t_game *game, char **rgb, int *color);
void	ft_populate_path_array(t_game *game, char **line, int i);
// utils/ft_exit.c
void	ft_validation_exit(t_game *game, char *msg);

#endif