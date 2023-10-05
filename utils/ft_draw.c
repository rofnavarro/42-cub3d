/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinacio <rinacio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 21:42:23 by rferrero          #+#    #+#             */
/*   Updated: 2023/09/29 19:18:59 by rinacio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_img_pix_put(t_img *img, int x, int y, int color)
{
	char	*pixel;

	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)pixel = color;
}

void	render_rect(t_img *img, t_rect rect)
{
	int	i;
	int	j;

	i = rect.position.y;
	while (i < rect.position.y + rect.height)
	{
		j = rect.position.x;
		while (j < rect.position.x + rect.width)
		{
			ft_img_pix_put(img, j, i, rect.color);
			j++;
		}
		++i;
	}
}

void	render_line(t_game *game, t_point start, t_point end, int color)
{
	t_point	delta;
	t_point	pixel;
	int		line;

	delta.x = end.x - start.x;
	delta.y = end.y - start.y;
	line = sqrt((delta.x * delta.x) + (delta.y * delta.y));
	delta.x /= line;
	delta.y /= line;
	pixel.x = start.x;
	pixel.y = start.y;
	while (line)
	{
		ft_img_pix_put(&game->img, pixel.x, pixel.y, color);
		pixel.x += delta.x;
		pixel.y += delta.y;
		line--;
	}
}

int	ft_draw_handler(t_game *game)
{
	ft_draw_background(game);
	ft_raycasting(game);
	if (game->map.toggle == 0)
	{
		render_minimap(game);
		render_player(game);
	}
	ft_draw_minimap_raylines(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.mlx_img, 0, 0);
	return (EXIT_SUCCESS);
}
