/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_finish.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 15:16:39 by rferrero          #+#    #+#             */
/*   Updated: 2023/09/13 17:33:39 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
