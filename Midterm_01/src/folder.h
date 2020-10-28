#ifndef FOLDER_H
#define FOLDER_H

#include "node.h"
#include "iterator.h"
#include "node_iterator.h"

#include <string>
#include <list>
using namespace std;

class Folder : public Node {
public:
    Folder(std::string id, std::string name):Node(id, name, 0) {
      _path = "";
      _name = name;
    } // the default size of folder is zero.
    // implement any functions inherit from Node that you think is suitable.

    Iterator* createIterator() const {
      return new NodeIterator<list<Node*>::const_iterator>(_nodes.begin(), _nodes.end());
    }

    string route() const {
      return _path + "/" + _name;
    }

    void updatePath(string path) {
      _path = path;
      for (Iterator* it = createIterator(); !it->isDone(); it->next())
        it->currentItem()->updatePath(route());
    }

    void addNode(Node* node) {
      node->updatePath(route());
      _nodes.push_back(node);
    }

    double size() const {
      double totalSize = 0.0;
      for(Iterator *it = createIterator();!it->isDone();it->next()){
          totalSize += it->currentItem()->size();
      }
      return totalSize;
    }

    Node* getNodeById(string id) const {
      for (Iterator* it = createIterator(); !it->isDone(); it->next()) {
        if (it->currentItem()->id() == id) return it->currentItem();
        if (!it->currentItem()->createIterator()->isDone()) return it->currentItem()->getNodeById(id);
      }throw string("Expected get node but node not found.");
    }

    void deleteNodeById(string id) {
      for (Iterator* it = createIterator(); !it->isDone(); it->next()) {
        if (it->currentItem()->id() == id) return _nodes.remove(it->currentItem());
        if (!it->currentItem()->createIterator()->isDone()) return it->currentItem()->deleteNodeById(id);
      }throw string("Expected delete node but node not found.");
    }

private:
    list<Node*> _nodes;
    string _path, _name;
};
#endif
