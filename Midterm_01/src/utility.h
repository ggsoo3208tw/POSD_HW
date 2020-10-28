#ifndef UTILITY_H
#define UTILITY_H

#include "node.h"

#include <deque>

template<class Filter>
std::deque<Node*> filterNode(Node* node, Filter filter) {
    // access the node with iterator pattern.
    // DO NOT use Type Checking or Dynamic Type that would violate OCP to implement the function.
    // return the nodes under the input node tree sturctur that match the given filter.
    // throw std::string "Only folder can filter node!" when the input node is not iterable.
    deque<Node*> _nodes;
    Iterator* it = node->createIterator();
    try {
        it->currentItem();
    }catch(string e){
        throw string("Only folder can filter node!");
    }
    for (it->first(); !it->isDone(); it->next()) {
        if (filter(it->currentItem())) {
            _nodes.push_back(it->currentItem());
        }
        Iterator* ita = it->currentItem()->createIterator();
        if (!ita->isDone()) {
            deque<Node*> getDequeNode = filterNode(it->currentItem(), filter);
            for (deque<Node*>::iterator ita = getDequeNode.begin(); ita != getDequeNode.end(); ita++) {
                _nodes.push_back(*ita);
            }
        }
    }
    return _nodes;

}

class SizeFilter {
public:
    SizeFilter(double upperBound, double lowerBound):_upperBound(upperBound), _lowerBound(lowerBound) {}
    bool operator() (Node* node) const {
      return (node->size() <= _upperBound) && (node->size() >= _lowerBound);
    }
private:
  double _upperBound, _lowerBound;
};
#endif
