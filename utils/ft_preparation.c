/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_preparation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinacio <rinacio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 13:42:49 by rferrero          #+#    #+#             */
/*   Updated: 2023/09/11 16:51:24 by rinacio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	ft_check_args(int argc, char **argv)
{
	if (!argc || argc != 2)
	{
		printf("Error\n%s\n", strerror(22));
		exit(EXIT_FAILURE);
	}
	else if (!ft_strchr(argv[1], '.'))
	{
		printf("Error\n%s or an executable\nMust use a file.cub\n", \
				strerror(21));
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

static void	ft_empty_map(char **str)
{
	int	i;

	i = 0;
	if (*(str[i]) == '\0')
	{
		free(*(str));
		printf("Error\n%s but it is an empty file\n", strerror(17));
		exit(EXIT_FAILURE);
	}
}

void	ft_map_validation(t_game *game)
{
	ft_check_characters(game);
	ft_player_position(&game->player, game->map.map);
	ft_player_to_zero(&game->player, game->map.map);
	ft_map_is_closed(game);
	ft_player_to_direction(&game->player, game->map.map);
}

void	ft_preparation(t_game *game, int argc, char **argv)
{
	char	*str;
	char	**matrix;

	ft_check_args(argc, argv);
	str = ft_read_map(game, argv[1]);
	ft_empty_map(&str);
	matrix = ft_split(str, '\n');
	free(str);
	game->map.map = ft_map_map(matrix);
	game->map.config = ft_map_config(matrix);
	ft_free_matrix(matrix);
	ft_config_validation(game);
	ft_map_validation(game);
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIN_W, WIN_H, \
								"cub3D - rinacio && rferrero");
}
