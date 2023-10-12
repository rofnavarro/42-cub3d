/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_textures.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinacio <rinacio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 16:02:37 by rinacio           #+#    #+#             */
/*   Updated: 2023/09/19 17:50:49 by rinacio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_load_textures(t_game *game)
{
	int		i;
	int		j;
	t_img	img;

	i = -1;
	while (++i < 4)
	{
		img.mlx_img = mlx_xpm_file_to_image(game->mlx,
				game->map.textures[i], &img.w, &img.h);
		if (!img.mlx_img)
			ft_validation_exit(game, "Error loading the texture.\n");
		img.addr = (int *)mlx_get_data_addr(img.mlx_img, &img.bpp,
				&img.line_len, &img.endian);
		j = -1;
		while (++j < 4096)
			game->map.walls[i][j] = img.addr[j];
		mlx_destroy_image(game->mlx, img.mlx_img);
	}
}

void	ft_get_pix_color(t_game *game, t_rays *rays, t_point tex)
{
	rays->color = game->map.walls[rays->texture]
	[((int)tex.y * 64 + (int)tex.x)];
	if (rays->intersection == 0)
		rays->color = (int)(((rays->color & RED) >> 16) * SHADE
				+ ((BLACK & RED) >> 16) * (1 - SHADE)) << 16
			| (int)(((rays->color & GREEN) >> 8) * SHADE
				+ ((BLACK & GREEN) >> 8) * (1 - SHADE)) << 8
			| (int)((rays->color & BLUE) * SHADE
				+ (BLACK & BLUE) * (1 - SHADE));
}

int	ft_choose_texture(t_game *game, t_rays *rays)
{
	int	wall;

	if (rays->intersection && rays->angle < PI
		&& game->player.position.y > rays->wall.y)
		wall = NO;
	else if (rays->intersection)
		wall = SO;
	else if (!rays->intersection && rays->angle > PI_2
		&& rays->angle < 3 * PI_2 && game->player.position.x > rays->wall.x)
		wall = WE;
	else if (!rays->intersection)
		wall = EA;
	return (wall);
}
