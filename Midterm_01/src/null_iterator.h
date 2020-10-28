#ifndef NULL_ITERATOR_H
#define NULL_ITERATOR_H

#include "node.h"
#include "iterator.h"
#include <string>
using namespace std;

class NullIterator : public Iterator {
public:
	Node* currentItem() const {
		if (isDone()) {
			throw string("No child member!");
		}
		return nullptr;
	}

	void next() {
		throw string("No child member!");
	}

	bool isDone() const {
		return true;
	}

	void first() {
		throw string("No child member!");
	}
};
#endif
