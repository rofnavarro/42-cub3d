/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 14:48:44 by rferrero          #+#    #+#             */
/*   Updated: 2023/09/05 14:56:22 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	ft_empty_map(t_game *game, char *map)
{
	int	i;

	i = 0;
	if (map[i] == '\0')
	{
		free(map);
		printf("Empty map.\n");
		exit(EXIT_FAILURE);
	}
	while (map[i])
	{
		if (map[i] == '\n' && map[i + 1] != '1')
		{
			free(map);
			printf("Invalid map.\n");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

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
		printf("File broken or does not exist.\n");
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
	free(tmp);
	close(fd);
	ft_empty_map(game, map_str);
	return (map_str);
}
