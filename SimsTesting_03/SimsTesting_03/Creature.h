#ifndef CREATURE_H
#define CREATURE_H

#include "sources.h"
#include "Brain.h"

class Creature {
public:
	Creature();

	int description;

	string brainInfo;

	float eyeWidth;
	float eyeLength;

	Vector2 drawPoint;
	float currentRandom;


	Brain* brain;
	int food;
	float lastFoodCounter;

	float direction;
	Vector2 location;

	vector<Vector2> eyes;
	vector<Vector2> body;

	//vector<Vector2> getLeftVision();
	//vector<Vector2> getRightVision();
	vector<Vector2> getVision();

	// Set outputs
	void process(vector<float> inputs);

	// Move outputs to real outputs
	vector<Vector2> getVertices();
	void update();

	// Draw creature based on changed location
	void draw();
};

#endif