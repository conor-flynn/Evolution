

#include "sources.h"
#include "Nature.h"

Nature* nature;

void display() {

	glClear(GL_COLOR_BUFFER_BIT);

	nature->update();

	glClear(GL_COLOR_BUFFER_BIT);

	vector<DPoint*>* points = &(nature->points);

	for (int i = 0; i < points->size(); i++) {

		DPoint* point = points->at(i);

	}

	glutSwapBuffers();
}

void myInit() {
	nature = new Nature();
}

int main(int argc, char** argv) {
	srand(static_cast <unsigned> (time(0)));


#if 1
	// graphics
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutInitWindowPosition(SCREEN_X, SCREEN_Y);
	glutCreateWindow("Simulation");
	glutDisplayFunc(display);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 1, -1);
	glMatrixMode(GL_MODELVIEW);
	glClearColor(1, 1, 1, 0);

	glewExperimental = GL_TRUE;
	GLenum glewError = glewInit();

	if (glewError == GLEW_OK) {
		cout << "GLUT/GLEW okay   8^)" << endl;
		myInit();
		glutMainLoop();
	}
	else {
		cout << "GLUT/GLEW failed to initialize." << endl;
	}
	// --------
#endif



	return 0;
}

