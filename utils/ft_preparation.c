/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_preparation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 13:42:49 by rferrero          #+#    #+#             */
/*   Updated: 2023/09/07 15:16:05 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_check_args(int argc, char **argv)
{
	if (!argc || argc != 2)
	{
		printf("Error\n%s\n", strerror(22));
		exit(EXIT_FAILURE);
	}
	else if (!ft_strchr(argv[1], '.'))
	{
		printf("Error\n%s or an executable\nMust use a file.cub\n", strerror(21));
		exit(EXIT_FAILURE);
	}
	else if (ft_strlen(ft_strchr(argv[1], '.') + 1) != 3 || \
			ft_strncmp(ft_strchr(argv[1], '.') + 1, "cub", 3) != 0)
	{
		printf("Error\n");
		printf("%s\nWrong type of file. Must use a file.cub\n", strerror(22));
		exit(EXIT_FAILURE);
	}
}

void	ft_empty_map(t_game *game)
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

void	ft_preparation(t_game *game, int argc, char **argv)
{
	ft_check_args(argc, argv);
	game->map.map_str = ft_read_map(game, argv[1]);
	ft_empty_map(game);
	game->map.matrix = ft_split(game->map.map_str, '\n');
	free(game->map.map_str);
	game->map.config = ft_map_config(game);
	game->map.map = ft_map_map(game);
	ft_free_matrix(game->map.matrix);
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIN_W, WIN_H, \
								"cub3D - rinacio && rferrero");
}
