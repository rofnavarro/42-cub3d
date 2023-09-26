/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 17:35:45 by rferrero          #+#    #+#             */
/*   Updated: 2023/09/26 17:44:49 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

float		ft_fix_angle(float a)
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
