/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_movement_validation.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 11:39:23 by rferrero          #+#    #+#             */
/*   Updated: 2023/10/06 12:19:02 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	is_valid_front(t_game *game, float angle)
{
	t_point	ref;
	t_point	map;

	if (game->player.angle <= PI && game->player.angle > 0)
	{
		ref.y = -0.2;
		if (game->player.angle < PI_2)
			ref.x = 0.2;
		else
			ref.x = -0.2;
	}
	else if (game->player.angle > PI && game->player.angle < (2 * PI) || \
			game->player.angle == 0)
	{
		ref.y = 0.2;
		if (game->player.angle >= (3 * PI_2))
			ref.x = 0.2;
		else
			ref.x = -0.2;
	}
	map.y = rintf(game->player.displacement.y + ref.y);
	map.x = rintf(game->player.displacement.x + ref.x);
	if (game->map.map[(int)map.y][(int)map.x] != '1')
		ft_update_player_position(game, angle);
}

void	is_valid_back(t_game *game, float angle)
{
	t_point	ref;
	t_point	map;

	if (game->player.angle <= PI && game->player.angle > 0)
	{
		ref.y = 0.2;
		if (game->player.angle < PI_2)
			ref.x = -0.2;
		else
			ref.x = 0.2;
	}
	else if (game->player.angle > PI && game->player.angle < (2 * PI) || \
			game->player.angle == 0)
	{
		ref.y = -0.2;
		if (game->player.angle >= (3 * PI_2))
			ref.x = -0.2;
		else
			ref.x = 0.2;
	}
	map.y = rintf(game->player.displacement.y + ref.y);
	map.x = rintf(game->player.displacement.x + ref.x);
	if (game->map.map[(int)map.y][(int)map.x] != '1')
		ft_update_player_position(game, angle);
}

void	is_valid_right(t_game *game, float angle)
{
	t_point	ref;
	t_point	map;

	if (game->player.angle <= PI_2 || game->player.angle >= (3 * PI_2))
	{
		ref.y = 0.2;
		if (game->player.angle > 0)
			ref.x = 0.2;
		else
			ref.x = -0.2;
	}
	else if (game->player.angle > PI_2 && game->player.angle < (3 * PI_2))
	{
		ref.y = -0.2;
		if (game->player.angle > PI)
			ref.x = -0.2;
		else
			ref.x = 0.2;
	}
	map.y = rintf(game->player.displacement.y + ref.y);
	map.x = rintf(game->player.displacement.x + ref.x);
	if (game->map.map[(int)map.y][(int)map.x] != '1')
		ft_update_player_position(game, angle);
}

void	is_valid_left(t_game *game, float angle)
{
	t_point	ref;
	t_point	map;

	if (game->player.angle <= PI_2 || game->player.angle >= (3 * PI_2))
	{
		ref.y = -0.2;
		if (game->player.angle > 0)
			ref.x = -0.2;
		else
			ref.x = 0.2;
	}
	else if (game->player.angle > PI_2 && game->player.angle < (3 * PI_2))
	{
		ref.y = 0.2;
		if (game->player.angle > PI)
			ref.x = 0.2;
		else
			ref.x = -0.2;
	}
	map.y = rintf(game->player.displacement.y + ref.y);
	map.x = rintf(game->player.displacement.x + ref.x);
	if (game->map.map[(int)map.y][(int)map.x] != '1')
		ft_update_player_position(game, angle);
}
