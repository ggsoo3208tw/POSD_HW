#ifndef NULL_ITERATOR_H
#define NULL_ITERATOR_H

#include "shape.h"
#include "iterator.h"
#include <string>
using namespace std;

class NullIterator : public Iterator {
public:
	Shape* currentItem() const {
		if (isDone()) {
			throw string("no current item");
		}
		return nullptr;
	}

	void next() {

	}

	bool isDone() const {
		return true;
	}

	void first() {

	}
};
#endif
