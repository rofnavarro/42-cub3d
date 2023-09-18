/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_keypress.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 16:54:23 by rinacio           #+#    #+#             */
/*   Updated: 2023/09/17 21:02:30 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_handle_keypress(int keysym, t_game *game)
{
	if (keysym == XK_Escape)
		ft_finish(game);
	else if (keysym == XK_M || keysym == XK_m)
	{
		if (game->map.toggle == 0)
			game->map.toggle = 1;
		else
			game->map.toggle = 0;
	}
	return (0);
}
