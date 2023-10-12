/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 13:29:03 by rferrero          #+#    #+#             */
/*   Updated: 2023/10/06 12:20:17 by rferrero         ###   ########.fr       */
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
# define WIN_W 1200
# define WIN_H 900

# define MINIMAP_TILE 8
# define MINIMAP_OFFSET 2
# define LINE_SIZE 8
# define N_RAYS 600

# define PI 3.14159265358979323846
# define PI_2 1.57079632679489661923
# define PI_4 0.78539816339744830962

# define ROT_SPEED 0.05F
# define SPEED 0.04F

//	structs
typedef struct s_img
{
	void	*mlx_img;
	//char	*addr;
	int		*addr;
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

typedef struct s_rays
{
	int		ray;
	int		depth;
	int		mp;
	float	angle;
	float	dist_h;
	float	dist_v;
	int		intersection;
	float	shade;
	t_point	map;
	t_point	start;
	t_point	end;
	t_point	wall;
}	t_rays;

typedef struct s_rect
{
	t_point	position;
	int		width;
	int		height;
	int		color;
}	t_rect;

typedef struct s_map
{
	t_point	location;
	char	**config;
	char	**map;
	char	**textures;
	int		*floor_color;
	int		*ceiling_color;
	int		toggle;
	int		walls[4][4096];
}	t_map;

typedef struct s_player
{
	t_point		position;
	t_point		displacement;
	float		angle;
	char		direction;
	int			size;
}	t_player;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_player	player;
	t_map		map;
	t_img		img;
}	t_game;

//	enums
typedef enum e_direction
{
	NO,
	SO,
	EA,
	WE
}	t_direction;

typedef enum e_key
{
	UP,
	DOWN,
	LEFT,
	RIGHT
}	t_key;

//	utils/ft_class.c
void		render_minimap(t_game *game);
void		render_player(t_game *game);
//	utils/ft_config_validation.c
void		ft_config_validation(t_game *game);
void		ft_get_map_config(t_game *game, char **line);
void		ft_check_valid_texture_path(t_game *game, char **path);
void		ft_check_rgb(t_game *game, char **rgb, int *color);
void		ft_populate_path_array(t_game *game, char **line, int i);
// utils/ft_draw_background.c
int			ft_convert_rgb(int *rgb);
void		ft_draw_background(t_game *game);
//	utils/ft_draw.c
void		ft_img_pix_put(t_img *img, int x, int y, int color);
void		render_rect(t_img *img, t_rect rect);
void		render_line(t_game *game, t_point start, t_point end, int color);
int			ft_draw_handler(t_game *game);
//	utils/ft_finish.c
int			ft_finish(t_game *game);
void		ft_validation_exit(t_game *game, char *msg);
//	utils/ft_handle_keypress.c
int			ft_handle_keypress(int keysym, t_game *game);
int			ft_handle_keyrelease(int keysym, t_game *game);
//	utils/ft_map_validation.c
void		ft_check_characters(t_game *game);
void		ft_map_is_closed(t_game *game);
//	utils/ft_math.c
float		ft_fix_angle(float a);
float		ft_distance(t_point a, t_point b, float angle);
float		ft_convert_distance(float distance_minimap);
//	utils/ft_matrix.c
void		ft_free_matrix(char **matrix);
int			ft_matrix_size(char **matrix);
char		**ft_matrix_calloc(int size);
int			ft_is_numeric(char **matrix);
int			ft_matrix_max_width(char **matrix);
//	utils/ft_movement_validation.c
void		is_valid_front(t_game *game, float angle);
void		is_valid_back(t_game *game, float angle);
void		is_valid_right(t_game *game, float angle);
void		is_valid_left(t_game *game, float angle);
//	utils/ft_movement.c
void		ft_move_player(t_game *game, int keysym);
void		ft_rotate_player(t_game *game, int keysym);
void		ft_update_player_position(t_game *game, float angle);
void		ft_displacement(t_game *game, float angle);
//	utils/ft_player.c
void		ft_player_position(t_player *player, char **map);
void		ft_player_to_zero(t_player *player, char **map);
void		ft_player_to_direction(t_player *player, char **map);
//	utils/ft_preparation.c
void		ft_map_validation(t_game *game);
void		ft_preparation(t_game *game, int argc, char **argv);
//	utils/ft_rays_check.c
void		ft_raycasting(t_game *game);
void		ft_calc_rays(t_game *game, t_rays *rays, t_point *final, char dir);
void		ft_calc_rays_3d(t_game *game, t_rays *rays, t_point *final, char dir);
void		ft_check_angles_h(t_rays *rays, t_point *zero);
void		ft_check_angles_h_3d(t_rays *rays, t_point *zero);
void		ft_check_angles_v_3d(t_rays *rays, t_point *zero);
int			ft_check_boundaries(t_game *game, t_rays *rays, t_point *zero);
void		ft_check_angles_v(t_rays *rays, t_point *zero);
void		ft_draw_minimap_raylines(t_game *game);
//	utils/ft_read_map.c
char		*ft_read_map(t_game *game, char argv[]);
char		**ft_map_config(char **matrix);
char		**ft_map_map(char **matrix);
//utils/ft_textures.c
void		ft_load_textures(t_game *game);

#endif