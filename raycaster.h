#ifndef		RAYCASTER_H
# define	RAYCASTER_H

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

//	openGL lib
# include	<GL/gl.h>
# include	<GL/glu.h>
# include	<GL/glut.h>

//	defines
# define	WIN_W	1024
# define	WIN_H	512

# define	PI		3.1415926535
# define	P2		PI/2
# define	P3		3*PI/2
# define	DG		0.0174533

# define	size	64

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

typedef struct s_rays
{
	int		rays;
	int		map_x;
	int		map_y;
	int		map_pos;
	int		dept_of_field;
	float	ray_x;
	float	ray_y;
	float	ray_angle;
	float	xo;
	float	yo;
	float	distH;
	float	hx;
	float	hy;
	float	distV;
	float	vx;
	float	vy;
	float	dist;
}	t_rays;

//	globals
extern	t_player	player;
extern	t_map		map;
extern	t_rays		rays;

//	utils/check_lines.c
void    checkHorizontalLines();
void    checkVerticalLines();

//	ultils/display.c
void	display();
void	init();

//	utils/draw.c
void	drawPlayer(t_player player);
void	drawMap(t_map map);
void	drawRays3D();

//	utils/moves.c
void	buttons(unsigned char key, int x, int y);
float	distance(float ax, float ay, float bx, float by, float angle);

//	ultils/read_map.c
char	*read_map(char *map);

#endif