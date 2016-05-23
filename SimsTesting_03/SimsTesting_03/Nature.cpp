#include "Nature.h"

Nature::Nature() {

	gen = 0;
	generation = 0;

	int num_species = 3;
	int num_creatures_per_species = 10;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			evolution[i][j] = 0;
		}
	}

	vector<vector<int>> species;


	species.push_back(vector<int>
		{
			NUMBER_INPUTS, 
			15, 
			15,
			NUMBER_OUTPUTS
		});

	species.push_back(vector<int>
		{
			NUMBER_INPUTS, 
			15,
			15,
			NUMBER_OUTPUTS
		});

	species.push_back(vector<int>
		{
			NUMBER_INPUTS, 
			15,
			15,
			NUMBER_OUTPUTS
		});

	//species.push_back(vector<int>{_inputs, _inputs + 1, _inputs / 2, _inputs / 4, _outputs});
	//species.push_back(vector<int>{_inputs, _inputs + 1, _inputs, _outputs});
	//species.push_back(vector<int>{_inputs, _inputs / 2, _inputs / 4, _outputs});


	for (int i = 0; i < species.size(); i++) {
		creatures.push_back(vector<Creature*>());

		for (int k = 0; k < num_creatures_per_species; k++) {
			Creature* creature = new Creature();
			int x, y;
			x = xrandomi(0, SCREEN_MAIN_WIDTH);
			y = xrandomi(0, SCREEN_MAIN_HEIGHT);

			creature->location = Vector2(x, y);
			creature->direction = xrandomf(0, 360);

			creature->brain = new Brain(species[i]);

			stringstream ss;
			for (int j = 0; j < species[i].size(); j++) {
				ss << species[i][j];
				if (j + 1 != species[i].size()) {
					ss << ", ";
				}
				creature->brainInfo = ss.str();
			}
			creatures[i].push_back(creature);
		}
	}

	for (int i = 0; i < 80; i++) {
		Food* food = new Food();

		int x, y;
		x = xrandomi(0, SCREEN_MAIN_WIDTH);
		y = xrandomi(0, SCREEN_MAIN_HEIGHT);

		food->location = Vector2(x, y);

		foods.push_back(food);
	}
}

void Nature::evolve(vector<Creature*>* group, int speciesIndex, DPoint* point) {

	vector<pair<int, Creature*>> order(group->size());

	Store<int> indices;

	for (int i = 0; i < group->size(); i++) {
		int min = RAND_MAX;
		int index = -1;
		for (int j = 0; j < group->size(); j++) {
			if (indices.contains(j)) continue;
			if (group->at(j)->food <= min) {
				min = group->at(j)->food;
				index = j;
			}
		}
		indices.add(index);
		order[i] = pair<int, Creature*>(min, group->at(index));

		int x, y; x = xrandomi(0, SCREEN_MAIN_WIDTH); y = xrandomi(0, SCREEN_MAIN_HEIGHT);
		order[i].second->location = Vector2(x, y);
		order[i].second->direction = xrandomf(0, 360);
		order[i].second->food = 0;
	}
	int index = order[order.size() - 1].second->description;
	evolution[speciesIndex][index]++;

	order[order.size() - 1].second->description = Generation::TopCreature;
	for (int i = 5; i < order.size()-1; i++) {
		order[i].second->description = Generation::Original;
	}

	// Non crazy mutations
#if 1
	for (int i = 0; i < 5; i++) {
		Creature* worst = order[i].second;
		Creature* best = order[order.size() - 1].second;

		delete worst->brain;
		worst->brain = NULL;
		worst->brain = new Brain(best->brain);
		worst->brain->mutate();

		worst->description = Generation::MutatedCreature;

		while (chance(5 * i)) {
			worst->brain->mutate();
		}
	}
#endif


	// Volatile mutations
#if 0
	for (int i = 0; i < order.size(); i++) {
		Creature* worst = order[i].second;
		Creature* best = order[order.size() - 1 - i].second;

		if (worst == best) {
			break;
		}

		int x, y; x = xrandomi(0, SCREEN_WIDTH); y = xrandomi(0, SCREEN_HEIGHT);

		worst->location = Vector2(x, y);
		worst->direction = xrandomf(0, 360);

		delete worst->brain;
		worst->brain = NULL;
		worst->brain = new Brain(best->brain);
		worst->brain->mutate();
	}
#endif

	float sum = 0;
	for (int i = 0; i < order.size(); i++) {
		sum += order[i].first;
	}
	sum /= ((float)order.size());


	cout << "Species : " << group->at(0)->brainInfo << endl;
	cout << "\tWorst    : " << order[0].first << endl;
	cout << "\tAverage  : " << sum << endl;
	cout << "\tBest     : " << order[order.size() - 1].first << endl;
	cout << "\tProgress : " << endl;

	int orig = evolution[speciesIndex][Generation::Original];
	int top = evolution[speciesIndex][Generation::TopCreature];
	int mut = evolution[speciesIndex][Generation::MutatedCreature];

	cout << "\t\tMutated Creature   : " << mut << endl;
	cout << "\t\tOriginal Creature  : " << orig << endl;
	cout << "\t\tTop Creature       : " << top << endl;

	point->mean[speciesIndex] = sum;
	point->max[speciesIndex] = order[order.size() - 1].first;

#if 0
	int indexMax = 0;
	int maxFood = -1;

	int indexMin = 0;
	int leastFood = RAND_MAX;

	float foodAverage = 0;

	for (int i = 0; i < group->size(); i++) {

		foodAverage += group->at(i)->food;

		if (group->at(i)->food > maxFood) {
			indexMax = i;
			maxFood = group->at(i)->food;
		}

		if (group->at(i)->food < leastFood) {
			indexMin = i;
			leastFood = group->at(i)->food;
		}	
	}

	if (indexMax != indexMin) {

		Creature* worst = group->at(indexMin);
		Creature* best = group->at(indexMax);
		//Creature* mutant = new Creature();

		int x, y; x = xrandomi(0, SCREEN_WIDTH); y = xrandomi(0, SCREEN_HEIGHT);

		worst->location = Vector2(x, y);
		worst->direction = xrandomf(0, 360);

		delete worst->brain;
		worst->brain = NULL;
		worst->brain = new Brain(best->brain);
		worst->brain->mutate();



		////group.erase(group.begin() + indexMin);
		////delete worst;
		////group.push_back(mutant);

		//delete group->at(indexMin);
		//group->erase(group->begin() + indexMin);
		//group->push_back(mutant);
		
	}

	for (Creature* creature : *group) {
		creature->food = 0;
	}

	foodAverage /= ((float)group->size());

	cout << "\tWorst fitness     : " << leastFood << endl;
	cout << "\tAverage fitness   : " << foodAverage << endl;
	cout << "\tBest fitness      : " << maxFood << endl;
#endif
}

