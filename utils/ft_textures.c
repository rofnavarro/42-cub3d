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

int	ft_apply_shade(t_rays *rays, int color)
{
	if (rays->intersection == 0)
		return ((int)(((color & RED) >> 16) * SHADE
			+ ((BLACK & RED) >> 16) * (1 - SHADE)) << 16
			| (int)(((color & GREEN) >> 8) * SHADE
			+ ((BLACK & GREEN) >> 8) * (1 - SHADE)) << 8
			| (int)((color & BLUE) * SHADE
			+ (BLACK & BLUE) * (1 - SHADE)));
}
