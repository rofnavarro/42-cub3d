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
	rays.ray_angle = player.angle - DG * 30;
	if (rays.ray_angle < 0)
	{
		rays.ray_angle += 2 * PI;
	}
	if (rays.ray_angle > 2 * PI)
	{
		rays.ray_angle -= 2 * PI;
	}
	for (rays.rays = 0; rays.rays < 60; rays.rays++)
	{
		//	horizontal lines
		rays.dept_of_field = 0;
		float	distH = 10000000;
		float	hx = player.x;
		float	hy = player.y;
		float	hTan = -1/tan(rays.ray_angle);
		//	looking down
		if (rays.ray_angle > PI)
		{
			rays.ray_y = (((int)player.y>>6)<<6) - 0.0001;
			rays.ray_x = (player.y - rays.ray_y) * hTan + player.x;
			rays.yo = -64;
			rays.xo = -rays.yo * hTan;
		}
		//	looking up
		if (rays.ray_angle < PI)
		{
			rays.ray_y = (((int)player.y>>6)<<6) + 64;
			rays.ray_x = (player.y - rays.ray_y) * hTan + player.x;
			rays.yo = 64;
			rays.xo = -rays.yo * hTan;
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
			if (rays.map_pos > 0 && rays.map_pos < map.x * map.y && map.map_str[rays.map_pos] == '1')
			{
				hx = rays.ray_x;
				hy = rays.ray_y;
				distH = distance(player.x, player.y, hx, hy, rays.ray_angle);
				rays.dept_of_field = 8;
			}
			else
			{
				rays.ray_x += rays.xo;
				rays.ray_y += rays.yo;
				rays.dept_of_field += 1;
			}
		}

		//	vertical lines
		rays.dept_of_field = 0;
		float	distV = 10000000;
		float	vx = player.x;
		float	vy = player.y;
		float	vTan = -tan(rays.ray_angle);
		//	looking left
		if (rays.ray_angle > P2 && rays.ray_angle < P3)
		{
			rays.ray_x = (((int)player.x>>6)<<6) - 0.0001;
			rays.ray_y = (player.x - rays.ray_x) * vTan + player.y;
			rays.xo = -64;
			rays.yo = -rays.xo * vTan;
		}
		//	looking right
		if (rays.ray_angle < P2 || rays.ray_angle > P3)
		{
			rays.ray_x = (((int)player.x>>6)<<6) + 64;
			rays.ray_y = (player.x - rays.ray_x) * vTan + player.y;
			rays.xo = 64;
			rays.yo = -rays.xo * vTan;
		}
		//	looking up or down
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
			if (rays.map_pos > 0 && rays.map_pos < map.x * map.y && map.map_str[rays.map_pos] == '1')
			{
				vx = rays.ray_x;
				vy = rays.ray_y;
				distV = distance(player.x, player.y, vx, vy, rays.ray_angle);
				rays.dept_of_field = 8;
			}
			else
			{
				rays.ray_x += rays.xo;
				rays.ray_y += rays.yo;
				rays.dept_of_field += 1;
			}
		}
		if (distV < distH)
		{
			rays.ray_x = vx;
			rays.ray_y = vy;
			rays.dist = distV;
			glColor3f(0.9, 0, 0);
		}
		if (distH < distV)
		{
			rays.ray_x = hx;
			rays.ray_y = hy;
			rays.dist = distH;
			glColor3f(0.7, 0, 0);
		}
		glLineWidth(1);
		glBegin(GL_LINES);
		glVertex2i(player.x, player.y);
		glVertex2i(rays.ray_x, rays.ray_y);
		glEnd();

		float	dist_norm = player.angle - rays.ray_angle;
		if (dist_norm < 0)
		{
			dist_norm += 2 * PI;
		}
		if (dist_norm > 2 * PI)
		{
			dist_norm -= 2 * PI;
		}
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

		rays.ray_angle += DG;
		if (rays.ray_angle < 0)
		{
			rays.ray_angle += 2 * PI;
		}
		if (rays.ray_angle > 2 * PI)
		{
			rays.ray_angle -= 2 * PI;
		}

		//draw floor
		// for (int y = lineO + lineH; y < 320; y++)
		// {

		// }
	}
}
