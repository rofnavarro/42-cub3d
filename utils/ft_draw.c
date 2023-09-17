/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 21:42:23 by rferrero          #+#    #+#             */
/*   Updated: 2023/09/16 23:51:51 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_img_pix_put(t_img *img, int x, int y, int color)
{
    char    *pixel;

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
		{
			ft_img_pix_put(img, j++, i, color);
		}
		i++;
	}
}

static void	render_player(t_game *game)
{
	int	i;
	int	j;

	i = (game->player.position.y * 5);
	while (i < ((game->player.position.y + 5) * 5))
	{
		j = (((game->player.position.x) - 1) * 5);
		while (++j < ((game->player.position.x + 5)) * 5)
			ft_img_pix_put(&game->img, j, i, 0x0000FF);
		++i;
	}
}

int	ft_draw_handler(t_game *game)
{
	render_background(&game->img, 0xFFFFFF);
	render_player(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.mlx_img, 0, 0);
	return (EXIT_SUCCESS);
}
