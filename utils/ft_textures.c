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

void	load_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		game->map.walls[i].mlx_img = mlx_xpm_file_to_image(game->mlx,
				game->map.textures[i], &game->map.walls[i].w,
				&game->map.walls[i].h);
		if (!game->map.walls[i].mlx_img)
			ft_validation_exit(game, "Error loading the texture.\n");
		game->map.walls[i].addr = mlx_get_data_addr(game->map.walls[i].mlx_img,
				&game->map.walls[i].bpp, &game->map.walls[i].line_len,
				&game->map.walls[i].endian);
		i++;
	}
	i = 0;
	while (i < 4)
	{
		if (game->map.walls[i].mlx_img)
			mlx_destroy_image(game->mlx, game->map.walls[i].mlx_img);
		i++;
	}
}
