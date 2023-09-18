/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_class.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 15:36:59 by rferrero          #+#    #+#             */
/*   Updated: 2023/09/18 17:46:47 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	ft_check_map_char(t_game *game, char c, t_rect *rect)
{
	if (c == '1')
	{
		rect->color = 0x808080;
		render_rect(&game->img, *rect);
	}
	else if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		rect->color = 0xFFFFFF;
		render_rect(&game->img, *rect);
	}
}

void	render_minimap(t_game *game)
{
	int		i;
	int		j;
	t_rect	rect;

	rect.width = SIZE_MINIMAP;
	rect.height = SIZE_MINIMAP;
	i = 0;
	while (game->map.map[i])
	{
		j = 0;
		rect.position.y = i * (SIZE_MINIMAP + 1);
		while (game->map.map[i][j])
		{
			rect.position.x = j * (SIZE_MINIMAP + 1);
			ft_check_map_char(game, game->map.map[i][j], &rect);
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
	t_point	minimap;

	player.height = 4;
	player.width = 4;
	player.color = 0x0000FF;
	player.position.x = (game->player.position.x * (SIZE_MINIMAP + 1)) + \
											(SIZE_MINIMAP / 2) - 2;
	player.position.y = (game->player.position.y * (SIZE_MINIMAP + 1)) + \
											(SIZE_MINIMAP / 2) - 2;
	minimap.x = player.position.x;
	minimap.y = player.position.y;
	render_rect(&game->img, player);
}
