/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 21:42:23 by rferrero          #+#    #+#             */
/*   Updated: 2023/09/18 17:38:14 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	render_background(t_img *img, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < WIN_H)
	{
		j = 0;
		while (j < WIN_W)
			ft_img_pix_put(img, j++, i, color);
		i++;
	}
}

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
	render_background(&game->img, 0x000000);
	if (game->map.toggle == 0)
	{
		render_minimap(game);
		render_player(game);
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img.mlx_img, 0, 0);
	return (EXIT_SUCCESS);
}
