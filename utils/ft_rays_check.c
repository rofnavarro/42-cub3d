/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rays_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:11:54 by rferrero          #+#    #+#             */
/*   Updated: 2023/10/13 16:42:07 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_raycasting(t_game *game)
{
	t_rays	rays;
	t_point	zero;
	t_point	final_h;
	t_point	final_v;

	rays.ray = -1;
	rays.angle = (game->player.angle + (30 * PI / 180));
	rays.angle = ft_fix_angle(rays.angle);
	while (++rays.ray < N_RAYS)
	{
		ft_calc_3d(game, &rays, &final_h, 'H');
		ft_calc_3d(game, &rays, &final_v, 'V');
		ft_intersection(game, &rays, final_h, final_v);
		rays.angle = ft_fix_angle(rays.angle - (PI / 1800));
	}
}

void	ft_intersection(t_game *game, t_rays *rays, t_point h, t_point v)
{
	rays->intersection = 0;
	if (rays->dist_h < rays->dist_v)
	{
		rays->intersection = 1;
		rays->end.x = h.x;
		rays->end.y = h.y;
		ft_draw_3d(game, rays, rays->dist_h);
	}
	else
	{
		rays->end.x = v.x;
		rays->end.y = v.y;
		ft_draw_3d(game, rays, rays->dist_v);
	}
}

int	ft_check_boundaries(t_game *game, t_rays *rays, t_point *zero)
{
	rays->wall.x = 0;
	rays->wall.y = 0;
	if ((rays->map.y >= 0 && rays->map.x >= 0) && \
			(rays->map.y < ft_matrix_size(game->map.map)) && \
			(rays->map.x < ft_strlen(game->map.map[(int)rays->map.y])))
	{
		if (game->map.map[(int)rays->map.y][(int)rays->map.x] == '1')
		{
			rays->depth = 20;
			rays->wall.x = rays->map.x;
			rays->wall.y = rays->map.y;
		}
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
