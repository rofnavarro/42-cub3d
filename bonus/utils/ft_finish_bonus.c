/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_finish.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinacio <rinacio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 15:16:39 by rferrero          #+#    #+#             */
/*   Updated: 2023/09/19 17:17:09 by rinacio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

int	ft_finish(t_game *game)
{
	mlx_destroy_image(game->mlx, game->img.mlx_img);
	ft_free_matrix(game->map.config);
	ft_free_matrix(game->map.map);
	ft_free_matrix(game->map.textures);
	free(game->map.ceiling_color);
	free(game->map.floor_color);
	mlx_loop_end(game->mlx);
	mlx_destroy_window(game->mlx, game->win);
	game->win = NULL;
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	exit (0);
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
