/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 20:49:06 by rferrero          #+#    #+#             */
/*   Updated: 2022/06/20 18:56:07 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*string;
	char	*ref;

	if (!s1 || !s2)
	{
		return (NULL);
	}
	string = (char *) malloc((ft_strlen(s1) + ft_strlen(s2) + 1)
			* sizeof(char));
	if (string == NULL)
	{
		return (NULL);
	}
	ref = string;
	while (*s1)
	{
		*string++ = *s1++;
	}
	while (*s2)
	{
		*string++ = *s2++;
	}
	*string = '\0';
	return (ref);
}
