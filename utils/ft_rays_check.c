/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rays_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:11:54 by rferrero          #+#    #+#             */
/*   Updated: 2023/09/26 23:53:44 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	check_horizontal(t_game *game)
{
	t_rays	rays;

	rays.ray = 1;
	rays.depth = 0;
	rays.dist_h = 10;
	rays.angle = (game->player.angle - (30 * PI / 180));
	rays.angle = ft_fix_angle(rays.angle);
	rays.start.x = (game->player.position.x * MINIMAP_SIZE) + \
						((MINIMAP_SIZE / 2) + MINIMAP_OFFSET);
	rays.start.y = (game->player.position.y * MINIMAP_SIZE) + \
						((MINIMAP_SIZE / 2) + MINIMAP_OFFSET);
	rays.end.x = (rays.start.x * rays.dist_h);
	rays.end.y = (rays.start.y * rays.dist_h);
	while (rays.ray < 60)
	{
		if (rays.angle < PI && rays.angle > 0)
		{
			rays.end.y = ((((int)rays.start.y) >> ((int)log2(MINIMAP_SIZE))) << \
					((int)log2(MINIMAP_SIZE))) + MINIMAP_OFFSET;
			rays.end.x = (rays.start.y - rays.end.y) * (1 / tan(rays.angle)) + \
							rays.start.x + MINIMAP_OFFSET;
		}
		else if (rays.angle > PI && rays.angle < 2 * PI)
		{
			rays.end.y = ((((int)rays.start.y) >> ((int)log2(MINIMAP_SIZE))) << \
					((int)log2(MINIMAP_SIZE))) + MINIMAP_SIZE + MINIMAP_OFFSET;
			rays.end.x = (rays.start.y - rays.end.y) * (1 / tan(rays.angle)) + \
							rays.start.x + MINIMAP_OFFSET;
		}
		else
			rays.depth = 8;
		rays.angle = (rays.angle + (PI / 180));
		rays.angle = ft_fix_angle(rays.angle);
		rays.ray++;
		render_line(game, rays.start, rays.end, 0x009090);
	}
}
