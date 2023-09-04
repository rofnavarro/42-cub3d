#include	"../raycaster.h"

void	display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	drawMap(map);
	drawPlayer(player);
	drawDirection(player);
	drawRays3D();

	glutSwapBuffers();
}

void	init()
{
	map.x = 8;
	map.y = 8;
	player.angle = 90;
	player.x = 400;
	player.dx = cos(degToRad(player.angle));
	player.y = 300;
	player.dy = -sin(degToRad(player.angle));
	glClearColor(0.3, 0.3, 0.3, 0);
	gluOrtho2D(0, 1024, 512, 0);
}
