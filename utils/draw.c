#include	"../raycaster.h"

void	drawPlayer(t_player player)
{
	glColor3f(1, 1, 0);
	glPointSize(8);
	glBegin(GL_POINTS);
	glVertex2i(player.x, player.y);
	glEnd();
}

void	drawDirection(t_player player)
{
	glLineWidth(3);
	glBegin(GL_LINES);
	glVertex2i(player.x, player.y);
	glVertex2i(player.x + player.dx * 5, player.y + player.dy * 5);
	glEnd();
}

void	drawMap(t_map map)
{
	int	x;
	int	y;
	int	xo;
	int	yo;

	for (y = 0; y < map.y; y++)
	{
		for (x = 0; x < map.x; x++)
		{
			if (map.map_str[y * map.x + x] != '\n' && map.map_str[y * map.x + x] != '\0')
			{
				if (map.map_str[y * map.x + x] == '1')
					glColor3f(1, 1, 1);
				else if (map.map_str[y * map.x + x] == '0')
					glColor3f(0, 0, 0);
				xo = x * size;
				yo = y * size;
				glBegin(GL_QUADS);
				glVertex2i(xo + 1, yo + 1);
				glVertex2i(xo + 1, yo + size - 1);
				glVertex2i(xo + size - 1, yo + size - 1);
				glVertex2i(xo + size - 1, yo + 1);
				glEnd();
			}
		}
	}
}

void	drawRays3D()
{
	rays.ray_angle = fixAngle(player.angle);

	for (rays.rays = 0; rays.rays < 60; rays.rays++)
	{
		checkHorizontalLines();
		checkVerticalLines();

		checkDistance();

		glLineWidth(1);
		glBegin(GL_LINES);
		glVertex2i(player.x, player.y);
		glVertex2i(rays.ray_x, rays.ray_y);
		glEnd();

		float	dist_norm = player.angle - rays.ray_angle;
		if (dist_norm < 0)
			dist_norm += 2 * M_PI;
		if (dist_norm > 2 * M_PI)
			dist_norm -= 2 * M_PI;
		rays.dist = rays.dist * cos(dist_norm);
		float	lineH = (size * 320)/ rays.dist;
		// if (lineH > 320)
		// 	lineH = 320;
		float	lineO = 120 - lineH / 2;
		glLineWidth(8);
		glBegin(GL_LINES);
		glVertex2i(rays.rays * 8 + 530, lineO);
		glVertex2i(rays.rays * 8 + 530, lineH + lineO);
		glEnd();

		rays.ray_angle += fixAngle(rays.ray_angle - 1);

		//draw floor
		// for (int y = lineO + lineH; y < 320; y++)
		// {

		// }
	}
}
