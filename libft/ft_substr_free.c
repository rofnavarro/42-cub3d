/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 16:35:45 by rferrero          #+#    #+#             */
/*   Updated: 2022/06/22 16:35:58 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr_free(char *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	strlen;

	if (!s)
		return (0);
	strlen = ft_strlen(s);
	if (start > strlen)
	{
		len = 0;
		start = strlen;
	}
	else if (start + len > strlen)
		len = strlen - start;
	ptr = (char *)malloc(len + 1 * sizeof(char));
	if (!ptr)
		return (0);
	ft_strlcpy(ptr, s + start, len + 1);
	free(s);
	return (ptr);
}
