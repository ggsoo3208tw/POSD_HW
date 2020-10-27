#ifndef SHAPE_ITERATOR_H
#define SHAPE_ITERATOR_H

#include "shape.h"
#include "iterator.h"
#include <list>
#include <string>
using namespace std;
template<class ForwardIterator>
class ShapeIterator : public Iterator {
public:
    ShapeIterator(ForwardIterator begin, ForwardIterator end):_begin(begin),_end(end) {
        // initialize iterator.
        first();
    }

    void first() {
        // initialize iterator.
        _current = _begin;
    }

    void next() {
        // move iterator to next position,
        // throw std::string "Moving past the end!" when iterator move over the range of the structure.
        if(isDone()){
          throw string("Moving past the end!");
        }
        _current++;
    }

    bool isDone() const {
        // return true when iterator reach the end of the structure.
        return _current == _end;
    }

    Shape* currentItem() const {
        // return the shape that iterator currently point at.
        return *_current;
    }
private:
    ForwardIterator _begin;
    ForwardIterator _end;
    ForwardIterator _current;
};
#endif
