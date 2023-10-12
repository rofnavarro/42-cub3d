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
	rays.shade = 1.0;
	while (++rays.ray < N_RAYS)
	{
		ft_calc_rays_3d(game, &rays, &final_h, 'H');
		ft_calc_rays_3d(game, &rays, &final_v, 'V');
		if (rays.dist_h < rays.dist_v)
			rays.intersection = 1;
		else
			rays.intersection = 0;
		if (rays.dist_h < rays.dist_v)
		{
			rays.end.x = final_h.x;
			rays.end.y = final_h.y;
			ft_draw_3d(game, &rays, rays.dist_h, 0x5CB8B8);
		}
		else
		{
			rays.end.x = final_v.x;
			rays.end.y = final_v.y;
			ft_draw_3d(game, &rays, rays.dist_v, 0x009090);
			rays.shade = 0.5;
		}
		rays.angle = ft_fix_angle(rays.angle - (PI / 1800));
		
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

float	ft_calc_wall_height(t_game *game, float dist)
{
	float	line_height;

	line_height = (int)(WIN_H / dist * 1.8);
	if (line_height > WIN_H * 0.7)
		line_height = WIN_H * 0.7;
	return (line_height);
}

float	ft_draw_3d(t_game *game, t_rays *rays, float dist, int color)
{
	float	angle;
	t_point	start;
	t_point	end;
	float	line;
	int		i;
	int		j;
	float	tex_x;
	float	tex_y;
	float	tex_pos;
	float	tex_step;

	angle = ft_fix_angle(game->player.angle - rays->angle);
	dist *= cos(angle);
	line = ft_calc_wall_height(game, dist);
	tex_step = 64.0 / (float)line;
	end.y = (WIN_H/2 - line / 2);
	if (end.y  < 0 || end.y  > WIN_H)
		end.y = 0;
	start.y = (WIN_H/2 + line / 2);
	if (start.y >= WIN_H)
		start.y >= WIN_H - 1;
	start.x = rays->ray * (int)WIN_W / N_RAYS;
	i = -1;
	end.x = start.x;
		if (rays->intersection == 1)
		{
			tex_x = (int)(rays->end.x*4 * MINIMAP_TILE) % 64;
			if (rays->angle > PI)
				tex_x = 63 - tex_x;
		}
		else
		{
			tex_x = (int)(rays->end.y*4 * MINIMAP_TILE) % 64;
			if (rays->angle > PI_2 && rays->angle < 3 * PI_2)
				tex_x = 63-tex_x;			
		}
	while (++i < (int)WIN_W / N_RAYS)
	{
		tex_pos = (end.y - WIN_H / 2 + line / 2) * tex_step;
		tex_y = 0;       
		j = end.y;
		while (++j < start.y)
		{
			tex_y = (int)tex_pos & 63;
			tex_pos += tex_step;
			int wall = 0;
			if (rays->intersection && game->player.angle < PI && 
			game->player.position.y > rays->wall.y)
				wall = 0;
			else if (rays->intersection)
				wall = 1;
			else if (!rays->intersection && game->player.angle > PI_2 && game->player.angle < 3 * PI_2 &&
			game->player.position.x < rays->wall.x)
				wall = 2;
			else
				wall = 3;		
			color = game->map.walls[wall][((int)tex_y * 64 + (int)tex_x)];
			float fator = 0.60;
			int cor_de_fundo = 0x000000;
			if (rays->intersection == 0)
				color = (
    (int)(((color & 0xFF0000) >> 16) * fator + ((cor_de_fundo & 0xFF0000) >> 16) * (1 - fator)) << 16 |
    (int)(((color & 0x00FF00) >> 8) * fator + ((cor_de_fundo & 0x00FF00) >> 8) * (1 - fator)) << 8 |
    (int)((color & 0x0000FF) * fator + (cor_de_fundo & 0x0000FF) * (1 - fator))
);
			ft_img_pix_put(&game->img, start.x, j, color);

		}
		start.x++;
	}
}

void	ft_calc_rays_3d(t_game *game, t_rays *rays, t_point *final, char dir)
{
	t_point	zero;

	rays->depth = 0;
	rays->start.y = (game->player.position.y * MINIMAP_TILE) + \
						((MINIMAP_TILE / 2) + MINIMAP_OFFSET);
	rays->start.x = (game->player.position.x * MINIMAP_TILE) + \
						((MINIMAP_TILE / 2) + MINIMAP_OFFSET);
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
		rays->end.y = ft_convert_distance(rays->start.y) + MINIMAP_TILE \
			;
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
		rays->end.y = (rays->start.x - rays->end.x) * \
						(tan(rays->angle)) + rays->start.y;
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
