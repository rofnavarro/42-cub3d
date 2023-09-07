/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 13:28:52 by rferrero          #+#    #+#             */
/*   Updated: 2023/09/07 15:27:22 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;

	ft_preparation(&game, argc, argv);

	// int i = -1;
	// while (game.map.config[++i])
	// 	printf("%s\n", game.map.config[i]);
	// i = -1;
	// while (game.map.map[++i])
	// 	printf("%s\n", game.map.map[i]);

	ft_finish(&game);
	return (EXIT_SUCCESS);
}
