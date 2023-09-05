/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rofnavarro@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/14 20:44:49 by rferrero          #+#    #+#             */
/*   Updated: 2021/11/13 03:35:18 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*tmp_s1;
	unsigned char	*tmp_s2;
	size_t			counter;

	tmp_s1 = (unsigned char *) s1;
	tmp_s2 = (unsigned char *) s2;
	counter = 0;
	while (counter < n)
	{
		if (tmp_s1[counter] != tmp_s2[counter])
		{
			return ((int)(tmp_s1[counter] - tmp_s2[counter]));
		}
		if (n == 0)
		{
			return (0);
		}
		counter++;
	}
	return (0);
}
