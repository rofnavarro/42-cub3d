/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_movement.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinacio <rinacio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 16:32:56 by rinacio           #+#    #+#             */
/*   Updated: 2023/09/19 15:00:54 by rinacio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_move_player(t_game *game, int keysym)
{	
	if (keysym == XK_A || keysym == XK_a)
		ft_update_player_position(game, PI / 2);
	else if (keysym == XK_W || keysym == XK_w)
		ft_update_player_position(game, 0);
	else if (keysym == XK_D || keysym == XK_d)
		ft_update_player_position(game, -PI / 2);
	else if (keysym == XK_S || keysym == XK_s)
		ft_update_player_position(game, PI);
}

void	ft_rotate_player(t_game *game, int keysym)
{
	if (keysym == XK_Right)
		game->player.angle += ROT_SPEED;
	else if (keysym == XK_Left)
		game->player.angle -= ROT_SPEED;
	return ;
}

void	ft_update_player_position(t_game *game, float angle)
{
	t_point	pos;

	pos.x = game->player.position.x + SPEED * cos(game->player.angle + angle);
	pos.y = game->player.position.y - SPEED * sin(game->player.angle + angle);
	if (game->map.map[(int)pos.y][(int)pos.x] == '1')
		return ;
	game->player.position.x = pos.x;
	game->player.position.y = pos.y;
}
