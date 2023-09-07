/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 14:48:44 by rferrero          #+#    #+#             */
/*   Updated: 2023/09/07 14:44:34 by rferrero         ###   ########.fr       */
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
		printf("Error\n%s\n", strerror(2));
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

char	**ft_map_config(t_game	*game)
{
	int		i;
	char	**ret_config;

	i = 0;
	ret_config = ft_matrix_calloc(7);
	while (i < 6)
	{
		ret_config[i] = ft_strdup(game->map.matrix[i]);
		i++;
	}
	return (ret_config);
}

char	**ft_map_map(t_game *game)
{
	int		i;
	char	**ret_map;

	i = ft_matrix_size(game->map.matrix) - 6;
	ret_map = ft_matrix_calloc(i);
	i = 6;
	while (i < ft_matrix_size(game->map.matrix) - 1)
	{
		ret_map[i - 6] = ft_strdup(game->map.matrix[i]);
		i++;
	}
	return (ret_map);
}
