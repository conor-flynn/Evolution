#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "sources.h"
#include "Store.h"


template <class Key, class Value> class Dictionary {
private:
	int num_values;
	map<Key, Value> data;

	Store<Key> _keys;
	Store<Value> _values;
	// ---
public:
	Dictionary();
	// =~ =~ =~ =~ =~ =~ =~ =~ =~ 
	void add(Key k, Value v);
	void set(Key k, Value v);
	void clear();
	bool containsKey(Key k);
	bool containsValue(Value v);
	bool remove(Key k);

	Store<Key> keyStore();
	Store<Value> valueStore();
	vector<Value> values();
	vector<Key> keys();

	Value operator[](Key k);
	Value get(Key k);

	Key getByValue(Value v);

	vector<pair<Key, Value>> pairs();
	// =~ =~ =~ =~ =~ =~ =~ =~ =~ 
	bool empty();
	int size();
	// =~ =~ =~ =~ =~ =~ =~ =~ =~ 
};

template<class Key, class Value>
inline Dictionary<Key, Value>::Dictionary() {
	num_values = 0;
}

template<class Key, class Value>
inline void Dictionary<Key, Value>::add(Key k, Value v) {
	if (containsKey(k)) {
		throw new exception;
	}
	else {
		_keys.add(k);
		_values.add(v);
		data.insert(pair<Key, Value>(k, v));
		num_values++;
	}
}

template<class Key, class Value>
inline void Dictionary<Key, Value>::set(Key k, Value v) {
	if (containsKey(k)) {

		_values.remove(data[k]);
		_values.add(v);

		data[k] = v;
	}
	else {
		throw new exception;
	}
}

template<class Key, class Value>
inline void Dictionary<Key, Value>::clear() {

	_keys.clear();
	_values.clear();

	data.clear();
	num_values = 0;
}

template<class Key, class Value>
inline bool Dictionary<Key, Value>::containsKey(Key k) {

	return _keys.contains(k);

	/*for (pair<Key, Value> p : data) {
	if (p.first == k) return true;
	}

	return false;*/
}

template<class Key, class Value>
inline bool Dictionary<Key, Value>::containsValue(Value v) {

	return _values.contains(v);

	/*for (pair<Key, Value> p : data) {
	if (p.second == v) {
	return true;
	}
	}

	return false;*/
}

template<class Key, class Value>
inline bool Dictionary<Key, Value>::remove(Key k) {
	if (containsKey(k)) {

		_values.remove(data[k]);
		_keys.remove(k);

		data.erase(k);
		num_values--;
		return true;
	}
	return false;
}

template<class Key, class Value>
inline Store<Key> Dictionary<Key, Value>::keyStore() {
	return _keys;
	/*Store<Key> s;

	for (pair<Key, Value> p : data) {
	s.add(p.first);
	}

	return s;*/
}

template<class Key, class Value>
inline Store<Value> Dictionary<Key, Value>::valueStore() {
	return _values;
	/*Store<Value> s;

	for (pair<Key, Value> p : data) {
	s.add(p.second);
	}

	return s;*/
}

template<class Key, class Value>
inline vector<Value> Dictionary<Key, Value>::values() {

	return _values.values();

	/*vector<Value> v;

	for (pair<Key, Value> p : data) {
	v.push_back(p.second);
	}

	return v;*/
}

template<class Key, class Value>
inline vector<Key> Dictionary<Key, Value>::keys() {

	return _keys.values();

	/*vector<Key> k;

	for (pair<Key, Value> p : data) {
	k.push_back(p.first);
	}

	return k;*/
}

template<class Key, class Value>
inline Value Dictionary<Key, Value>::operator[](Key k) {
	if (containsKey(k)) {
		return data[k];
	}
	else {
		throw new exception;
	}
}

template<class Key, class Value>
inline Value Dictionary<Key, Value>::get(Key k) {
	if (containsKey(k)) {
		return data[k];
	}
	else {
		throw new exception;
	}
}

template<class Key, class Value>
inline Key Dictionary<Key, Value>::getByValue(Value v) {
	for (pair<Key, Value> p : data) {
		if (p.second == v) {
			return p.first;
		}
	}

	throw new exception;
}

template<class Key, class Value>
inline vector<pair<Key, Value>> Dictionary<Key, Value>::pairs() {
	vector<pair<Key, Value>> result;

	for (pair<Key, Value> p : data) {
		result.push_back(p);
	}

	return result;
}

template<class Key, class Value>
inline bool Dictionary<Key, Value>::empty() {
	return num_values == 0;
}

template<class Key, class Value>
inline int Dictionary<Key, Value>::size() {
	return num_values;
}


#endif