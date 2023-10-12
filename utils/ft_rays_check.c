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

void	ft_draw_minimap_raylines(t_game *game)
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
		rays.angle = ft_fix_angle(rays.angle - (PI / 180));
	}
}

float	ft_calc_wall_height(t_game *game, float dist, t_rays *rays)
{
	rays->line = (int)(WIN_H / dist * 1.8);
	if (rays->line > WIN_H)
		rays->line = WIN_H;
}

float	ft_calc_text_x(t_rays *rays)
{
	float	tex_x;

	if (rays->intersection == 1)
	{
		tex_x = (int)(rays->end.x * 4 * MINIMAP_TILE) % 64;
		if (rays->angle > PI)
			tex_x = 63 - tex_x;
	}
	else
	{
		tex_x = (int)(rays->end.y * 4 * MINIMAP_TILE) % 64;
		if (rays->angle > PI_2 && rays->angle < 3 * PI_2)
			tex_x = 63 - tex_x;
	}
	return (tex_x);
}

float	ft_draw_3d(t_game *game, t_rays *rays, float dist)
{
	float	angle;
	t_point	start;
	t_point	end;

	angle = ft_fix_angle(game->player.angle - rays->angle);
	dist *= cos(angle);
	ft_calc_wall_height(game, dist, rays);
	end.y = (WIN_H / 2 - rays->line / 2);
	if (end.y < 0 || end.y > WIN_H)
		end.y = 0;
	start.y = (WIN_H / 2 + rays->line / 2);
	if (start.y >= WIN_H)
		start.y >= WIN_H - 1;
	start.x = rays->ray * (int)WIN_W / N_RAYS;
	end.x = start.x;
	ft_draw_wall(game, rays, start, end);
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
	rays->wall.x = 0;
	rays->wall.y = 0;
	if ((rays->map.y >= 0 && rays->map.x >= 0) && \
			(rays->map.y < ft_matrix_size(game->map.map)) && \
			(rays->map.x < ft_strlen(game->map.map[(int)rays->map.y])))
	{
		if (game->map.map[(int)rays->map.y][(int)rays->map.x] == '1')
		{
			rays->depth = 8;
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
		rays->depth = 8;
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
		rays->depth = 8;
	}
}
