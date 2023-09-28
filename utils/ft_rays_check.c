/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rays_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:11:54 by rferrero          #+#    #+#             */
/*   Updated: 2023/09/28 16:27:12 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	check_horizontal(t_game *game)
{
	t_rays	rays;
	t_point	zero;

	rays.ray = 0;
	rays.dist_h = 10;
	rays.angle = (game->player.angle - (30 * PI / 180));
	rays.angle = ft_fix_angle(rays.angle);
	rays.start.x = (game->player.position.x * MINIMAP_SIZE) + \
						((MINIMAP_SIZE / 2) + MINIMAP_OFFSET);
	rays.start.y = (game->player.position.y * MINIMAP_SIZE) + \
						((MINIMAP_SIZE / 2) + MINIMAP_OFFSET);
	while (rays.ray < 60)
	{
		rays.depth = 0;
		if (rays.angle < PI)
		{
			rays.end.y = ((((int)rays.start.y) >> ((int)log2(MINIMAP_SIZE))) << \
					((int)log2(MINIMAP_SIZE))) + MINIMAP_OFFSET - 0.0001;
			rays.end.x = (rays.start.y - rays.end.y) * (1 / tan(ft_fix_angle(rays.angle))) + \
							rays.start.x;
			zero.y = (-(MINIMAP_SIZE));
			zero.x = -zero.y * (1 / tan(ft_fix_angle(rays.angle)));
		}
		if (rays.angle > PI)
		{
			rays.end.y = ((((int)rays.start.y) >> ((int)log2(MINIMAP_SIZE))) << \
					((int)log2(MINIMAP_SIZE))) + MINIMAP_SIZE + MINIMAP_OFFSET;
			rays.end.x = (rays.start.y - rays.end.y) * (1 / tan(ft_fix_angle(rays.angle))) + \
							rays.start.x;
			zero.y = (MINIMAP_SIZE);
			zero.x = -zero.y * (1 / tan(ft_fix_angle(rays.angle)));
		}
		if (rays.angle == PI || rays.angle == 0 || rays.angle == (2 * PI))
		{
			rays.depth = 8;
			rays.end.y = rays.start.y;
			rays.end.x = rays.start.x;
		}
		while (rays.depth < 8)
		{
			rays.map.y = (((int)rays.end.y) >> ((int)log2(MINIMAP_SIZE)) << ((int)log2(MINIMAP_SIZE))) / (MINIMAP_SIZE);
			rays.map.x = (((int)rays.end.x) >> ((int)log2(MINIMAP_SIZE)) << ((int)log2(MINIMAP_SIZE))) / (MINIMAP_SIZE);
			if (rays.map.y >= 0 && rays.map.x >= 0 && \
				rays.map.y < ft_matrix_size(game->map.map) && \
				rays.map.x < ft_strlen(game->map.map[(int)rays.map.y]))
			{
				if (game->map.map[(int)rays.map.y][(int)rays.map.x] == '1')
				{
					printf("não precisa atravessar char = %c\n", game->map.map[(int)rays.map.y][(int)rays.map.x]);
					rays.depth = 8;
					rays.dist_h = ft_distance(rays.start, rays.end, rays.angle);
				}
				else
				{
					printf("precisa atravessar char = %c\n", game->map.map[(int)rays.map.y][(int)rays.map.x]);
					// rays.end.y += zero.y;
					// rays.end.x += zero.x;
				}
				rays.depth++;
			}
			else
				break ;
		}
		if (ft_distance(rays.start, rays.end, rays.angle) > 500)
		{
			rays.end.x = (rays.start.x + (rays.end.x * cos(ft_fix_angle(rays.angle))) * 0.0005);
			rays.end.y = (rays.start.y + (rays.end.y * -sin(ft_fix_angle(rays.angle))) * 0.0005);
		}
		render_line(game, rays.start, rays.end, 0x009090);
		rays.angle = (rays.angle + (PI / 180));
		rays.angle = ft_fix_angle(rays.angle);
		rays.ray++;
	}
}
