#ifndef NODE_H
#define NODE_H

#include <string>
#include "iterator.h"
using namespace std;
class Node {
public:
  Node(string a, string name, double size);
  string id() const;
  string name() const;
  virtual string route() const; // the "virtual" of this funtion is optional.
  virtual double size() const;
  virtual void updatePath(string path);
  virtual void addNode(Node* node);
  virtual Node* getNodeById(string id) const;
  virtual void deleteNodeById(string id);
  virtual Iterator* createIterator() const;
  virtual ~Node();
private:
  string _id;
  string _name;
  string _path = "";
  double _size;
};
#endif
