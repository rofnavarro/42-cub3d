#include	"raycaster.h"

t_player	player;
t_map		map;
t_rays		rays;

int	main(int argc, char **argv)
{
	if (argc == 2)
		map.map_str = read_map(argv[1]);
	else
		return (EXIT_FAILURE);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(WIN_W, WIN_H);
	glutCreateWindow("raycaster - 3D");
	init();
	glutDisplayFunc(display);
	glutKeyboardFunc(buttons);
	glutMainLoop();
}
