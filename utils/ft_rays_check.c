/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rays_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:11:54 by rferrero          #+#    #+#             */
/*   Updated: 2023/09/30 14:26:31 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

float	ft_draw_3d(t_game *game, t_rays *rays, float dist, int color);

void	ft_raycasting(t_game *game)
{
	t_rays	rays;
	t_point	zero;
	t_point	final_h;
	t_point	final_v;

	rays.ray = -1;
	rays.angle = (game->player.angle + (30 * PI / 180));
	rays.angle = ft_fix_angle(rays.angle);
	while (++rays.ray < 60)
	{
		ft_calc_rays(game, &rays, &final_h, 'H');
		ft_calc_rays(game, &rays, &final_v, 'V');
		if (game->map.toggle == 0)
		{
			if (rays.dist_h < rays.dist_v)
				render_line(game, rays.start, final_h, 0x009090);
			else if (rays.dist_v <= rays.dist_h)
				render_line(game, rays.start, final_v, 0x009090);
		}
		if (rays.dist_h < rays.dist_v)
			ft_draw_3d(game, &rays, rays.dist_h, 0x009090);
		else
			ft_draw_3d(game, &rays, rays.dist_v, 0x5CB8B8);
		rays.angle = ft_fix_angle(rays.angle - (PI / 180));
	}
}

float	ft_calc_wall_height(t_game *game, float dist)
{
	float	line_height;

	line_height = WIN_H / dist ;
	if (line_height > 320)
		line_height = 320;
	if (dist > 40)
		return (0);
	return (line_height);
}

float	ft_draw_3d(t_game *game, t_rays *rays, float dist, int color)
{
	float	angle;
	t_point	start;
	t_point	end;
	float	line;
	int		i;

	angle = -ft_fix_angle(game->player.angle - rays->angle);
	dist *= cos(angle);
	line = ft_calc_wall_height(game, dist);
	end.y = (450 - line / 2);
	start.y = (450 - line / 2) + line;
	start.x = rays->ray * (int)WIN_W / 60;
	i = -1;
	while (++i < (int)WIN_W / 60)
	{
		end.x = start.x;
		render_line(game, start, end, color);
		start.x++;
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
	while (rays->depth < 8)
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

int	ft_check_boundaries(t_game *game, t_rays *rays, t_point *zero)
{
	if ((rays->map.y >= 0 && rays->map.x >= 0) && \
			(rays->map.y < ft_matrix_size(game->map.map)) && \
			(rays->map.x < ft_strlen(game->map.map[(int)rays->map.y])))
	{
		if (game->map.map[(int)rays->map.y][(int)rays->map.x] == '1')
			rays->depth = 8;
		else
		{
			rays->end.y += zero->y;
			rays->end.x += zero->x;
		}
		rays->depth++;
		return (0);
	}
	else
		return (1);
}

void	ft_check_angles_h(t_rays *rays, t_point *zero)
{
	if (rays->angle < PI)
	{
		rays->end.y = ft_convert_distance(rays->start.y) - 0.0001;
		rays->end.x = ((rays->start.y - rays->end.y) * \
						(1 / tan(ft_fix_angle(rays->angle)))) + rays->start.x;
		zero->y = -(MINIMAP_TILE);
		zero->x = -zero->y * (1 / tan(ft_fix_angle(rays->angle)));
	}
	if (rays->angle > PI)
	{
		rays->end.y = ft_convert_distance(rays->start.y) + MINIMAP_TILE \
			+ MINIMAP_OFFSET;
		rays->end.x = ((rays->start.y - rays->end.y) * \
						(1 / tan(ft_fix_angle(rays->angle)))) + rays->start.x;
		zero->y = (MINIMAP_TILE);
		zero->x = -zero->y * (1 / tan(ft_fix_angle(rays->angle)));
	}
	if (rays->angle == PI || rays->angle == 0 || rays->angle == (2 * PI))
	{
		rays->end.y = rays->start.y;
		rays->end.x = rays->start.x;
		rays->depth = 8;
	}
}

void	ft_check_angles_v(t_rays *rays, t_point *zero)
{
	if (rays->angle < (3 * PI / 2) && rays->angle > PI_2)
	{
		rays->end.x = ft_convert_distance(rays->start.x) - 0.0001;
		rays->end.y = ((rays->start.x - rays->end.x) * \
						(tan(ft_fix_angle(rays->angle)))) + rays->start.y;
		zero->x = -(MINIMAP_TILE);
		zero->y = -zero->x * (tan(ft_fix_angle(rays->angle)));
	}
	if (rays->angle < PI_2 || rays->angle > (3 * PI / 2))
	{
		rays->end.x = ft_convert_distance(rays->start.x) + MINIMAP_TILE \
			+ MINIMAP_OFFSET;
		rays->end.y = ((rays->start.x - rays->end.x) * \
						(tan(ft_fix_angle(rays->angle)))) + rays->start.y;
		zero->x = ((MINIMAP_TILE));
		zero->y = -zero->x * (tan(ft_fix_angle(rays->angle)));
	}
	if (rays->angle == PI_2 || rays->angle == (3 * PI / 2))
	{
		rays->end.x = rays->start.x;
		rays->end.y = rays->start.y;
		rays->depth = 8;
	}
}
