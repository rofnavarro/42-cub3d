/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rofnavarro@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 14:00:08 by rferrero          #+#    #+#             */
/*   Updated: 2021/11/13 21:22:31 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	counter;
	char			*string;

	if (!s)
	{
		return (NULL);
	}
	string = (char *) malloc((ft_strlen(s) + 1) * sizeof(char));
	if (string == NULL)
	{
		return (NULL);
	}
	counter = 0;
	while (s[counter])
	{
		string[counter] = f(counter, s[counter]);
		counter++;
	}
	string[counter] = '\0';
	return (string);
}
