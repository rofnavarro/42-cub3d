#include	"../raycaster.h"

void	display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	drawMap(map);
	drawPlayer(player);
	glutSwapBuffers();
}

void	init()
{
	glClearColor(0.3, 0.3, 0.3, 0);
	gluOrtho2D(0, 1024, 448, 0);
	player.x = 300;
	player.y = 300;
	map.x = 9;
	map.y = 7;
}
