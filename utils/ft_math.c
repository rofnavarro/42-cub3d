/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 17:35:45 by rferrero          #+#    #+#             */
/*   Updated: 2023/09/11 18:08:02 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

float	ft_deg_to_rad(int deg)
{
	float	ret;

	ret = deg * PI / 180.00;
	return (ret);
}

int	ft_fix_angle(int angle)
{
	if (angle > 359)
		angle -= 360;
	if (angle < 0)
		angle += 360;
	return (angle);
}

float	ft_distance(t_point a, t_point b, float angle)
{
	float	ret;

	ret = (cos(ft_deg_to_rad(angle)) * (b.x - a.x)) - (sin(ft_deg_to_rad(angle)) * (b.y - a.y));
	return (ret);
}
