#ifndef NATURE_H
#define NATURE_H

#include "sources.h"
#include "Creature.h"
#include "Food.h"
#include "Store.h"
#include "Dictionary.h"


class Nature {
public:
	Nature();

	int gen;
	int generation;
	int evolution[3][3];
	vector<DPoint*> points;

	vector<vector<Creature*>> creatures;

	vector<Food*> foods;

	void evolve(vector<Creature*>* group, int speciesIndex, DPoint* point);

	void setVision(vector<Vector2> eyes, Creature* source, vector<float>* inputs);
	void senseArea(Creature* source, vector<float>* inputs);


	void update();
};

#endif