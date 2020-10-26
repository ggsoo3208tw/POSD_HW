#ifndef SHAPEITERATOR_H
#define SHAPEITERATOR_H

#include "Iterator.h"

template<class ForwardIterator>
class ShapeIterator : public Iterator {
public:
  ShapeIterator(ForwardIterator begin, ForwardIterator end):_begin(begin), _end(end) {
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
  ForwardIterator _begin;// This is the Iterator Indicator starting point. 此為指標指向第一個
  ForwardIterator _end;// This is the Iterator Indicator ending point. 此為指標指向最後一個
  ForwardIterator _current;// This is the Iterator Indicator currently point. 此為指標目前指向的
};
#endif
