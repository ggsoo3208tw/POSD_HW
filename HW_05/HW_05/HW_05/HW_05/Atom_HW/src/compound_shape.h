#include "shape.h"
#include <iostream>
#include <string>
using namespace std;
class CompoundShape : public Shape {
public:
    CompoundShape(string id, vector<Shape*>* shapes):Shape(id,"transparent") {
      /*-----------------------------------------------*/
      cout << "CompoundShape id:" << id << " " << endl;
      for(vector<Shape*>::iterator it = shapes->begin(); it != shapes->end(); it++){
        cout << (*it)->id() << " : " << (*it)->info() << endl;
      }
      /*---------------------------------------------*/
      if(shapes->empty()) throw (string)"This is not a compound shape!";
      _shapes = shapes;
    }

    double area() const {
        double totalArea = 0.0;
        for (vector<Shape*>::iterator it = _shapes->begin(); it != _shapes->end() ; it++) {
            //cout << (*it)->info() << endl;
            totalArea += (*it)->area();
        }
        return totalArea;
    }

    double perimeter() const {
        double totalPerimeter = 0.0;
        for (vector<Shape*>::iterator it = _shapes->begin(); it != _shapes->end(); it++) {
            //cout << (*it)->info() << endl;
            totalPerimeter += (*it)->perimeter();
        }
        return totalPerimeter;
    }

    string info() const {
        string totalInfo = "Compound Shape {";
        for (vector<Shape*>::iterator it = _shapes->begin(); it != _shapes->end(); it++) {
            //cout << (*it)->info() << endl;
            totalInfo += (*it)->info();
            if (it < _shapes->end() - 1) totalInfo += ", ";
        }
        totalInfo += "}";
        //cout << "info() = " << _shapes->size() << endl;
        return totalInfo;
    }

    void addShape(Shape* shape) {
        _shapes->push_back(shape);
    }

    void deleteShapeById(string id) override{
      cout << "deleteShape by id:" << id << endl;
      bool noValue = true;
        vector<Shape*>* __shapes = new vector<Shape*>(0);
        __shapes->assign(_shapes->begin(), _shapes->end());
        _shapes-> clear();
        cout << "delecteShpae size Before: " << __shapes->size() << endl;
        for (vector<Shape*>::iterator it = __shapes->begin(); it != __shapes->end(); it++) {
            if (id != (*it)->id()) {
                _shapes->push_back(*it);
            }
            else {//have value
                noValue = false;
            }
        }
        if (noValue) throw (string)"Expected delete shape but shape not found";
    }

    Shape* getShapeById(string id) override {
      cout << "getShapeById by id:" << id << endl;
      bool noValue = true;
      vector<Shape*>::iterator it;
      vector<Shape*>* __shapes = new vector<Shape*>(0);
      __shapes->assign(_shapes->begin(), _shapes->end());
      _shapes->clear();
      cout << "getShapeById size Before: " << __shapes->size() << endl;
      for (it = __shapes->begin(); it != __shapes->end(); it++) {
          if (id != (*it)->id()) {
              _shapes->push_back(*it);
          }
          else {//have value
              noValue = false;
              break;
          }
      }
      if (noValue) throw (string)"Expected get shape but shape not found";
      return *it;
    }
private:
    vector<Shape*>* _shapes;
};
