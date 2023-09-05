/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rofnavarro@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 13:11:49 by rferrero          #+#    #+#             */
/*   Updated: 2021/11/13 20:59:49 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	counter;
	size_t	ref;

	counter = 0;
	ref = 0;
	while (dest[counter] && counter < size)
	{
		counter++;
	}
	ref = counter;
	while (src[counter - ref] && (counter + 1) < size)
	{
		dest[counter] = src[counter - ref];
		counter++;
	}
	if (ref < size)
	{
		dest[counter] = '\0';
	}
	return (ref + ft_strlen(src));
}
