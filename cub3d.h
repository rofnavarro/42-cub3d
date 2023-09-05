#ifndef		CUB3D_H
# define	CUB3D_H

//	math
# include	<math.h>
//	open()
# include	<fcntl.h>
//	close(), read(), write()
# include	<unistd.h>
//	printf(), perror()
# include	<stdio.h>
//	malloc(), free(), exit()
# include	<stdlib.h>
//	strerror()
# include	<string.h>
//	minilibX
# include	<mlx.h>
//	libft
# include	"./libft/libft.a"

//	defines
# define	WIN_W	1024
# define	WIN_H	512

//	structs
typedef	struct s_player
{
	float	x;
	float	y;
	float	dx;
	float	dy;
	float	angle;
}	t_player;

typedef	struct s_map
{
	int		x;
	int		y;
	char	*map_str;
}	t_map;

#endif
