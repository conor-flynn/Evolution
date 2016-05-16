#ifndef AXON_H
#define AXON_H

#include "sources.h"

class Axon {
public:
	float weight;
	Axon();
	Axon(float weight);
	Axon(Axon* source);

};

#endif