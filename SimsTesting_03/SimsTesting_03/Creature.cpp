#include "Creature.h"

Creature::Creature() {
	food = 0;
	lastFoodCounter = 0;
	brainInfo = "";
	drawPoint = Vector2(0, 0);
	currentRandom = 0;
	description = 0;

	eyeWidth = 150;
	eyeLength = 300;

	eyes.push_back(Vector2(-eyeWidth, eyeLength));
	eyes.push_back(Vector2( eyeWidth, eyeLength));

	body.push_back(Vector2(-5, -5));
	body.push_back(Vector2( 0, 0));
	body.push_back(Vector2( 5, -5));
}

vector<Vector2> Creature::getVision() {

	vector<Vector2> result;

	Vector2 origin = Vector2(location);
	Vector2 backTrack = Vector2(0, 30).rotate(direction);

	result.push_back(origin - backTrack);
	for (Vector2 v : eyes) {
		Vector2 res1 = v.rotate(direction);
		Vector2 res2 = res1.add(location);
		result.push_back(res2);
	}

	return result;
}

void Creature::process(vector<float> inputs) {
	brain->process(inputs);
}

vector<Vector2> Creature::getVertices() {
	vector<Vector2> result;

	for (Vector2 v : body) {
		Vector2 res = v.rotate(direction);
		Vector2 res2 = res.add(location);
		result.push_back(res2);
	}

	return result;
}

void Creature::update() {
	Vector2 left  = Vector2(0.15f, 1.0f);
	Vector2 right = Vector2(1.0f, 0.15f);
	Vector2 forw  = Vector2(1.0f, 1.0f);
	float left_wheel = 0;
	float right_wheel = 0;




	// Non-fusing behavior movement
#if 1
	vector<Vector2> behaviors;
	behaviors.push_back(left);
	behaviors.push_back(right);
	behaviors.push_back(forw);

	int indexMax = -1;
	float value = -1;
	for (int i = 0; i < brain->processResults.size(); i++) {
		if (brain->processResults[i] >= value) {
			value = brain->processResults[i];
			indexMax = i;
		}
	}

	if (indexMax == -1) {
		return;
	}

	Vector2 behave = behaviors[indexMax];
	left_wheel = behave.getX();
	right_wheel = behave.getY();
#endif

	// Fusing behavior movement
#if 0
	left.scale(brain->processResults[0]);
	right.scale(brain->processResults[1]);
	forw.scale(brain->processResults[2]);

	left_wheel = left.getX() + right.getX() + forw.getX();
	right_wheel = left.getY() + right.getY() + forw.getY();

	float res = (brain->processResults[0] + brain->processResults[1] + brain->processResults[2]);

	left_wheel /= res;
	right_wheel /= res;
#endif


	float creature_turn_rate = 20;
	float creature_speed = 1;


	// Turns at small differences are insignificant
	// Turns at large differences are significant
	// direction += (-right_wheel + left_wheel, 2) * creature_turn_rate;

	float difference = pow(-right_wheel + left_wheel, 2) * creature_turn_rate;

	if (-right_wheel + left_wheel < 0) {
		direction += difference;
	}
	else if (-right_wheel + left_wheel >= 0) {
		direction -= difference;
	}

	if (direction >= 360) {
		direction -= 360;
	}

	if (direction < 0) {
		direction = 360 + direction;
	}

	float speed = right_wheel + left_wheel;

	Vector2 move = Vector2(0.0f, creature_speed*speed);
	move = move.rotate(direction);
	location = Vector2::add(location, move);


#if 1
	if (location.getX() < 0) location.setX(SCREEN_WIDTH);
	if (location.getX() > SCREEN_WIDTH) location.setX(0);
	if (location.getY() < 0) location.setY(SCREEN_HEIGHT);
	if (location.getY() > SCREEN_HEIGHT) location.setY(0);
#endif

#if 0
	if (location.getX() < 0) location.setX(0);
	if (location.getX() > SCREEN_WIDTH) location.setX(SCREEN_WIDTH);
	if (location.getY() < 0) location.setY(0);
	if (location.getY() > SCREEN_HEIGHT) location.setY(SCREEN_HEIGHT);
#endif
}

void Creature::draw() {

#if 0
	glBegin(GL_LINE_LOOP);
	for (Vector2 v : getLeftVision()) {
		glColor3f(0, 1, 0);
		glVertex2f(v.getX(), v.getY());
	}
	glEnd();

	glBegin(GL_LINE_LOOP);
	for (Vector2 v : getRightVision()) {
		glColor3f(0, 1, 0);
		glVertex2f(v.getX(), v.getY());
	}
	glEnd();
#endif

#if 1
	glBegin(GL_POLYGON);
	for (Vector2 v : getVertices()) {
		glColor3f(0, 0, 0);
		glVertex2f(v.getX(), v.getY());
	}
	glEnd();
#endif

#if 0
	glBegin(GL_LINE_LOOP);
	for (Vector2 v : getVision()) {
		glColor3f(0, 1, 0);
		glVertex2f(v.getX(), v.getY());
	}
	glEnd();
#endif

	glBegin(GL_LINE_LOOP);
		glColor3f(1, 0, 0);
		glVertex2f(location.getX(), location.getY());
		glVertex2f(drawPoint.getX(), drawPoint.getY());
	glEnd();


#if 0

	glBegin(GL_LINE_LOOP);
	glColor3f(1, 0, 1);
	int val = 100;
	glVertex2f(location.getX()- val, location.getY()- val);
	glVertex2f(location.getX()- val, location.getY()+ val);
	glVertex2f(location.getX()+ val, location.getY()+ val);
	glVertex2f(location.getX()+ val, location.getY()- val);
	glEnd();

#endif
}
