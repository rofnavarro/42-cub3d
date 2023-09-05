/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 13:28:52 by rferrero          #+#    #+#             */
/*   Updated: 2023/09/05 14:58:51 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;

	ft_check_args(argc, argv);
	game.mlx = mlx_init();
	game.map.map_str = ft_read_map(&game, argv[1]);
	game.win = mlx_new_window(game.mlx, WIN_W, WIN_H, "cub3D - rinacio && rferrero");
	
	// mlx_loop(game.mlx);
	printf("%s\n", game.map.map_str);

	free(game.map.map_str);
	mlx_destroy_window(game.mlx, game.win);
	mlx_destroy_display(game.mlx);
	free(game.mlx);
	return (EXIT_SUCCESS);
}
