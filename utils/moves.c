#include	"../raycaster.h"

void	buttons(unsigned char key, int x, int y)
{
	if (key == 'a')
		player.x -= 5;
	else if (key == 'd')
		player.x += 5;
	else if (key == 'w')
		player.y -= 5;
	else if (key == 's')
		player.y += 5;
	glutPostRedisplay();
}