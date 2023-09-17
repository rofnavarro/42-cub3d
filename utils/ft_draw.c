/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 21:42:23 by rferrero          #+#    #+#             */
/*   Updated: 2023/09/17 03:07:34 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_img_pix_put(t_img *img, int x, int y, int color)
{
	char	*pixel;

	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)pixel = color;
}

static void	render_background(t_img *img, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < WIN_H)
	{
		j = 0;
		while (j < WIN_W)
			ft_img_pix_put(img, j++, i, 0xFFFFFF);
		i++;
	}
}

static void	render_rect(t_img *img, t_rect rect)
{
	int	i;
	int	j;

	i = rect.y;
	while (i < rect.y + rect.height)
	{
		j = rect.x;
		while (j < rect.x + rect.width)
			ft_img_pix_put(img, j++, i, rect.color);
		++i;
	}
}

static void	render_minimap(t_game *game)
{
	int		i;
	int		j;
	int		z;
	t_rect	rect;

	i = 0;
	while (game->map.map[i])
	{
		j = 0;
		while (game->map.map[i][j])
		{
			rect.x = (i * 10) + 1;
			rect.y = (j * 10) + 1;
			rect.width = 10;
			rect.height = 10;
			if (game->map.map[i][j] == ' ' || game->map.map[i][j] == '1')
				rect.color = 0x000000;
			else
				rect.color = 0x808080;
			render_rect(&game->img, rect);
			j++;
		}
		i++;
	}
}

static void	render_player(t_game *game)
{
	int	i;
	int	j;

	i = (game->player.position.y * 2);
	while (i < ((game->player.position.y + 2) * 2))
	{
		j = ((game->player.position.x) * 2);
		while (j < ((game->player.position.x + 2)) * 2)
			ft_img_pix_put(&game->img, j++, i, 0x0000FF);
		++i;
	}
}

int	ft_draw_handler(t_game *game)
{
	render_minimap(game);
	render_background(&game->img, 0xFFFFFF);
	render_player(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.mlx_img, 0, 0);
	return (EXIT_SUCCESS);
}
