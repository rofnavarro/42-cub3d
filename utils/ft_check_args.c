/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 13:42:49 by rferrero          #+#    #+#             */
/*   Updated: 2023/09/05 18:44:39 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_check_args(int argc, char **argv)
{
	if (!argc || argc != 2)
	{
		printf("Error\n");
		printf("%s\n", strerror(22));
		return (EXIT_FAILURE);
	}
	else if (!ft_strchr(argv[1], '.'))
	{
		printf("Error\n");
		printf("%s or an executable\nMust use a file.cub\n", strerror(21));
		return (EXIT_FAILURE);
	}
	else if (ft_strlen(ft_strchr(argv[1], '.') + 1) != 3 || \
			ft_strncmp(ft_strchr(argv[1], '.') + 1, "cub", 3) != 0)
	{
		printf("Error\n");
		printf("%s\nWrong type of file. Must use a file.cub\n", strerror(22));
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
