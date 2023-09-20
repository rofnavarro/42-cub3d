/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinacio <rinacio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 13:28:52 by rferrero          #+#    #+#             */
/*   Updated: 2023/09/18 17:21:10 by rinacio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;

	ft_preparation(&game, argc, argv);
	game.img.mlx_img = mlx_new_image(game.mlx, WIN_W, WIN_H);
	game.img.addr = mlx_get_data_addr(game.img.mlx_img, &game.img.bpp, \
									&game.img.line_len, &game.img.endian);
	mlx_loop_hook(game.mlx, &ft_draw_handler, &game);
	mlx_hook(game.win, KeyPress, KeyPressMask, &ft_handle_keypress, &game);
	mlx_hook(game.win, DestroyNotify, NoEventMask, &ft_finish, &game);
	mlx_loop(game.mlx);
	mlx_destroy_image(game.mlx, game.img.mlx_img);
	ft_finish(&game);
	return (EXIT_SUCCESS);
}
