/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 13:42:49 by rferrero          #+#    #+#             */
/*   Updated: 2023/09/05 17:06:23 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_check_args(int argc, char **argv)
{
	if (!argc || argc != 2)
	{
		perror("Error\nMust enter ONE map file\n");
		exit (EXIT_FAILURE);
	}
	else if (!ft_strchr(argv[1], '.'))
	{
		perror("Error\nMust enter a file map\n");
		exit (EXIT_FAILURE);
	}
	else if (ft_strlen(ft_strchr(argv[1], '.') + 1) != 3 || \
			ft_strncmp(ft_strchr(argv[1], '.') + 1, "cub", 3) != 0)
	{
		perror("Wrong type of file. Must enter a file.cub\n");
		exit (EXIT_FAILURE);
	}
}
