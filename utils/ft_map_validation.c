/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_validation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 18:23:53 by rferrero          #+#    #+#             */
/*   Updated: 2023/09/09 11:57:41 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	ft_acceptable_char(t_game *game, int i, int j, int *player)
{
	if (game->map.map[i][j] == 'N' || game->map.map[i][j] == 'S' || \
		game->map.map[i][j] == 'E' || game->map.map[i][j] == 'W')
		(*player)++;
	if (game->map.map[i][j] != 'N' && game->map.map[i][j] != 'S' && \
		game->map.map[i][j] != 'E' && game->map.map[i][j] != 'W' && \
		game->map.map[i][j] != '1' && game->map.map[i][j] != '0' && \
		game->map.map[i][j] != ' ')
	{
		printf("Error\nMap must have ONE player\n");
		ft_free_matrix(game->map.config);
		ft_free_matrix(game->map.map);
		exit(EXIT_FAILURE);
	}
}

void	ft_check_characters(t_game *game)
{
	int	i;
	int	j;
	int	player;

	i = 0;
	player = 0;
	while (game->map.map[i])
	{
		j = 0;
		while (game->map.map[i][j])
		{
			ft_acceptable_char(game, i, j, &player);
			j++;
		}
		i++;
	}
	if (player != 1)
	{
		printf("Error\nMap must have ONE player\n");
		ft_free_matrix(game->map.config);
		ft_free_matrix(game->map.map);
		exit(EXIT_FAILURE);
	}
}

static void	ft_check_for_one(t_game *game, int i, int j)
{
	if (i < 0 || i > (ft_matrix_size(game->map.map)) - 1 || \
		j < 0 || j > ft_strlen(game->map.map[i]) - 1)
	{
		printf("Error\nMap from file is not closed\n");
		ft_free_matrix(game->map.config);
		ft_free_matrix(game->map.map);
		exit(EXIT_FAILURE);
	}
	else
	{
		if (game->map.map[i][j] != '1' && game->map.map[i][j] != '0')
		{
			printf("Error\nMap from file is not closed\n");
			ft_free_matrix(game->map.config);
			ft_free_matrix(game->map.map);
			exit(EXIT_FAILURE);
		}
	}
}

static void	ft_check_ones_and_zeros(t_game *game, int i, int j)
{
	ft_check_for_one(game, i - 1, j);
	ft_check_for_one(game, i + 1, j);
	ft_check_for_one(game, i, j - 1);
	ft_check_for_one(game, i, j + 1);
}

void	ft_map_is_closed(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map.map[i])
	{
		j = 0;
		while (game->map.map[i][j])
		{
			if (game->map.map[i][j] == '0')
				ft_check_ones_and_zeros(game, i, j);
			j++;
		}
		i++;
	}
}
