/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_finish.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinacio <rinacio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 15:16:39 by rferrero          #+#    #+#             */
/*   Updated: 2023/09/12 16:28:30 by rinacio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_finish(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	ft_free_matrix(game->map.config);
	ft_free_matrix(game->map.map);
	ft_free_matrix(game->map.textures);
	free(game->map.ceiling_color);
	free(game->map.floor_color);
	free(game->mlx);
}

void	ft_validation_exit(t_game *game, char *msg)
{
	int	i;

	printf("Error\n%s", msg);
	ft_free_matrix(game->map.config);
	ft_free_matrix(game->map.map);
	if (game->map.textures)
		ft_free_matrix(game->map.textures);
	free(game->map.ceiling_color);
	free(game->map.floor_color);
	exit(EXIT_FAILURE);
}
