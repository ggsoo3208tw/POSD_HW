#ifndef NODEITERATOR_H
#define NODEITERATOR_H

#include "iterator.h"
#include "node.h"

template<class ForwardIterator>
class NodeIterator : public Iterator {
public:
    NodeIterator(ForwardIterator begin, ForwardIterator end):_begin(begin),_end(end) {
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
          throw std::string("Moving past the end!");
        }
        _current++;
    }

    bool isDone() const {
        // return true when iterator reach the end of the structure.
        return _current == _end;
    }

    Node* currentItem() const {
        // return the Node that iterator currently point at.
        return *_current;
    }
private:
  ForwardIterator _begin;
  ForwardIterator _end;
  ForwardIterator _current;
};
#endif
