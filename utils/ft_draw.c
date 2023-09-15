/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 21:42:23 by rferrero          #+#    #+#             */
/*   Updated: 2023/09/14 23:37:44 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_img_pixel_put(t_img *img, int x, int y, int color)
{
	char	*pixel;
	int		i;

	i = img->bpp - 8;
	pixel = (img->addr + ((y * img->line_len) + (x * (img->bpp / 8))));
	while (i >= 0)
	{
		if (img->endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		else
			*pixel++ = (color >> (img->bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}

static int	render_background(t_img *img)
{
	int	i;
	int	j;

	i = 0;
	while (i < WIN_H)
	{
		j = -1;
		while (++j < WIN_W)
			ft_img_pixel_put(img->mlx_img, j, i, 0xFF0000);
		++i;
	}
	return (EXIT_SUCCESS);
}

static int	render_player(t_game *game)
{
	int	i;
	int	j;

	i = (game->player.position.y);
	while (i < ((game->player.position.y + 5)))
	{
		j = (game->player.position.x) - 1;
		while (++j < (game->player.position.x + 5))
			ft_img_pixel_put(game->img.mlx_img, j, i, 0xFFFFFF);
		++i;
	}
	return (EXIT_SUCCESS);
}

int	ft_draw_handler(t_game *game)
{
	t_img	*img;

	img = NULL;
	img->mlx_img = mlx_new_image(game->mlx, WIN_W, WIN_H);
	img->addr = mlx_get_data_addr(&img->mlx_img, &img->bpp, \
									&img->line_len, &img->endian);
	if (render_background(img) == EXIT_FAILURE)
		ft_validation_exit(game, "Fail to render background\n");
	// if (render_player(game) == EXIT_FAILURE)
	// 	ft_validation_exit(game, "Fail to render player\n");
	mlx_put_image_to_window(game->mlx, game->win, img->mlx_img, 0, 0);
	return (EXIT_SUCCESS);
}
