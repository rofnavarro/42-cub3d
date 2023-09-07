/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 13:28:52 by rferrero          #+#    #+#             */
/*   Updated: 2023/09/06 22:50:36 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;

	ft_check_args(argc, argv);
	game.map.map_str = ft_read_map(&game, argv[1]);
	ft_validate_map(&game);
	game.mlx = mlx_init();
	game.map.matrix = ft_split(game.map.map_str, '\n');
	free(game.map.map_str);
	game.map.config = ft_map_config(&game);
	game.map.map = ft_map_map(&game);

	ft_free_matrix(game.map.matrix);
	
	game.win = mlx_new_window(game.mlx, WIN_W, WIN_H, \
								"cub3D - rinacio && rferrero");

	mlx_destroy_window(game.mlx, game.win);
	mlx_destroy_display(game.mlx);
	ft_free_matrix(game.map.config);
	ft_free_matrix(game.map.map);
	free(game.mlx);
	return (EXIT_SUCCESS);
}
