/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_walls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinacio <rinacio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 16:02:37 by rinacio           #+#    #+#             */
/*   Updated: 2023/09/19 17:50:49 by rinacio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	ft_check_angles_v_3d(t_rays *rays, t_point *zero)
{
	if (rays->angle < (3 * PI / 2) && rays->angle > PI_2)
	{
		rays->end.x = ft_convert_distance(rays->start.x) - 0.0001;
		rays->end.y = (rays->start.x - rays->end.x) * \
						(tan(rays->angle)) + rays->start.y;
		zero->x = -(MINIMAP_TILE);
		zero->y = -zero->x * (tan(rays->angle));
	}
	if (rays->angle < PI_2 || rays->angle > (3 * PI / 2))
	{
		rays->end.x = ft_convert_distance(rays->start.x) + MINIMAP_TILE;
		rays->end.y = (rays->start.x - rays->end.x)
			* tan(rays->angle) + rays->start.y;
		zero->x = (MINIMAP_TILE);
		zero->y = -zero->x * tan(rays->angle);
	}
	if (rays->angle == PI_2 || rays->angle == (3 * PI / 2))
	{
		rays->end.x = rays->start.x;
		rays->end.y = rays->start.y;
		rays->depth = 8;
	}
}

void	ft_check_angles_h_3d(t_rays *rays, t_point *zero)
{
	if (rays->angle < PI)
	{
		rays->end.y = ft_convert_distance(rays->start.y) - 0.0001;
		rays->end.x = (rays->start.y - rays->end.y) * \
						(1 / tan(rays->angle)) + rays->start.x;
		zero->y = -(MINIMAP_TILE);
		zero->x = -zero->y * (1 / tan(rays->angle));
	}
	else if (rays->angle > PI)
	{
		rays->end.y = ft_convert_distance(rays->start.y) + MINIMAP_TILE;
		rays->end.x = (rays->start.y - rays->end.y) * \
						(1 / tan(rays->angle)) + rays->start.x;
		zero->y = (MINIMAP_TILE);
		zero->x = -zero->y * (1 / tan(rays->angle));
	}
	else if (rays->angle == PI || rays->angle == 0 || rays->angle == (2 * PI))
	{
		rays->end.y = rays->start.y;
		rays->end.x = rays->start.x;
		rays->depth = 8;
	}
}

void	ft_calc_3d(t_game *game, t_rays *rays, t_point *final, char dir)
{
	t_point	zero;

	rays->depth = 0;
	rays->start.y = game->player.position.y * MINIMAP_TILE + \
						MINIMAP_TILE / 2;
	rays->start.x = game->player.position.x * MINIMAP_TILE + \
						MINIMAP_TILE / 2;
	if (dir == 'H')
		ft_check_angles_h_3d(rays, &zero);
	else
		ft_check_angles_v_3d(rays, &zero);
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

void	ft_draw_wall(t_game *game, t_rays *rays, t_point start, t_point end)
{
	int		i;
	float	tex_pos;
	t_point	tex;
	float	tex_step;
	int		j;

	i = -1;
	tex_step = 64.0 / (float)rays->line;
	tex.x = ft_calc_text_x(rays);
	while (++i < (int)WIN_W / N_RAYS)
	{
		tex_pos = (end.y - WIN_H / 2 + rays->line / 2) * tex_step;
		tex.y = 0;
		j = end.y;
		while (++j < start.y)
		{
			tex.y = (int)tex_pos & 63;
			tex_pos += tex_step;
			rays->texture = ft_choose_texture(game, rays);
			ft_get_pix_color(game, rays, tex);
			ft_img_pix_put(&game->img, start.x, j, rays->color);
		}
		start.x++;
	}
}
