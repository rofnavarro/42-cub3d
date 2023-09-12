/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 21:42:23 by rferrero          #+#    #+#             */
/*   Updated: 2023/09/12 12:55:50 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	render_background(t_game *game)
{
    int	i;
    int	j;

    if (game->win == NULL)
        return (EXIT_FAILURE);
    i = 0;
    while (i < WIN_H)
    {
        j = 0;
        while (j < WIN_W)
            mlx_pixel_put(game->mlx, game->win, j++, i, 0x000000);
        ++i;
    }
}

static int render_player(t_game *game)
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
            mlx_pixel_put(game->mlx, game->win, j++, i, 0xFFFFFF);
        ++i;
    }
    return (EXIT_SUCCESS);
}

int	ft_draw_handler(t_game *game)
{
	if (render_player(game) == EXIT_FAILURE)
	{
		printf("Error\nFail to render player\n");
		ft_free_matrix(game->map.config);
		ft_free_matrix(game->map.map);
		exit(EXIT_FAILURE);
	}
	if (render_background(game) == EXIT_FAILURE)
	{
		printf("Error\nFail to render background\n");
		ft_free_matrix(game->map.config);
		ft_free_matrix(game->map.map);
		exit(EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
