/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rofnavarro@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 13:14:33 by rferrero          #+#    #+#             */
/*   Updated: 2021/11/20 22:01:22 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*end;

	end = s;
	while (*end)
	{
		end++;
	}
	while (end != s)
	{
		if (*end == (char) c)
		{
			return ((char *) end);
		}
		end--;
	}
	if (*end == (char) c)
	{
		return ((char *) end);
	}
	return (NULL);
}
