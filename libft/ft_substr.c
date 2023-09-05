/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rofnavarro@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 15:03:24 by rferrero          #+#    #+#             */
/*   Updated: 2021/11/25 19:06:08 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	s_length;
	char	*s_start;
	char	*substring;
	char	*tmp;
	size_t	t_len;

	if (!s)
		return (NULL);
	if (len > ft_strlen(s + start))
		t_len = ft_strlen(s + start);
	else
		t_len = len;
	substring = (char *) malloc((t_len + 1) * sizeof(char));
	if (substring == NULL)
		return (NULL);
	s_start = (char *) s;
	s_length = ft_strlen(s);
	tmp = substring;
	s = s + start;
	while (((size_t)(s - s_start) < s_length) && len--)
		*tmp++ = *s++;
	*tmp = '\0';
	return (substring);
}
