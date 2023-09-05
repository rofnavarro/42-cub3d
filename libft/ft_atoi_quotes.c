/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinacio <rinacio@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 13:06:39 by rferrero          #+#    #+#             */
/*   Updated: 2023/04/30 16:21:41 by rinacio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi_quotes(const char *nptr)
{
	int	result;
	int	signal;
	int	counter;

	result = 0;
	signal = 1;
	counter = 0;
	while ((nptr[counter] >= 9 && nptr[counter] <= 13) || nptr[counter] == 32)
		counter++;
	if ((nptr[counter] == '-' || nptr[counter] == '+')
		&& (ft_isdigit(nptr[counter + 1]) || nptr[counter + 1] == '\"'))
	{
		if (nptr[counter] == '-')
			signal = -1;
		counter++;
	}
	if (nptr[counter] == '\"' && ft_isdigit(nptr[counter + 1]))
		counter++;
	while (ft_isdigit(nptr[counter]))
	{
		result = (result * 10) + (nptr[counter] - '0');
		counter++;
	}
	return (signal * result);
}
