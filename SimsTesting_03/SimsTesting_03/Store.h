#ifndef STORE_H
#define STORE_H

#include "sources.h"

template <class Value> class Store {
private:
	vector<Value> data;
public:
	Store();
	// =~ =~ =~ =~ =~ =~ =~ =~ =~ 
	void add(Value v);
	void remove(Value v);
	void clear();
	bool contains(Value v);
	Value getRandom();

	vector<Value> values();
	int size();
	bool empty();

};

template<class Value>
inline Store<Value>::Store() {

}

template<class Value>
inline void Store<Value>::add(Value v) {
	if (contains(v)) {
		throw new exception();
	}
	else {
		data.push_back(v);
	}
}

template<class Value>
inline void Store<Value>::remove(Value v) {
	if (contains(v)) {
		for (int i = 0; i < data.size(); i++) {
			if (data[i] == v) {
				data.erase(data.begin() + i);
			}
		}
	}
	else {
		throw new exception();
	}
}

template<class Value>
inline void Store<Value>::clear() {
	data.clear();
}

template<class Value>
inline bool Store<Value>::contains(Value v) {
	for (Value k : data) {
		if (k == v) return true;
	}
	return false;
}

template<class Value>
inline Value Store<Value>::getRandom() {

	if (data.size() == 0) {
		throw new exception;
	}

	int index = data.size() * random();
	return data[index];
}

template<class Value>
inline vector<Value> Store<Value>::values() {
	return data;
}

template<class Value>
inline int Store<Value>::size() {
	return data.size();
}

template<class Value>
inline bool Store<Value>::empty() {
	return data.size() == 0;
}


#endif