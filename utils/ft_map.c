/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 17:25:07 by rferrero          #+#    #+#             */
/*   Updated: 2023/09/05 18:57:30 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	ft_empty_map(t_game *game)
{
	int	i;

	i = 0;
	if (game->map.map_str[i] == '\0')
	{
		free(game->map.map_str);
		printf("Error\n%s but it is an empty file\n", strerror(17));
		exit(EXIT_FAILURE);
	}
}

static int	ft_is_closed_h(t_game *game)
{

}

static int	ft_is_closed_v(t_game *game)
{

}

void	ft_validate_map(t_game *game)
{
	ft_empty_map(game);
}
