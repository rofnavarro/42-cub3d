/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinacio <rinacio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 17:16:02 by rinacio           #+#    #+#             */
/*   Updated: 2023/09/11 18:27:54 by rinacio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_validation_exit(t_game *game, char *msg)
{
	int	i;

	printf("Error\n%s", msg);
	ft_free_matrix(game->map.config);
	ft_free_matrix(game->map.map);
	i = -1;
	while (++i)
	{
		if(game->map.textures[i])
			free(game->map.textures[i]);
	}
	free(game->map.textures);
	free(game->map.ceiling_color);
	free(game->map.floor_color);
	exit(EXIT_FAILURE);
}