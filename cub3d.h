/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 13:29:03 by rferrero          #+#    #+#             */
/*   Updated: 2023/09/07 21:11:11 by rferrero         ###   ########.fr       */
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
}	t_map;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_player	player;
	t_map		map;
}	t_game;

//	utils/ft_finish.c
void	ft_finish(t_game *game);
//	utils/ft_matrix.c
void	ft_free_matrix(char **matrix);
int		ft_matrix_size(char **matrix);
char	**ft_matrix_calloc(int size);
//	utils/ft_player.c
void	ft_player_position(t_player *player, char **map);
void	ft_player_to_zero(t_player *player, char **map);
void	ft_player_to_direction(t_player *player, char **map);
//	utils/ft_preparation.c
void	ft_preparation(t_game *game, int argc, char **argv);
//	utils/ft_read_map.c
char	*ft_read_map(t_game *game, char argv[]);
char	**ft_map_config(char **matrix);
char	**ft_map_map(char **matrix);

#endif