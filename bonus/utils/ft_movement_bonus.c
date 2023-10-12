/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_movement.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 16:32:56 by rinacio           #+#    #+#             */
/*   Updated: 2023/10/06 12:00:58 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	ft_move_player(t_game *game, int keysym)
{
	if (keysym == XK_A || keysym == XK_a)
	{
		ft_displacement(game, PI_2);
		is_valid_left(game, PI_2);
	}
	else if (keysym == XK_W || keysym == XK_w)
	{
		ft_displacement(game, 0);
		is_valid_front(game, 0);
	}
	else if (keysym == XK_D || keysym == XK_d)
	{
		ft_displacement(game, (3 * PI_2));
		is_valid_right(game, (3 * PI_2));
	}
	else if (keysym == XK_S || keysym == XK_s)
	{
		ft_displacement(game, PI);
		is_valid_back(game, PI);
	}
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
	game->player.position.y = game->player.displacement.y;
	game->player.position.x = game->player.displacement.x;
}

void	ft_displacement(t_game *game, float angle)
{
	game->player.displacement.x = game->player.position.x + \
									SPEED * cos(game->player.angle + angle);
	game->player.displacement.y = game->player.position.y + \
									SPEED * -sin(game->player.angle + angle);
}
