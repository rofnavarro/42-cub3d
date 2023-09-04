#include	"../raycaster.h"

void	buttons(unsigned char key, int x, int y)
{
	if (key == 'a')
	{
		player.angle += 5;
		player.angle = fixAngle(player.angle);
		player.dx = cos(degToRad(player.angle));
		player.dy = -sin(degToRad(player.angle));
	}
	if (key == 'd')
	{
		player.angle -= 5;
		player.angle = fixAngle(player.angle);
		player.dx = cos(degToRad(player.angle));
		player.dy = -sin(degToRad(player.angle));
	}
	if (key == 'w')
	{
		player.x += player.dx * 2;
		player.y += player.dy * 2;
	}
	if (key == 's')
	{
		player.x -= player.dx * 2;
		player.y -= player.dy * 2;
	}
	glutPostRedisplay();
}

float	distance(float ax, float ay, float bx, float by, float angle)
{
	return ((cos(degToRad(angle)) * (bx - ax)) - (sin(degToRad(angle)) * (by - ay)));
}
