/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_background.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinacio <rinacio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 14:58:23 by rinacio           #+#    #+#             */
/*   Updated: 2023/09/19 16:49:38 by rinacio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_convert_rgb(int *rgb)
{
	int	color;

	return ((rgb[0] * 65536) + (rgb[1] * 256) + rgb[2]);
}

void	ft_draw_background(t_game *game)
{
	int	height;
	int	width;
	int	color;

	width = -1;
	while (++width < WIN_W)
	{
		height = -1;
		while (++height < WIN_H)
		{
			if (height < WIN_H / 2)
				color = ft_convert_rgb(game->map.ceiling_color);
			else
				color = ft_convert_rgb(game->map.floor_color);
			ft_img_pix_put(&game->img, width, height, color);
		}
	}
	load_textures(game);
}
