/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minimap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 16:34:27 by rferrero          #+#    #+#             */
/*   Updated: 2023/09/12 16:55:46 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_screen_pixel_put(t_screen *screen, int x, int y, int color)
{
	char	*pixel;

	pixel = (screen->addr + ((y * screen->line_len) + (x * (screen->bpp / 8))));
	*(int *)pixel = color;
}

int	ft_draw_minimap_handler(t_game *game)
{


	return (EXIT_SUCCESS);
}
