/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_class.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 15:36:59 by rferrero          #+#    #+#             */
/*   Updated: 2023/09/26 17:16:41 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	render_direction(t_game *game)
{
	t_point	direction;
	t_point	start;

	start.x = (game->player.position.x * (MINIMAP_SIZE)) + \
											((MINIMAP_SIZE / 2) + MINIMAP_OFFSET);
	start.y = (game->player.position.y * (MINIMAP_SIZE)) + \
											((MINIMAP_SIZE / 2) + MINIMAP_OFFSET);
	direction.x = start.x + (cos(game->player.angle) * 10);
	direction.y = start.y + (-sin(game->player.angle) * 10);
	render_line(game, start, direction, 0xFF0000);
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
		rect.position.y = ((i * (MINIMAP_SIZE)) + MINIMAP_OFFSET);
		while (game->map.map[i][j])
		{
			rect.position.x = ((j * (MINIMAP_SIZE)) + MINIMAP_OFFSET);
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

	player.height = game->player.size + 1;
	player.width = game->player.size + 1;
	player.color = 0x0000FF;
	player.position.x = (game->player.position.x * MINIMAP_SIZE) + \
						((MINIMAP_SIZE / 2) - (game->player.size / 2) + MINIMAP_OFFSET);
	player.position.y = (game->player.position.y * MINIMAP_SIZE) + \
						((MINIMAP_SIZE / 2) - (game->player.size / 2) + MINIMAP_OFFSET);
	render_rect(&game->img, player);
	render_direction(game);
}
