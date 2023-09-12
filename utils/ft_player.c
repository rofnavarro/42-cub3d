/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_player.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 20:59:41 by rferrero          #+#    #+#             */
/*   Updated: 2023/09/11 18:12:10 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_player_position(t_player *player, char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || \
				map[i][j] == 'E' || map[i][j] == 'W')
			{
				player->position.x = j;
				player->position.y = i;
				player->direction = map[i][j];
				return ;
			}
			j++;
		}
		i++;
	}
}

void	ft_player_to_zero(t_player *player, char **map)
{
	map[(int)player->position.y][(int)player->position.x] = '0';
}

void	ft_player_to_direction(t_player *player, char **map)
{
	map[(int)player->position.y][(int)player->position.x] = player->direction;
}
