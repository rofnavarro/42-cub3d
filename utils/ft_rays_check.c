/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rays_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:11:54 by rferrero          #+#    #+#             */
/*   Updated: 2023/09/19 18:22:58 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	check_horizontal(t_game *game)
{
	t_rays	rays;

	rays.ray = 1;
	rays.depth = 0;
	rays.dist_h = 100000;
	rays.angle = ft_fix_angle(game->player.angle + 30);
	rays.end.x = game->player.position.x * rays.dist_h;
	rays.end.y = game->player.position.y * rays.dist_h;
	while (rays.ray < 2)
	{
		if (rays.angle < PI && rays.angle >= 0)
		{
			rays.end.y = (((int)game->player.position.y >> 5) << 5) - 0.0001;
			rays.end.x = (game->player.position.y - rays.end.y) * \
							(1 / tan(rays.angle)) + game->player.position.x;
			rays.start.y = -32;
			rays.start.x = rays.start.y * (1 / tan(rays.angle));
		}
		else if (rays.angle >= PI && rays.angle <= 2 * PI)
		{
			rays.end.y = (((int)game->player.position.y >> 5) << 5) + 32;
			rays.end.x = (game->player.position.y - rays.end.y) * \
							(1 / tan(rays.angle)) + game->player.position.x;
			rays.start.y = 32;
			rays.start.x = -rays.start.y * (1 / tan(rays.angle));
		}
		else
		{
			rays.end.y = game->player.position.y;
			rays.end.x = game->player.position.x;
			rays.depth = 8;
		}
		while (rays.depth < 8)
		{
			rays.map.x = (int)rays.end.x >> 5;
			rays.map.y = (int)rays.end.y >> 5;
			if (rays.map.x > 0 && rays.map.x < ft_strlen(game->map.map[(int)rays.map.y]) &&
				rays.map.y > 0 && rays.map.y < ft_matrix_size(game->map.map) && 
				game->map.map[(int)rays.map.y][(int)rays.map.x] == '1')
			{
				rays.depth = 8;
				rays.dist_h = ft_distance(rays.start, rays.end, rays.angle);
			}
			else
			{
				rays.end.x += rays.start.x;
				rays.end.y += rays.start.y;
				rays.depth++;
			}
		}
		rays.angle = ft_fix_angle(rays.angle - 1);
		rays.ray++;
	}
	// printf("player x = %f\nplayer y = %f\n", game->player.position.x, game->player.position.y);
	// printf("ray x = %f\nray y = %f\n", rays.end.x, rays.end.y);
	render_line(game, game->player.position, rays.end, 0xFF0000);
}
