#ifndef BRAIN_H
#define BRAIN_H

#include "sources.h"
#include "Neuron.h"
#include "Axon.h"

class Brain {
public:
	Brain();
	Brain(vector<int> info);
	//Brain(int inputs, int layers, int neuronsPer, int outputs);
	Brain(Brain* source);

	vector<float> processResults;

	vector<vector<Neuron*>> neurons;

	void process(vector<float> inputs);
	void fireNeuron(Neuron* neuron, int layer);

	void mutate();
};

#endif