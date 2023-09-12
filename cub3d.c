/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 13:28:52 by rferrero          #+#    #+#             */
/*   Updated: 2023/09/12 13:16:26 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;

	ft_preparation(&game, argc, argv);
	mlx_key_hook(game.win, &ft_handle_keypress, &game);
	mlx_hook(game.win, DestroyNotify, NoEventMask, &ft_finish, &game);
	mlx_loop_hook(game.mlx, &ft_draw_handler, &game);
	mlx_loop(game.mlx);

	ft_finish(&game);
	return (EXIT_SUCCESS);
}
