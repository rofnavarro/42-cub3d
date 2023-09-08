/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_preparation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 13:42:49 by rferrero          #+#    #+#             */
/*   Updated: 2023/09/08 13:38:09 by rferrero         ###   ########.fr       */
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
/**********************************************************************/

void	ft_check_for_one(t_game *game, int i, int j)
{
	if (game->map.map[i][j] != '1' && game->map.map[i][j] != '0')
	{
		printf("Error\nMap from file is not closed\n");
		ft_free_matrix(game->map.config);
		ft_free_matrix(game->map.map);
		exit(EXIT_FAILURE);
	}
}

void	ft_check_ones_and_zeros(t_game *game, int i, int j)
{
	if (i == 0 || i == (ft_matrix_size(game->map.map) - 1) || \
		j == 0 || j == ft_strlen(game->map.map[i]) - 1 || \
		j >= ft_strlen(game->map.map[i]))
	{
		printf("Error\nMap from file is not closed\n");
		ft_free_matrix(game->map.config);
		ft_free_matrix(game->map.map);
		exit(EXIT_FAILURE);
	}
	ft_check_for_one(game, i - 1, j);
	ft_check_for_one(game, i + 1, j);
	ft_check_for_one(game, i, j - 1);
	ft_check_for_one(game, i, j + 1);
}

void	ft_map_is_closed(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map.map[i])
	{
		j = 0;
		while (game->map.map[i][j])
		{
			if (game->map.map[i][j] == '0')
				ft_check_ones_and_zeros(game, i, j);
			j++;
		}
		i++;
	}
}

void	ft_map_validation(t_game *game)
{
	ft_player_position(&game->player, game->map.map);
	ft_player_to_zero(&game->player, game->map.map);

	// printf("player x = %f\nplayer y = %f\nplayer direction %c\n", player->x, player->y, player->direction);
	// int i = -1;
	// while (map[++i])
	// 	printf("%s\n", map[i]);

	ft_map_is_closed(game);

	ft_player_to_direction(&game->player, game->map.map);

	// i = -1;
	// while (map[++i])
	// 	printf("%s\n", map[i]);

}

/**********************************************************************/
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

	ft_map_validation(game);

	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIN_W, WIN_H, \
								"cub3D - rinacio && rferrero");
}
