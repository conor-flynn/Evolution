#include "Axon.h"



Axon::Axon() {
	this->weight = irandomf(-1, 1);
}

Axon::Axon(float weight) {
	this->weight = weight;
}

Axon::Axon(Axon* source) {
	this->weight = source->weight;
}
