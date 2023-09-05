/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 17:25:07 by rferrero          #+#    #+#             */
/*   Updated: 2023/09/05 17:28:43 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	ft_empty_map(t_game *game)
{
	int	i;

	i = 0;
	if (game->map.map_str[i] == '\0')
	{
		free(game->map.map_str);
		perror("Error\nEmpty map");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	ft_is_closed_h(t_game *game)
{

}

static int	ft_is_closed_v(t_game *game)
{
	
}

int	ft_validate_map(t_game *game)
{
	if (ft_empty_map(game) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
