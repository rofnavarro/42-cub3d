/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rofnavarro@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/14 13:45:09 by rferrero          #+#    #+#             */
/*   Updated: 2021/11/14 22:56:28 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_itoa_fill(long int n, char *nb, int counter)
{
	long int	tmp;

	if (n < 0)
	{
		tmp = -n;
		nb[0] = '-';
	}
	else
		tmp = n;
	if (tmp >= 10)
	{
		ft_itoa_fill(tmp / 10, nb, counter - 1);
		ft_itoa_fill(tmp % 10, nb, counter);
	}
	if (tmp < 10)
	{
		tmp = tmp + 48;
		nb[counter] = tmp;
	}
}

char	*ft_itoa(int n)
{
	char		*string;
	long int	tmp;
	int			length;
	int			size;

	tmp = n;
	length = 0;
	while (tmp != 0)
	{
		tmp = tmp / 10;
		length++;
	}
	size = length;
	if (n < 0)
	{
		size++;
		tmp = tmp * -n;
	}
	if (n == 0)
		size = 1;
	string = malloc ((size + 1) * sizeof(char));
	string[size] = '\0';
	ft_itoa_fill(n, string, size - 1);
	return (string);
}
