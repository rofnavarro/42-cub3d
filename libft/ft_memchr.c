/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rofnavarro@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/14 20:34:19 by rferrero          #+#    #+#             */
/*   Updated: 2021/11/13 03:17:23 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*scan;

	while (n-- > 0)
	{
		scan = (unsigned char *) s;
		if (*scan == (unsigned char) c)
		{
			return (scan);
		}
		s++;
	}
	return (NULL);
}
