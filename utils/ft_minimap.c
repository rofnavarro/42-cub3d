/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minimap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 16:02:37 by rinacio           #+#    #+#             */
/*   Updated: 2023/10/13 16:42:08 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_draw_minimap_raylines(t_game *game)
{
	t_rays	rays;
	t_point	zero;
	t_point	final_h;
	t_point	final_v;

	rays.ray = -1;
	rays.angle = (game->player.angle + (PI / 6));
	rays.angle = ft_fix_angle(rays.angle);
	while (++rays.ray < 60)
	{
		ft_calc_rays(game, &rays, &final_h, 'H');
		ft_calc_rays(game, &rays, &final_v, 'V');
		if (game->map.toggle == 0)
		{
			if (rays.dist_h < rays.dist_v)
				render_line(game, rays.start, final_h, RAY_COLOR);
			else if (rays.dist_v <= rays.dist_h)
				render_line(game, rays.start, final_v, RAY_COLOR);
		}
		rays.angle = ft_fix_angle(rays.angle - (PI / 180));
	}
}

void	ft_calc_rays(t_game *game, t_rays *rays, t_point *final, char dir)
{
	t_point	zero;

	rays->depth = 0;
	rays->start.y = (game->player.position.y * MINIMAP_TILE) + \
						((MINIMAP_TILE / 2) + MINIMAP_OFFSET);
	rays->start.x = (game->player.position.x * MINIMAP_TILE) + \
						((MINIMAP_TILE / 2) + MINIMAP_OFFSET);
	if (dir == 'H')
		ft_check_angles_h(rays, &zero);
	else
		ft_check_angles_v(rays, &zero);
	while (rays->depth < 20)
	{
		rays->map.y = ft_convert_distance(rays->end.y) / (MINIMAP_TILE);
		rays->map.x = ft_convert_distance(rays->end.x) / (MINIMAP_TILE);
		if (ft_check_boundaries(game, rays, &zero))
			break ;
	}
	if (dir == 'H')
		rays->dist_h = ft_distance(rays->start, rays->end, rays->angle);
	if (dir == 'V')
		rays->dist_v = ft_distance(rays->start, rays->end, rays->angle);
	final->y = rays->end.y;
	final->x = rays->end.x;
}

void	ft_check_angles_h(t_rays *rays, t_point *zero)
{
	if (rays->angle < PI)
	{
		rays->end.y = ft_convert_distance(rays->start.y) - 0.0001;
		rays->end.x = (rays->start.y - rays->end.y) * \
						1 / tan(rays->angle) + rays->start.x;
		zero->y = -(MINIMAP_TILE);
		zero->x = -zero->y * (1 / tan(rays->angle));
	}
	if (rays->angle > PI)
	{
		rays->end.y = ft_convert_distance(rays->start.y) + MINIMAP_TILE
			+ MINIMAP_OFFSET;
		rays->end.x = (rays->start.y - rays->end.y) / tan(rays->angle) \
						+ rays->start.x;
		zero->y = (MINIMAP_TILE);
		zero->x = -zero->y / tan(rays->angle);
	}
	if (rays->angle == PI || rays->angle == 0 || rays->angle == (2 * PI))
	{
		rays->end.y = rays->start.y;
		rays->end.x = rays->start.x;
		rays->depth = 20;
	}
}

void	ft_check_angles_v(t_rays *rays, t_point *zero)
{
	if (rays->angle < (3 * PI / 2) && rays->angle > PI_2)
	{
		rays->end.x = ft_convert_distance(rays->start.x) - 0.0001;
		rays->end.y = ((rays->start.x - rays->end.x) * \
						(tan((rays->angle)))) + rays->start.y;
		zero->x = -(MINIMAP_TILE);
		zero->y = -zero->x * (tan(rays->angle));
	}
	if (rays->angle < PI_2 || rays->angle > (3 * PI / 2))
	{
		rays->end.x = ft_convert_distance(rays->start.x) + MINIMAP_TILE \
			+ MINIMAP_OFFSET;
		rays->end.y = (rays->start.x - rays->end.x) * \
						tan(rays->angle) + rays->start.y;
		zero->x = ((MINIMAP_TILE));
		zero->y = -zero->x * tan(rays->angle);
	}
	if (rays->angle == PI_2 || rays->angle == (3 * PI / 2))
	{
		rays->end.x = rays->start.x;
		rays->end.y = rays->start.y;
		rays->depth = 20;
	}
}
