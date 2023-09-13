/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minimap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinacio <rinacio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 16:34:27 by rferrero          #+#    #+#             */
/*   Updated: 2023/09/13 16:26:57 by rinacio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_screen_pixel_put(t_img *img, int x, int y, int color)
{
	char	*pixel;

	pixel = (img->addr + ((y * img->line_len) + (x * (img->bpp / 8))));
	*(int *)pixel = color;
}


int	ft_draw_minimap_handler(t_game *game)
{


	return (EXIT_SUCCESS);
}
