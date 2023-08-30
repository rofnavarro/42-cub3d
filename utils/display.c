#include	"../raycaster.h"

void	display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	drawMap(map);
	drawRays3D();
	drawPlayer(player);
	glutSwapBuffers();
}

void	init()
{
	map.x = 9;
	map.y = 8;
	player.x = 300;
	player.dx = cos(player.angle) * 5;
	player.y = 300;
	player.dy = sin(player.angle) * 5;
	glClearColor(0.3, 0.3, 0.3, 0);
	gluOrtho2D(0, 1024, 512, 0);
}
