/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 13:28:52 by rferrero          #+#    #+#             */
/*   Updated: 2023/09/05 18:46:34 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (ft_check_args(argc, argv) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	game.map.map_str = ft_read_map(&game, argv[1]);
	if (ft_validate_map(&game) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	game.mlx = mlx_init();
	game.map.matrix = ft_split(game.map.map_str, '\n');
	free(game.map.map_str);

	game.win = mlx_new_window(game.mlx, WIN_W, WIN_H, \
								"cub3D - rinacio && rferrero");

	mlx_destroy_window(game.mlx, game.win);
	mlx_destroy_display(game.mlx);
	free(game.mlx);
	return (EXIT_SUCCESS);
}