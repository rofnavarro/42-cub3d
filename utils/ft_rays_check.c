/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rays_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:11:54 by rferrero          #+#    #+#             */
/*   Updated: 2023/09/29 17:44:02 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	check_horizontal(t_game *game)
{
	t_rays	rays;
	t_point	zero;
	t_point	final_h;
	t_point	final_v;

	rays.ray = 0;
	rays.dist_h = 10;
	rays.angle = (game->player.angle - (30 * PI / 180));
	rays.angle = ft_fix_angle(rays.angle);
	while (rays.ray < 60)
	{
		rays.depth = 0;
		rays.start.y = (game->player.position.y * MINIMAP_SIZE) + \
							((MINIMAP_SIZE / 2) + MINIMAP_OFFSET);
		rays.start.x = (game->player.position.x * MINIMAP_SIZE) + \
							((MINIMAP_SIZE / 2) + MINIMAP_OFFSET);
		if (rays.angle < PI)
		{
			rays.end.y = ((((int)rays.start.y) >> ((int)log2(MINIMAP_SIZE))) << \
					((int)log2(MINIMAP_SIZE))) -0.0001;
			rays.end.x = ((rays.start.y - rays.end.y) * \
							(1 / tan(ft_fix_angle(rays.angle)))) + rays.start.x;
			zero.y = -(MINIMAP_SIZE);
			zero.x = -zero.y * (1 / tan(ft_fix_angle(rays.angle)));
		}
		if (rays.angle > PI)
		{
			rays.end.y = ((((int)rays.start.y) >> ((int)log2(MINIMAP_SIZE))) << \
					((int)log2(MINIMAP_SIZE))) + MINIMAP_SIZE + MINIMAP_OFFSET;
			rays.end.x = ((rays.start.y - rays.end.y) * \
							(1 / tan(ft_fix_angle(rays.angle)))) + rays.start.x;
			zero.y = (MINIMAP_SIZE);
			zero.x = -zero.y * (1 / tan(ft_fix_angle(rays.angle)));
		}
		if (rays.angle == PI || rays.angle == 0 || rays.angle == (2 * PI))
		{
			rays.end.y = rays.start.y;
			rays.end.x = rays.start.x;
			rays.depth = 8;
		}
		while (rays.depth < 8)
		{
			rays.map.y = (((int)rays.end.y) >> ((int)log2(MINIMAP_SIZE)) << \
							((int)log2(MINIMAP_SIZE))) / (MINIMAP_SIZE);
			rays.map.x = (((int)rays.end.x) >> ((int)log2(MINIMAP_SIZE)) << \
							((int)log2(MINIMAP_SIZE))) / (MINIMAP_SIZE);
			if ((rays.map.y >= 0 && rays.map.x >= 0) && \
				(rays.map.y < ft_matrix_size(game->map.map)) && \
				(rays.map.x < ft_strlen(game->map.map[(int)rays.map.y])))
			{
				if (game->map.map[(int)rays.map.y][(int)rays.map.x] == '1')
					rays.depth = 8;
				else
				{
					rays.end.y += zero.y;
					rays.end.x += zero.x;
				}
				rays.depth++;
			}
			else
				break ;
		}
		final_h.y = rays.end.y;
		final_h.x = rays.end.x;
		rays.dist_h = ft_distance(rays.start, rays.end, rays.angle);

		//    corte aqui


		rays.depth = 0;
		rays.start.x = (game->player.position.x * MINIMAP_SIZE) + \
							((MINIMAP_SIZE / 2) + MINIMAP_OFFSET);
		rays.start.y = (game->player.position.y * MINIMAP_SIZE) + \
							((MINIMAP_SIZE / 2) + MINIMAP_OFFSET);
		if (rays.angle < (3 * PI / 2) && rays.angle > PI_2)
		{
			rays.end.x = ((((int)rays.start.x) >> ((int)log2(MINIMAP_SIZE))) << \
					((int)log2(MINIMAP_SIZE))) -0.0001;
			rays.end.y = ((rays.start.x - rays.end.x) * \
							(tan(ft_fix_angle(rays.angle)))) + rays.start.y;
			zero.x = -(MINIMAP_SIZE);
			zero.y = -zero.x * (tan(ft_fix_angle(rays.angle)));
		}
		if (rays.angle < PI_2 || rays.angle > (3 * PI / 2))
		{
			rays.end.x = ((((int)rays.start.x) >> ((int)log2(MINIMAP_SIZE))) << \
					((int)log2(MINIMAP_SIZE))) + MINIMAP_SIZE + MINIMAP_OFFSET;
			rays.end.y = ((rays.start.x - rays.end.x) * \
							(tan(ft_fix_angle(rays.angle)))) + rays.start.y;
			zero.x = ((MINIMAP_SIZE));
			zero.y = -zero.x * (tan(ft_fix_angle(rays.angle)));
		}
		if (rays.angle == PI_2 || rays.angle == (3 * PI / 2))
		{
			rays.end.x = rays.start.x;
			rays.end.y = rays.start.y;
			rays.depth = 8;
		}
		while (rays.depth < 8)
		{
			rays.map.x = (((int)rays.end.x) >> ((int)log2(MINIMAP_SIZE)) << \
							((int)log2(MINIMAP_SIZE))) / (MINIMAP_SIZE);
			rays.map.y = (((int)rays.end.y) >> ((int)log2(MINIMAP_SIZE)) << \
							((int)log2(MINIMAP_SIZE))) / (MINIMAP_SIZE);
			if ((rays.map.y >= 0 && rays.map.x >= 0) && \
				(rays.map.y < ft_matrix_size(game->map.map)) && \
				(rays.map.x < ft_strlen(game->map.map[(int)rays.map.y])))
			{
				if (game->map.map[(int)rays.map.y][(int)rays.map.x] == '1')
					rays.depth = 8;
				else
				{
					rays.end.x += zero.x;
					rays.end.y += zero.y;
				}
				rays.depth++;
			}
			else
				break ;
		}
		final_v.x = rays.end.x;
		final_v.y = rays.end.y;
		rays.dist_v = ft_distance(rays.start, rays.end, rays.angle);

		if (rays.dist_h < rays.dist_v)
			render_line(game, rays.start, final_h, 0x009090);
		else if (rays.dist_v <= rays.dist_h)
			render_line(game, rays.start, final_v, 0x009090);
		// if (rays.dist_h > 500)
		// {
		// 	rays.end.y = (rays.start.y + (rays.end.y * -sin(ft_fix_angle(rays.angle))) * 0.000000005);
		// 	rays.end.x = (rays.start.x + (rays.end.x * cos(ft_fix_angle(rays.angle))) * 0.000000005);
		// }
		// // render_line(game, rays.start, rays.end, 0x009090);
		rays.angle = (rays.angle + (PI / 180));
		rays.angle = ft_fix_angle(rays.angle);
		rays.ray++;
	}
}

void	check_vertical(t_game *game)
{
	t_rays	rays;
	t_point	zero;

	rays.ray = 0;
	rays.dist_v = 10;
	rays.angle = (game->player.angle - (30 * PI / 180));
	rays.angle = ft_fix_angle(rays.angle);
	while (rays.ray < 60)
	{
		rays.depth = 0;
		rays.start.x = (game->player.position.x * MINIMAP_SIZE) + \
							((MINIMAP_SIZE / 2) + MINIMAP_OFFSET);
		rays.start.y = (game->player.position.y * MINIMAP_SIZE) + \
							((MINIMAP_SIZE / 2) + MINIMAP_OFFSET);
		if (rays.angle < (3 * PI / 2) && rays.angle > PI_2)
		{
			rays.end.x = ((((int)rays.start.x) >> ((int)log2(MINIMAP_SIZE))) << \
					((int)log2(MINIMAP_SIZE))) -0.0001;
			rays.end.y = ((rays.start.x - rays.end.x) * \
							(tan(ft_fix_angle(rays.angle)))) + rays.start.y;
			zero.x = -(MINIMAP_SIZE);
			zero.y = -zero.x * (tan(ft_fix_angle(rays.angle)));
		}
		if (rays.angle < PI_2 || rays.angle > (3 * PI / 2))
		{
			rays.end.x = ((((int)rays.start.x) >> ((int)log2(MINIMAP_SIZE))) << \
					((int)log2(MINIMAP_SIZE))) + MINIMAP_SIZE + MINIMAP_OFFSET;
			rays.end.y = ((rays.start.x - rays.end.x) * \
							(tan(ft_fix_angle(rays.angle)))) + rays.start.y;
			zero.x = ((MINIMAP_SIZE));
			zero.y = -zero.x * (tan(ft_fix_angle(rays.angle)));
		}
		if (rays.angle == PI_2 || rays.angle == (3 * PI / 2))
		{
			rays.end.x = rays.start.x;
			rays.end.y = rays.start.y;
			rays.depth = 8;
		}
		while (rays.depth < 8)
		{
			rays.map.x = (((int)rays.end.x) >> ((int)log2(MINIMAP_SIZE)) << \
							((int)log2(MINIMAP_SIZE))) / (MINIMAP_SIZE);
			rays.map.y = (((int)rays.end.y) >> ((int)log2(MINIMAP_SIZE)) << \
							((int)log2(MINIMAP_SIZE))) / (MINIMAP_SIZE);
			if ((rays.map.y >= 0 && rays.map.x >= 0) && \
				(rays.map.y < ft_matrix_size(game->map.map)) && \
				(rays.map.x < ft_strlen(game->map.map[(int)rays.map.y])))
			{
				if (game->map.map[(int)rays.map.y][(int)rays.map.x] == '1')
					rays.depth = 8;
				else
				{
					rays.end.x += zero.x;
					rays.end.y += zero.y;
				}
				rays.depth++;
			}
			else
				break ;
		}
		rays.dist_v = ft_distance(rays.start, rays.end, rays.angle);
		if (rays.dist_v > 500)
		{
			rays.end.x = (rays.start.x + (rays.end.x * cos(ft_fix_angle(rays.angle))) * 0.000000005);
			rays.end.y = (rays.start.y + (rays.end.y * -sin(ft_fix_angle(rays.angle))) * 0.000000005);
		}
		// render_line(game, rays.start, rays.end, 0x009090);
		rays.angle = (rays.angle + (PI / 180));
		rays.angle = ft_fix_angle(rays.angle);
		rays.ray++;
	}
}
