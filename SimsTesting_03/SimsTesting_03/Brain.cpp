#include "Brain.h"



Brain::Brain(vector<int> info) {

	// {8, 10, 6, 4, 4, 3}
	// 8 inputs
		// 10 neurons
		// 6 neurons
		// 4 neurons
		// 4 neurons
		// 3 outputs

	/*
		number of inputs = info[0];
		number of layers = info.size()-1
		number of outputs = info[number of layers]

	*/

	// int inputs, int layers, int neuronsPer, int outputs

	/*int inputs = 3;
	int layers = 2; int neuronsPer = 4;
	int outputs = 3;*/

	info[0]++;
	
	for (int i = 0; i < info.size()-1; i++) {
		vector<Neuron*> layer;

		int neuronsCurrent = info[i];
		int neuronsNext = info[i + 1];

		for (int j = 0; j < neuronsCurrent; j++) {
			Neuron* neuron = new Neuron();
			for (int k = 0; k < neuronsNext; k++) {
				neuron->axons.push_back(new Axon());
			}
			layer.push_back(neuron);
		}
#if 0
		//if (i == 0) {
		//	// For each input, construct a neuron
		//		// For each neuron, connect to the number of neurons per layer

		//	for (int j = 0; j < neuronsCurrent; j++) {
		//		Neuron* neuron = new Neuron();
		//		for (int k = 0; k < neuronsNext; k++) {
		//			neuron->axons.push_back(new Axon());
		//		}
		//		layer.push_back(neuron);
		//	}

		//} else if (i == layers) {
		//	// For each neuron in neuronsPer, connect to the number of outputs

		//	for (int j = 0; j < neuronsCurrent; j++) {
		//		Neuron* neuron = new Neuron();
		//		for (int k = 0; k < neuronsNext; k++) {
		//			neuron->axons.push_back(new Axon());
		//		}
		//		layer.push_back(neuron);
		//	}

		//} else {

		//	for (int j = 0; j < neuronsCurrent; j++) {
		//		Neuron* neuron = new Neuron();
		//		for (int k = 0; k < neuronsNext; k++) {
		//			neuron->axons.push_back(new Axon());
		//		}
		//		layer.push_back(neuron);
		//	}
		//}
#endif
		neurons.push_back(layer);
	}
}

Brain::Brain(Brain* source) {

	vector<vector<Neuron*>>* data = &(source->neurons);

	for (int i = 0; i < data->size(); i++) {
		vector<Neuron*> layer;

		int neuronsCurrent = data->at(i).size();
		int neuronsNext = data->at(i)[0]->axons.size();

		for (int j = 0; j < neuronsCurrent; j++) {
			Neuron* neuron = new Neuron();
			for (int k = 0; k < neuronsNext; k++) {
				neuron->axons.push_back(new Axon(data->at(i)[j]->axons[k]));
			}
			layer.push_back(neuron);
		}
		neurons.push_back(layer);
	}
	return;

#if 0
	int inputs = data->at(0).size();
	int layers = data->size() - 1;
	int neuronsPer = data->at(1).size();
	int outputs = data->at(data->size() - 1)[0]->axons.size();

	// inputs++;

	for (int i = 0; i < layers + 1; i++) {
		vector<Neuron*> layer;

		if (i == 0) {
			// For each input, construct a neuron
			// For each neuron, connect to the number of neurons per layer

			for (int j = 0; j < inputs; j++) {
				Neuron* neuron = new Neuron();
				for (int k = 0; k < neuronsPer; k++) {
					Axon* sourceAxon = new Axon(data->at(i)[j]->axons[k]);
					neuron->axons.push_back(sourceAxon);
				}
				layer.push_back(neuron);
			}

		}
		else if (i == layers) {
			// For each neuron in neuronsPer, connect to the number of outputs

			for (int j = 0; j < neuronsPer; j++) {
				Neuron* neuron = new Neuron();
				for (int k = 0; k < outputs; k++) {
					Axon* sourceAxon = new Axon(data->at(i)[j]->axons[k]);
					neuron->axons.push_back(sourceAxon);
				}
				layer.push_back(neuron);
			}

		}
		else {

			for (int j = 0; j < neuronsPer; j++) {
				Neuron* neuron = new Neuron();
				for (int k = 0; k < neuronsPer; k++) {
					Axon* sourceAxon = new Axon(data->at(i)[j]->axons[k]);
					neuron->axons.push_back(sourceAxon);
				}
				layer.push_back(neuron);
			}
		}
		neurons.push_back(layer);
	}
#endif
}

void Brain::process(vector<float> inputs) {
	inputs.push_back(1);
	
	processResults = vector<float>(neurons[neurons.size() - 1][0]->axons.size());

	for (int i = 0; i < neurons.size(); i++) {

		vector<Neuron*> layer = neurons[i];

		if (i == 0) {
			// Read the input values into the neurons
			for (int k = 0; k < layer.size(); k++) {
				layer[k]->value = inputs[k];
				fireNeuron(layer[k], i);
			}
		}
		else if (i + 1 == neurons.size()) {
			// Write to outputs

			for (int k = 0; k < layer.size(); k++) {
				Neuron* neuron = layer[k];
				for (int j = 0; j < neuron->axons.size(); j++) {
					Axon* axon = neuron->axons[j];
					processResults[j] += (neuron->value * axon->weight);
				}
				neuron->value = 0;
			}

			for (int k = 0; k < layer[0]->axons.size(); k++) {
				processResults[k] = sigmoid(processResults[k]);
			}
		}
		else {
			for (int k = 0; k < layer.size(); k++) {
				fireNeuron(layer[k], i);
			}
		}
	}
}

void Brain::fireNeuron(Neuron * neuron, int layer) {
	int targetLayer = layer + 1;

	vector<Neuron*> targets = neurons[targetLayer];

	for (int i = 0; i < neuron->axons.size(); i++) {
		Axon* axon = neuron->axons[i];
		Neuron* target = targets[i];

		target->value += (neuron->value * axon->weight);
	}
	neuron->value = 0;
}

void Brain::mutate() {
	vector<Neuron*> layer = neurons[irandomi(0, neurons.size() - 1)];
	Neuron* targetNeuron = layer[irandomi(0, layer.size() - 1)];
	Axon* targetAxon = targetNeuron->axons[irandomi(0, targetNeuron->axons.size() - 1)];
	targetAxon->weight += irandomf(-0.1f, 0.1f);
}
