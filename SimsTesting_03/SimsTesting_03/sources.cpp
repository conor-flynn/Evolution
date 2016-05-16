#include "sources.h"

float sigmoid(float input) {
	return (1.0f / (1 + exp(-input)));
}

bool chance(int val) {
	return irandomi(1, 100) <= val;
}



float xrandom() {
	return ((float)rand() / (RAND_MAX));
}

float irandom() {
	return ((float)rand() / (RAND_MAX + 1));
}

float xrandomf(float lowerBound, float upperBound) {
	float diff = upperBound - lowerBound;
	float val = xrandom() * diff;
	return (val + lowerBound);
}

float irandomf(float lowerBound, float upperBound) {
	float diff = upperBound - lowerBound;
	float val = irandom() * diff;
	return (val + lowerBound);
}

int irandomi(int lowerBound, int upperBound) {
	int diff = 1 + upperBound - lowerBound;

	return ((int)(irandom() * ((float)diff))) + lowerBound;
}

int xrandomi(int lowerBound, int upperBound) {
	int diff = upperBound - lowerBound;

	return ((int)(irandom() * ((float)diff))) + lowerBound;
}

