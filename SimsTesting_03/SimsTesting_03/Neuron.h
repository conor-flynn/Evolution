#ifndef NEURON_H
#define NEURON_H

#include "sources.h"
#include "Axon.h"

class Neuron {
public:
	float value;
	vector<Axon*> axons;
	Neuron();
};

#endif