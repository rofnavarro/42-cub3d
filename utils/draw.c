#include	"../raycaster.h"

void	drawPlayer(t_player player)
{
	glColor3f(1, 1, 0);
	glPointSize(8);
	glBegin(GL_POINTS);
	glVertex2i(player.x, player.y);
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
			}
		}
	}
}