void Nature::setVision(vector<Vector2> eyes, Creature* source, vector<float>* inputs) {

	Vector2 A = eyes[0];
	Vector2 B = eyes[1];
	Vector2 C = eyes[2];
	
	int foodCount = 0;

	/*for (Creature* other : creatures) {

		if (source == other) continue;

		Vector2 p = other->location;
		Vector2 v0 = Vector2::subtract(C, A);
		Vector2 v1 = Vector2::subtract(B, A);
		Vector2 v2 = Vector2::subtract(p, A);

		float dot00 = Vector2::dot(v0, v0);
		float dot01 = Vector2::dot(v0, v1);
		float dot02 = Vector2::dot(v0, v2);
		float dot11 = Vector2::dot(v1, v1);
		float dot12 = Vector2::dot(v1, v2);

		float inv = 1 / ((dot00*dot11) - (dot01*dot01));
		float u = ((dot11*dot02) - (dot01*dot12)) * inv;
		float v = ((dot00*dot12) - (dot01*dot02))*inv;
		bool within = (u > 0) && (v > 0) && (u + v < 1);

		if (within) {

		}

		creatureCount += within;
	}*/

	float minDistance = RAND_MAX;
	Food* closestFood;
	bool found = false;

	for (Food* food : foods) {
		Vector2 p = food->location;
		Vector2 v0 = Vector2::subtract(C, A);
		Vector2 v1 = Vector2::subtract(B, A);
		Vector2 v2 = Vector2::subtract(p, A);

		float dot00 = Vector2::dot(v0, v0);
		float dot01 = Vector2::dot(v0, v1);
		float dot02 = Vector2::dot(v0, v2);
		float dot11 = Vector2::dot(v1, v1);
		float dot12 = Vector2::dot(v1, v2);

		float inv = 1 / ((dot00*dot11) - (dot01*dot01));
		float u = ((dot11*dot02) - (dot01*dot12)) * inv;
		float v = ((dot00*dot12) - (dot01*dot02))*inv;
		bool within = (u >= 0) && (v >= 0) && (u + v < 1);

		if (within) {
			float dist = Vector2::distance(food->location, source->location);
			if (dist < minDistance) {
				minDistance = dist;
				closestFood = food;
				found = true;
			}
		}
	}

	float distance = 0;
	float angle = 0;
	source->drawPoint = source->location;
	(*inputs) = vector<float>(NUM_EYES);

	if (found) {
		source->drawPoint = closestFood->location;

		distance = 1 - (minDistance / source->eyeLength);

		Vector2 eyeOut = Vector2::subtract(closestFood->location, source->location);
		Vector2 leftSide = Vector2::subtract(B, A);
		Vector2 rightSide = Vector2::subtract(C, A);

		float maxAngle = Vector2::angle(leftSide, rightSide);
		angle = Vector2::angle(leftSide, eyeOut) / maxAngle;

#if 1
		inputs->at(0) = angle;
		inputs->at(1) = 1 - angle;
		//inputs->at(2) = distance;
		//inputs->at(3) = 1 - distance;		
#endif

#if 0
		int pos = floor(angle * 10);

		int indA = pos - 3;
		int indB = pos - 2;
		int ind1 = pos - 1;
		int ind2 = pos;
		int indC = pos + 1;
		int indD = pos + 2;

		float outer = 0.15f;
		float inner = 0.5f;
		float orig = 1.0f;

		if (indA >= 0 && indA < inputs->size()) {
			inputs->at(indA) = outer * distance;
		}
		if (indB >= 0 && indB < inputs->size()) {
			inputs->at(indB) = inner * distance;
		}

			if (ind1 >= 0 && ind1 < inputs->size()) {
				inputs->at(ind1) = orig * distance;
			}

			if (ind2 >= 0 && ind2 < inputs->size()) {
				inputs->at(ind2) = orig * distance;
			}

		if (indC >= 0 && indC < inputs->size()) {
			inputs->at(indC) = inner * distance;
		}

		if (indD >= 0 && indD < inputs->size()) {
			inputs->at(indD) = outer * distance;
		}
#endif
	}
}

