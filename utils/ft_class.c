/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_class.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 15:36:59 by rferrero          #+#    #+#             */
/*   Updated: 2023/09/19 17:06:51 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	render_direction(t_game *game, char c)
{
	t_point	direction;
	t_point	start;

	start.x = (game->player.position.x * (MINIMAP_SIZE)) + \
											(MINIMAP_SIZE / 2);
	start.y = (game->player.position.y * (MINIMAP_SIZE)) + \
											(MINIMAP_SIZE / 2);
	direction.x = (start.x + (game->player.displacement.x * 2));
	direction.y = (start.y + (game->player.displacement.y * 2));
	render_line(game, start, direction, 0x000000);
}

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

	rect.width = MINIMAP_SIZE - 1;
	rect.height = MINIMAP_SIZE - 1;
	i = 0;
	while (game->map.map[i])
	{
		j = 0;
		rect.position.y = (i * (MINIMAP_SIZE)) + 1;
		while (game->map.map[i][j])
		{
			rect.position.x = (j * (MINIMAP_SIZE)) + 1;
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

	player.height = PLAYER_SIZE + 1;
	player.width = PLAYER_SIZE + 1;
	player.color = 0x0000FF;
	player.position.x = (game->player.position.x * MINIMAP_SIZE) + \
						((MINIMAP_SIZE / 2) - (PLAYER_SIZE / 2));
	player.position.y = (game->player.position.y * MINIMAP_SIZE) + \
						((MINIMAP_SIZE / 2) - (PLAYER_SIZE / 2));
	minimap.x = player.position.x;
	minimap.y = player.position.y;
	render_rect(&game->img, player);
	render_direction(game, game->player.direction);
}
