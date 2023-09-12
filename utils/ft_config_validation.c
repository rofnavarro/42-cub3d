/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_config_validation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinacio <rinacio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 16:41:48 by rinacio           #+#    #+#             */
/*   Updated: 2023/09/12 16:30:55 by rinacio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_config_validation(t_game *game)
{
	int		i;
	char	**line;

	game->map.textures = ft_matrix_calloc(5);
	game->map.ceiling_color = (int *)malloc(sizeof(int) * 3);
	game->map.floor_color = (int *)malloc(sizeof(int) * 3);
	if (!game->map.textures || !game->map.ceiling_color
		|| !game->map.floor_color)
		ft_validation_exit(game, "Memory allocation failed\n");
	i = -1;
	while (game->map.config[++i])
	{
		line = ft_split(game->map.config[i], ' ');
		if (ft_matrix_size(line) != 2)
		{
			ft_free_matrix(line);
			ft_validation_exit(game, "Invalid map configuration\n");
		}
		ft_get_map_config(game, line);
		ft_free_matrix(line);
	}
	game->map.textures[4] = NULL;
	ft_check_valid_texture_path(game, game->map.textures);
}

void	ft_get_map_config(t_game *game, char **line)
{
	if (!ft_strncmp(line[0], "NO", 2) && ft_strlen(line[0]) == 2)
		ft_populate_path_array(game, line, NO);
	else if (!ft_strncmp(line[0], "SO", 2) && ft_strlen(line[0]) == 2)
		ft_populate_path_array(game, line, SO);
	else if (!ft_strncmp(line[0], "EA", 2) && ft_strlen(line[0]) == 2)
		ft_populate_path_array(game, line, EA);
	else if (!ft_strncmp(line[0], "WE", 2) && ft_strlen(line[0]) == 2)
		ft_populate_path_array(game, line, WE);
	else if (!ft_strncmp(line[0], "F", 1) && ft_strlen(line[0]) == 1)
		ft_check_rgb(game, line, game->map.floor_color);
	else if (!ft_strncmp(line[0], "C", 1) && ft_strlen(line[0]) == 1)
		ft_check_rgb(game, line, game->map.ceiling_color);
	else
	{
		ft_free_matrix(line);
		ft_validation_exit(game, "Invalid map configuration\n");
	}
}

void	ft_populate_path_array(t_game *game, char **line, int i)
{
	if (game->map.textures[i])
	{
		ft_free_matrix(line);
		ft_validation_exit(game, "Invalid map configuration\n");
	}
	game->map.textures[i] = ft_strdup(line[1]);
}

void	ft_check_valid_texture_path(t_game *game, char **path)
{
	int		fd;
	int		i;

	i = -1;
	while (path[++i])
	{
		fd = open(path[i], O_RDONLY);
		if (fd < 0)
			ft_validation_exit(game, "Invalid texture path\n");
	}
}

void	ft_check_rgb(t_game *game, char **rgb, int *color)
{
	char	**color_matrix;
	int		i;

	color_matrix = ft_split(rgb[1], ',');
	if (ft_matrix_size(color_matrix) != 3 || !ft_is_numeric(color_matrix))
	{
		ft_free_matrix(color_matrix);
		ft_free_matrix(rgb);
		ft_validation_exit(game, "Invalid RGB color\n");
	}
	i = -1;
	while (++i < 3)
	{
		color[i] = ft_atoi(color_matrix[i]);
		if (color[i] < 0 || color[i] > 255)
		{
			ft_free_matrix(color_matrix);
			ft_free_matrix(rgb);
			ft_validation_exit(game, "Invalid RGB color\n");
		}
	}
	ft_free_matrix(color_matrix);
}
