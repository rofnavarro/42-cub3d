/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rofnavarro@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/14 13:33:25 by rferrero          #+#    #+#             */
/*   Updated: 2021/11/13 19:28:47 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	*ref;
	size_t	total_size;

	total_size = nmemb * size;
	ref = malloc(total_size);
	if (!ref || (total_size > INT_MAX))
	{
		return (NULL);
	}
	ft_bzero(ref, total_size);
	return ((void *)ref);
}
