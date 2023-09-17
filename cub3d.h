/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 13:29:03 by rferrero          #+#    #+#             */
/*   Updated: 2023/09/16 22:15:41 by rferrero         ###   ########.fr       */
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
//	X11
# include <X11/keysym.h>
# include <X11/X.h>

//	defines
# define WIN_W	1024
# define WIN_H	512

# define PI	3.14159265358979323846

//	structs
typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		w;
	int		h;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_point
{
	float	x;
	float	y;
}	t_point;

typedef struct s_player
{
	t_point	position;
	t_point	displacement;
	float	angle;
	char	direction;
}	t_player;

typedef struct s_map
{
	t_point	location;
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
	t_img		img;
}	t_game;

typedef enum e_direction
{
	NO,
	SO,
	EA,
	WE
}	t_direction;

// utils/ft_config_validation.c
void	ft_config_validation(t_game *game);
void	ft_get_map_config(t_game *game, char **line);
void	ft_check_valid_texture_path(t_game *game, char **path);
void	ft_check_rgb(t_game *game, char **rgb, int *color);
void	ft_populate_path_array(t_game *game, char **line, int i);
//	utils/ft_draw.c
void	ft_img_pix_put(t_img *img, int x, int y, int color);
int		ft_draw_handler(t_game *game);
t_img	*ft_new_image(t_game *game, int width, int height);
//	utils/ft_finish.c
int		ft_finish(t_game *game);
// utils/ft_handle_keypress.c
int		ft_handle_keypress(int keysym, t_game *game);
void	ft_validation_exit(t_game *game, char *msg);
//	utils/ft_map_validation.c
void	ft_check_characters(t_game *game);
void	ft_map_is_closed(t_game *game);
//	utils/ft_math.c
float	ft_deg_to_rad(int deg);
int		ft_fix_angle(int angle);
float	ft_distance(t_point a, t_point b, float angle);
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

#endif