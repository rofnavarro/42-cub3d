/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 13:28:52 by rferrero          #+#    #+#             */
/*   Updated: 2023/09/11 18:29:24 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int render_player(t_game *game)
{
    int	i;
    int j;

    if (game->win == NULL)
        return (EXIT_FAILURE);
    i = (game->player.position.y * 24);
    while (i < ((game->player.position.y + 5) * 24))
    {
        j = (game->player.position.x * 24);
        while (j < (game->player.position.x + 5) * 24)
            mlx_pixel_put(game->mlx, game->win, j++, i, 0xFF00);
        ++i;
    }
    return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_game	game;

	ft_preparation(&game, argc, argv);

	mlx_loop_hook(game.mlx, &render_player, &game);

	mlx_loop(game.mlx);

	ft_finish(&game);
	return (EXIT_SUCCESS);
}