void Nature::senseArea(Creature * source, vector<float>* inputs) {
	float res = 0;
	for (vector<Creature*> things : creatures) {
		for (Creature* creature : things) {
			if (creature == source) continue;


			if (Vector2::distance(creature->location, source->location) < 100) {
				res += (0.75f - Vector2::distance(creature->location, source->location) / 200.0f);
			}
		}
	}
	res = (res > 1.0f ? 1.0 : res);
	inputs->push_back(res);
}

void Nature::update() {
	//float genLimit = 2000 + (2 * generation);
	float genLimit = 2000 + (2 * generation);

	for (vector<Creature*> things : creatures) {
		for (Creature* creature : things) {
			vector<float> inputs = vector<float>();

			setVision(creature->getVision(), creature, &inputs);
			senseArea(creature, &inputs);

			float boredom = (creature->lastFoodCounter++ / 1000.0f);
			boredom = (boredom > 1.0f) ? 1.0f : boredom;

			inputs.push_back(boredom);
			if (gen % 100 == 0) {
				creature->currentRandom = irandomf(0.0f, 1.0f);
			}
			inputs.push_back(creature->currentRandom);

#if 0
			float relx = creature->location.getX() / SCREEN_WIDTH;
			float relx_ = 1 - relx;

			float rely = creature->location.getY() / SCREEN_HEIGHT;
			float rely_ = 1 - rely;

			inputs.push_back(relx);
			inputs.push_back(relx_);

			inputs.push_back(rely);
			inputs.push_back(rely_);

			float dir = creature->direction / 360.0f;
			float dir_ = 1 - dir;

			inputs.push_back(dir);
			inputs.push_back(dir_);
#endif

			if (inputs.size() != NUMBER_INPUTS) {
				cout << "Input size mismatch" << endl;
				while (true) {}
			}
			creature->process(inputs);
		}
	}

	for (vector<Creature*> things : creatures) {
		for (Creature* creature : things) {
			creature->update();
			creature->draw();

			for (int i = 0; i < foods.size(); i++) {
				Food* food = foods[i];

				if (Vector2::distance(food->location, creature->location) < 20) {
					delete food;
					foods[i] = new Food();
					creature->food++;
					creature->lastFoodCounter = 0;

					int x, y;
					x = xrandomi(0, SCREEN_MAIN_WIDTH);
					y = xrandomi(0, SCREEN_MAIN_HEIGHT);

					foods[i]->location = Vector2(x, y);
				}
			}
		}
	}

	for (Food* food : foods) {
		food->draw();
		food->life++;

		if (food->life > irandomi(3200, 4000)) {
			food->life = 0;

			int x, y;
			x = xrandomi(0, SCREEN_MAIN_WIDTH);
			y = xrandomi(0, SCREEN_MAIN_HEIGHT);

			food->location = Vector2(x, y);
		}
	}


	gen++;

	if (gen > genLimit) {
		
		cout << "\n\n\n\tGeneration: " << generation++ << endl << endl;

		DPoint* point = new DPoint();

		for (int i = 0; i < creatures.size(); i++) {
			evolve(&creatures[i], i, point);
		}

		points.push_back(point);

		for (int i = 0; i < 3; i++) {
			point->mean[i] /= gen;
			point->max[i] /= gen;
		}


		gen = 0;
	}
	glutPostRedisplay();
}