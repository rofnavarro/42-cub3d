/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinacio <rinacio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 17:35:45 by rferrero          #+#    #+#             */
/*   Updated: 2023/09/29 19:27:50 by rinacio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

float	ft_fix_angle(float a)
{
	if (a > (2 * PI) - (PI / 180))
		a -= (2 * PI);
	if (a < 0)
		a += (2 * PI);
	return (a);
}

float	ft_distance(t_point a, t_point b, float angle)
{
	float	ret;

	ret = (cos((angle)) * (b.x - a.x)) - \
			(sin((angle)) * (b.y - a.y));
	return (ret);
}

float	ft_convert_distance(float distance_minimap)
{
	return ((int)distance_minimap >> (int)log2(MINIMAP_TILE) << \
					(int)log2(MINIMAP_TILE));
}
