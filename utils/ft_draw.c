/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 21:42:23 by rferrero          #+#    #+#             */
/*   Updated: 2023/09/16 22:16:36 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_img_pix_put(t_img *img, int x, int y, int color)
{
	char    *pixel;
	int		i;

	i = img->bpp - 8;
    pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	while (i >= 0)
	{
		/* big endian, MSB is the leftmost bit */
		if (img->endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		/* little endian, LSB is the leftmost bit */
		else
			*pixel++ = (color >> (img->bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}

void	render_background(t_img *img, int color)
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
		++i;
	}
}

// static int	render_player(t_game *game, t_img *img)
// {
// 	int	i;
// 	int	j;

// 	i = (game->player.position.y);
// 	while (i < ((game->player.position.y + 5)))
// 	{
// 		j = (game->player.position.x) - 1;
// 		while (++j < (game->player.position.x + 5))
// 			ft_img_pixel_put(img->mlx_img, j, i, 0xFFFFFF);
// 		++i;
// 	}
// 	return (EXIT_SUCCESS);
// }

int	ft_draw_handler(t_game *game)
{
	render_background(&game->img, 0xFFFFFF);
	// if (render_player(game, img) == EXIT_FAILURE)
	// 	ft_validation_exit(game, "Fail to render player\n");
	mlx_put_image_to_window(game->mlx, game->win, game->img.mlx_img, 0, 0);
	return (EXIT_SUCCESS);
}

t_img	*ft_new_image(t_game *game, int width, int height)
{
	t_img	*ret;

	ret = (t_img *)malloc(sizeof(t_img));
	if (!ret)
		return (NULL);
	ret->w = width;
	ret->h = height;
	ret->mlx_img = mlx_new_image(game->mlx, width, height);
	ret->addr = mlx_get_data_addr(ret->mlx_img, &(ret->bpp), \
								&(ret->line_len), &(ret->endian));
	return (ret);
}
