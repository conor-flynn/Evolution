#ifndef FOOD_H
#define FOOD_H

#include "sources.h"

class Food {
public:
	Food();
	int life;
	vector<Vector2> body;

	Vector2 location;

	void draw();
};

#endif