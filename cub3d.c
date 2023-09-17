/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 13:28:52 by rferrero          #+#    #+#             */
/*   Updated: 2023/09/16 22:17:51 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;
	

	ft_preparation(&game, argc, argv);

	game.img.mlx_img = ft_new_image(&game, WIN_W, WIN_H);
	
	mlx_loop_hook(game.mlx, &ft_draw_handler, &game);
	mlx_key_hook(game.win, &ft_handle_keypress, &game);
	mlx_hook(game.win, DestroyNotify, NoEventMask, &ft_finish, &game);
	mlx_loop(game.mlx);

	mlx_destroy_image(game.mlx, game.img.mlx_img);

	ft_finish(&game);
	return (EXIT_SUCCESS);
}
