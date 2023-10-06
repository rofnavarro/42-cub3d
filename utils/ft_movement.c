/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_movement.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 16:32:56 by rinacio           #+#    #+#             */
/*   Updated: 2023/10/06 00:23:32 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	is_valid(t_game *game, float angle)
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
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

void	ft_move_player(t_game *game, int keysym)
{
	if (keysym == XK_A || keysym == XK_a)
		ft_update_player_position(game, PI_2);
	else if (keysym == XK_W || keysym == XK_w)
		ft_update_player_position(game, 0);
	else if (keysym == XK_D || keysym == XK_d)
		ft_update_player_position(game, (3 * PI) / 2);
	else if (keysym == XK_S || keysym == XK_s)
		ft_update_player_position(game, PI);
}

void	ft_rotate_player(t_game *game, int keysym)
{
	if (keysym == XK_Right)
		game->player.angle -= ROT_SPEED;
	else if (keysym == XK_Left)
		game->player.angle += ROT_SPEED;
	game->player.angle = ft_fix_angle(game->player.angle);
	game->player.displacement.x = game->player.position.x + \
									ROT_SPEED * cos(game->player.angle);
	game->player.displacement.y = game->player.position.y + \
									ROT_SPEED * -sin(game->player.angle);
}

void	ft_update_player_position(t_game *game, float angle)
{
	game->player.displacement.x = game->player.position.x + \
									SPEED * cos(game->player.angle + angle);
	game->player.displacement.y = game->player.position.y + \
									SPEED * -sin(game->player.angle + angle);
	if (is_valid(game, angle) == EXIT_SUCCESS)
	{
		game->player.position.y = game->player.displacement.y;
		game->player.position.x = game->player.displacement.x;
	}
}
