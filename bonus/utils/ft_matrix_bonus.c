/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 21:29:44 by rferrero          #+#    #+#             */
/*   Updated: 2023/09/17 02:37:54 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

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
				return (EXIT_SUCCESS);
		}
	}
	return (EXIT_FAILURE);
}

int	ft_matrix_max_width(char **matrix)
{
	int	i;
	int	j;
	int	ret;

	i = -1;
	ret = 0;
	while (matrix[++i])
	{
		j = 0;
		while (matrix[i][j])
			j++;
		if (ret < j)
			ret = j;
	}
	return (ret);
}
