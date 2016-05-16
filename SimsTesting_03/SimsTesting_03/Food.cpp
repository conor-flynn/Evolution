#include "Food.h"



Food::Food() {
	life = 0;
	int size = 10;
	body.push_back(Vector2(-size, -size));
	body.push_back(Vector2(-size, size));
	body.push_back(Vector2(size, size));
	body.push_back(Vector2(size, -size));
}

void Food::draw() {

	glBegin(GL_POLYGON);

	for (Vector2 vv : body) {
		Vector2 v = vv.add(location);
		glColor3f(0, 1, 0);
		glVertex2f(v.getX(), v.getY());
	}

	glEnd();
}

