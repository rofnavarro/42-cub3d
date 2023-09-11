/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_config_validation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinacio <rinacio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 16:41:48 by rinacio           #+#    #+#             */
/*   Updated: 2023/09/11 18:30:41 by rinacio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_config_validation(t_game *game)
{
	int		i;
	char	**line;

	//FIXME: Memory leaks

	game->map.textures = (char **)malloc(sizeof(char *) * 4);
	game->map.ceiling_color = (int *)malloc(sizeof(int) * 3);
	game->map.floor_color = (int *)malloc(sizeof(int) * 3);
	if (!game->map.textures || !game->map.ceiling_color || !game->map.floor_color)
		ft_validation_exit(game, "Memory allocation failed\n");
	i = -1;
	while (game->map.config[++i])
	{
		line = ft_split(game->map.config[i], ' ');
		if (count_matrix_lines(line) != 2)
			ft_validation_exit(game, "Invalid map configuration\n");
		ft_get_map_config(game, line);
		free(line);
	}
	
	printf("NO: %s\n", game->map.textures[0]);
	printf("SO: %s\n", game->map.textures[1]);
	printf("WE: %s\n", game->map.textures[2]);
	printf("EA: %s\n", game->map.textures[3]);
	printf("Celing RGB: %d %d %d\n", game->map.ceiling_color[0], game->map.ceiling_color[1], game->map.ceiling_color[2]);
	printf("Floor RGB: %d %d %d\n", game->map.floor_color[0], game->map.floor_color[1], game->map.floor_color[2]);
}

void	ft_get_map_config(t_game *game, char **line)
{
	if (!ft_strncmp(line[0], "NO", 2) && ft_strlen(line[0]) == 2)
		ft_check_valid_texture_path(game, line[1], &game->map.textures[0]);
	else if (!ft_strncmp(line[0], "SO", 2) && ft_strlen(line[0]) == 2)
		ft_check_valid_texture_path(game, line[1], &game->map.textures[1]);
	else if (!ft_strncmp(line[0], "WE", 2) && ft_strlen(line[0]) == 2)
		ft_check_valid_texture_path(game, line[1], &game->map.textures[2]);
	else if (!ft_strncmp(line[0], "EA", 2) && ft_strlen(line[0]) == 2)
		ft_check_valid_texture_path(game, line[1], &game->map.textures[3]);
	else if (!ft_strncmp(line[0], "F", 1) && ft_strlen(line[0]) == 1)
		ft_check_rgb(game, line[1], game->map.floor_color);
	else if (!ft_strncmp(line[0], "C", 1) && ft_strlen(line[0]) == 1)
		ft_check_rgb(game, line[1], game->map.ceiling_color);
	else
		printf("erro\n");
}

void	ft_check_valid_texture_path(t_game *game, char *path, char **config)
{
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		ft_validation_exit(game, "Invalid texture path\n");
	*config = ft_strdup(path);
}

int	ft_is_numeric(char **matrix)
{
	int	i;
	int	j;

	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (matrix[i][++j])
		{
			if (!ft_isdigit(matrix[i][j]))
				return (0);
		}
	}
	return (1);
}

void	ft_check_rgb(t_game *game, char *rgb, int *color)
{
	char **color_matrix;	printf("%d %d %d\n", game->map.ceiling_color[0], game->map.ceiling_color[1], game->map.ceiling_color[2]);
	printf("%d %d %d\n", game->map.floor_color[0], game->map.floor_color[1], game->map.floor_color[2]);
	int	i;

	color_matrix = ft_split(rgb, ',');
	if (count_matrix_lines(color_matrix) != 3)
		ft_validation_exit(game, "Invalid RGB color\n");
	if(!ft_is_numeric(color_matrix))
		ft_validation_exit(game, "Invalid RGB color\n");
	i = -1;
	while (++i < 3)
	{
		color[i] = ft_atoi(color_matrix[i]);
		if(color[i] < 0 || color[i] > 255)
			ft_validation_exit(game, "Invalid RGB color\n");
	}
	free(color_matrix);
}

int	count_matrix_lines(char **matrix)
{
	int	i;
	int	lines;

	lines = 0;
	i = -1;
	while (matrix[++i] != NULL)
		lines++;
	return (lines);
}
