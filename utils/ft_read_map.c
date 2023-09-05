/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 14:48:44 by rferrero          #+#    #+#             */
/*   Updated: 2023/09/05 17:27:19 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*ft_read_map(t_game *game, char argv[])
{
	char	*map_str;
	char	*tmp;
	int		fd;

	map_str = ft_strdup("");
	fd = open(argv, O_RDONLY);
	if (fd < 0)
	{
		free(map_str);
		perror("Error\nFile broken or does not exist.\n");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		tmp = get_next_line(fd);
		if (!tmp)
		{
			free(tmp);
			break ;
		}
		map_str = ft_strjoin_free(map_str, tmp);
		free(tmp);
	}
	close(fd);
	return (map_str);
}
