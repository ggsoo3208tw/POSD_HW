#ifndef COMPOUNDSHAPE_H
#define COMPOUNDSHAPE_H

#include "shape.h"
#include "iterator.h"
#include "shape_iterator.h"

#include <string>
#include <list>
using namespace std;

class CompoundShape : public Shape{
public:
    CompoundShape(string id, list<Shape*> shapes):Shape(id, "transparent"){
        if(shapes.size() == 0) throw string("This is not a compound shape!");
        _shapes = shapes;
    }

    Iterator *createIterator() const {
        return new ShapeIterator<list<Shape *>::const_iterator>(_shapes.begin(), _shapes.end());
    }

    double area() const {
        double totalArea = 0.0;
        Iterator *it = new ShapeIterator<list<Shape*>::const_iterator>(_shapes.begin(), _shapes.end());
        for (it->first() ; !it->isDone() ; it->next()) {
            totalArea += it->currentItem()->area();
        }
        return totalArea;
    }

    double perimeter() const {
        double totalPerimeter = 0.0;
        Iterator* it = new ShapeIterator<list<Shape*>::const_iterator>(_shapes.begin(), _shapes.end());
        for (it->first(); !it->isDone(); it->next()) {
            totalPerimeter += it->currentItem()->perimeter();
        }
        return totalPerimeter;
    }

    string info() const {
        string compoundShapeInfo = "Compound Shape {";
        Iterator* it = new ShapeIterator<list<Shape*>::const_iterator>(_shapes.begin(), _shapes.end());
        for (it->first(); !it->isDone(); it->next()) {
            compoundShapeInfo += it->currentItem()->info();
            compoundShapeInfo += ", ";
        }
        compoundShapeInfo = compoundShapeInfo.substr(0, compoundShapeInfo.size() - 2);
        compoundShapeInfo += "}";
        return compoundShapeInfo;
    }

    string type() const {
        return string("Compound Shape");
    }

    void addShape(Shape* shape) {
        _shapes.push_back(shape);
    }

    void deleteShapeById(string id) {
        for (Iterator* it = new ShapeIterator<list<Shape*>::iterator>(_shapes.begin(), _shapes.end()); !it->isDone(); it->next()) {
            //cout << it->currentItem()->id() << endl;
            if (it->currentItem()->id() == id) { //�j�M����
                //cout << "Search successful" << endl;
                _shapes.remove(it->currentItem());
                return;
            }
            Iterator* ita = it->currentItem()->createIterator();
            if (!ita->isDone()) { //�Y�� Compound Shape�h�~���U�h
                //cout << "This is Compound Shape!." << endl;
                try {
                    it->currentItem()->deleteShapeById(id);
                    return;
                }catch (string e) {
                    //cout << e << endl;
                }
            }
        }
        throw string("Expected delete shape but shape not found");
    }

    Shape* getShapeById(string id) const {
        //cout << "seach id = " << id << endl;
        for (Iterator* it = new ShapeIterator<list<Shape*>::const_iterator>(_shapes.begin(), _shapes.end()); !it->isDone(); it->next()) {
            //cout << it->currentItem()->id() << endl;
            if (it->currentItem()->id() == id) { //�j�M����
                //cout << "Search successful" << endl;
                //cout << "it : " << it->currentItem()->info() << endl;
                return it->currentItem();
            }
            Iterator* ita = it->currentItem()->createIterator();
            if (!ita->isDone()) { //�Y�� Compound Shape�h�~���U�h
                //cout << "This is Compound Shape!" << endl;
                try {
                    it->currentItem()->getShapeById(id);
                    //cout << "ita : " << ita->currentItem()->info() << endl;
                    return it->currentItem()->getShapeById(id);
                }catch (string e) {
                    //cout << e << endl;
                }
            }
        }
        throw string("Expected get shape but shape not found");
    }
private:
    list<Shape*> _shapes;
};
#endif
