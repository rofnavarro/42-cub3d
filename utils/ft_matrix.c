/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinacio <rinacio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 21:29:44 by rferrero          #+#    #+#             */
/*   Updated: 2023/09/12 16:30:59 by rinacio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_free_matrix(char	**matrix)
{
	int	i;

	i = -1;
	while (matrix[++i])
	{
		free(matrix[i]);
	}
	free(matrix);
}

int	ft_matrix_size(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i] && *matrix != NULL)
		i++;
	return (i);
}

char	**ft_matrix_calloc(int size)
{
	char	**ret;

	ret = (char **)ft_calloc(sizeof(char *), size);
	return (ret);
}

int	ft_is_numeric(char **matrix)
{
	int	i;
	int	j;

	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (matrix[i][++j])
		{
			if (!ft_isdigit(matrix[i][j]))
				return (0);
		}
	}
	return (1);
}
