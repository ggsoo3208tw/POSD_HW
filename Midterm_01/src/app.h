#ifndef APP_H
#define APP_H

#include "node.h"

class App : public Node {
public:
  App(std::string id, std::string name, double size):Node(id, name, size) {
  }
  void addNode(Node* node){
    throw std::string("only folder can add node.");
  }
  Node* getNodeById(std::string id) const {
    throw std::string("only folder can get node.");
  }
  void deleteNodeById(std::string id) {
    throw std::string("only folder can delete node.");
  }
};
#endif
