/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_class.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 15:36:59 by rferrero          #+#    #+#             */
/*   Updated: 2023/09/17 15:40:36 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	render_background(t_img *img, int color)
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

void	render_minimap(t_game *game)
{
	int		i;
	int		j;
	t_rect	rect;

	rect.width = SIZE;
	rect.height = SIZE;
	i = 0;
	while (game->map.map[i])
	{
		j = 0;
		while (game->map.map[i][j])
		{
			rect.y = (i * rect.height) + 2;
			rect.x = (j * rect.width) + 2;
			if (game->map.map[i][j] == ' ')
				rect.color = 0x000000;
			else if (game->map.map[i][j] == '1')
				rect.color = 0x808080;
			else
				rect.color = 0xFFFFFF;
			render_rect(&game->img, rect);
			j++;
		}
		i++;
	}
}

void	render_player(t_game *game)
{
	int		i;
	int		j;
	t_rect	player;

	player.height = 4;
	player.width = 4;
	player.color = 0x0000FF;
	player.x = (game->player.position.x * SIZE) + (SIZE / 2) - 1;
	player.y = (game->player.position.y * SIZE) + (SIZE / 2) - 1;
	render_rect(&game->img, player);
}
