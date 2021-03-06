

#include "sources.h"
#include "Nature.h"

Nature* nature;

void drawit(float lx, float ly, float hx, float hy, float x1, float y1, float x2, float y2) {
	float xdiff = hx - lx;
	float ydiff = hy - ly;

	float nx1 = (x1 / xdiff) * SCREEN_DEBUG_WIDTH;
	float ny1 = (y1 / ydiff) * SCREEN_DEBUG_HEIGHT * 0.95f;
	ny1 = (SCREEN_MAIN_HEIGHT + SCREEN_DEBUG_HEIGHT) - ny1;

	float nx2 = (x2 / xdiff) * SCREEN_DEBUG_WIDTH;
	float ny2 = (y2 / ydiff) * SCREEN_DEBUG_HEIGHT * 0.95f;
	ny2 = (SCREEN_MAIN_HEIGHT + SCREEN_DEBUG_HEIGHT) - ny2;

	glVertex2f(nx1, ny1);
	glVertex2f(nx2, ny2);
	glEnd();
}

void drawData() {
	vector<DPoint*>* points = &(nature->points);
	if (points->size() == 0) return;

	float miny = RAND_MAX;
	float maxy = -1;

	for (int i = 0; i < points->size(); i++) {

		DPoint* point = points->at(i);

		for (int j = 0; j < 3; j++) {
#if 0
			float v1 = point->mean[j];
			float v2 = point->max[j];

			float max = (v1 >= v2) ? v1 : v2;
			float min = (v1 >= v2) ? v2 : v1;

			if (min < miny) miny = min;
			if (max > maxy) maxy = max;
#endif
#if 1
			float v1 = point->mean[j];
			if (v1 < miny) miny = v1;
			if (v1 > maxy) maxy = v1;
#endif
		}
	}

	/*
	You want miny to be larger than 0
	You want maxy to be smaller than it can be
	*/

	float ly = miny;
	float hy = maxy;

	float lx = 0;
	float hx = points->size() + 1;

	for (int i = 0; i < points->size() - 1; i++) {

		DPoint* current = points->at(i);
		DPoint* next = points->at(i + 1);

		for (int j = 0; j < 3; j++) {
			// Mean
			glBegin(GL_LINES);
			switch (j) {
			case 0:
				glColor3f(0, 1, 0);
				break;
			case 1:
				glColor3f(0, 0, 1);
				break;
			case 2:
				glColor3f(1, 0, 0);
				break;
			default:
				break;
			}
			float x1 = i;
			float y1 = current->mean[j];

			float x2 = i + 1;
			float y2 = next->mean[j];

			drawit(lx, ly, hx, hy, x1, y1, x2, y2);
		}
#if 0
		for (int j = 0; j < 3; j++) {
			// Max
			glBegin(GL_LINES);
			glColor3f(0, 0, 1);
			float x1 = i;
			float y1 = current->max[j];

			float x2 = i + 1;
			float y2 = next->max[j];

			drawit(lx, ly, hx, hy, x1, y1, x2, y2);
		}
#endif
	}
}

void display() {

	glClear(GL_COLOR_BUFFER_BIT);
	nature->update();

	// =~ =~ =~ =~ =~ =~ =~ =~ =~ =~ =~ =~ =~ =~ =~ =~ =~ =~ =~ 
	drawData();
	// =~ =~ =~ =~ =~ =~ =~ =~ =~ =~ =~ =~ =~ =~ =~ =~ =~ =~ =~ 
	
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
	glutInitWindowSize(SCREEN_MAIN_WIDTH, SCREEN_MAIN_HEIGHT + SCREEN_DEBUG_HEIGHT);
	glutInitWindowPosition(SCREEN_X, SCREEN_Y);
	glutCreateWindow("Simulation");
	glutDisplayFunc(display);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, SCREEN_MAIN_WIDTH, SCREEN_MAIN_HEIGHT + SCREEN_DEBUG_HEIGHT, 0, 1, -1);
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

