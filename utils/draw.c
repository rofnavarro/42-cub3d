#include	"../raycaster.h"

void	drawPlayer(t_player player)
{
	//	player
	glColor3f(1, 1, 0);
	glPointSize(8);
	glBegin(GL_POINTS);
	glVertex2i(player.x, player.y);
	glEnd();
	//	direction
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
	rays.ray_angle = player.angle;
	for (rays.rays = 0; rays.rays < 1; rays.rays++)
	{
		//	horizontal lines
		rays.dept_of_field = 0;
		float	aTan = -1/tan(rays.ray_angle);
		//	looking down
		if (rays.ray_angle > PI)
		{
			rays.ray_y = (((int)player.y>>6)<<6) - 0.0001;
			rays.ray_x = (player.y - rays.ray_y) * aTan + player.x;
			rays.yo = -64;
			rays.xo = -rays.yo * aTan;
		}
		//	looking up
		if (rays.ray_angle < PI)
		{
			rays.ray_y = (((int)player.y>>6)<<6) + 64;
			rays.ray_x = (player.y - rays.ray_y) * aTan + player.x;
			rays.yo = 64;
			rays.xo = -rays.yo * aTan;
		}
		//	looking left or right
		if (rays.ray_angle == 0 || rays.ray_angle == PI)
		{
			rays.ray_x = player.x;
			rays.ray_y = player.y;
			rays.dept_of_field = 8;
		}
		while (rays.dept_of_field < 8)
		{
			rays.map_x = (int)(rays.ray_x)>>6;
			rays.map_y = (int)(rays.ray_y)>>6;
			rays.map_pos = rays.map_y * map.x + rays.map_x;
			if (rays.map_pos < map.x * map.y && map.map_str[rays.map_pos] == '1')
				rays.dept_of_field = 8;
			else
			{
				rays.ray_x += rays.xo;
				rays.ray_y += rays.yo;;
				rays.dept_of_field += 1;
			}
		}
		glColor3f(0, 1, 0);
		glLineWidth(1);
		glBegin(GL_LINES);
		glVertex2i(player.x, player.y);
		glVertex2i(rays.ray_x, rays.ray_y);
		glEnd();
	}
}
