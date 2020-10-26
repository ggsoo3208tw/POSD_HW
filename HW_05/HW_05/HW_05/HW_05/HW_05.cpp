#include <iostream>
#include "rectangle.h"
#include "ellipse.h"
#include <string>
#include <list>
#include <deque>

#include "shape.h"
#include "iterator.h"
#include "shape_iterator.h"
#include "compound_shape.h"
#include "utility.h"

using namespace std;
int main() {
    Shape* r34 = new Rectangle("1", 3, 4);
    Shape* e56 = new Ellipse("2", 5, 6);
    cout << r34->area() << endl;
    cout << r34->info() << endl;
    cout << e56->area() << endl;
    cout << e56->info() << endl;
    cout << "Hello World!\n";

    list<Shape*> shapes;
    shapes.push_back(r34);
    shapes.push_back(e56);
    Iterator* it = new ShapeIterator<list<Shape*>::iterator>(shapes.begin(), shapes.end());
    for (it; !it->isDone(); it->next()) {
        cout << it->currentItem()->area() << endl;
    }
    cout << "---------- TEST Compound Shape mbox1 ----------" << endl;
    Shape* mbox1 = new CompoundShape("99",shapes);
    cout << mbox1->area() << endl;
    cout << mbox1->perimeter() << endl;
    cout << mbox1->info() << endl;

    cout << "---------- TEST Compound Shape mbox1 and mbox2 ----------" << endl;
    Shape* r78 = new Rectangle("3", 7, 8);
    Shape* e78 = new Ellipse("4", 7, 8);
    Shape* r89 = new Rectangle("5", 8, 9);
    list<Shape*> shapes2;
    shapes2.push_back(r78);
    shapes2.push_back(e78);
    shapes2.push_back(r89);
    Shape* mbox2 = new CompoundShape("100", shapes2);
    mbox1->addShape(mbox2);
    cout << mbox1->area() << endl;
    cout << mbox1->perimeter() << endl;
    cout << mbox1->info() << endl;
    try {
        mbox1->deleteShapeById("4");
    }catch (string e) {
        cout << e << endl;
    }

    cout << "------------ delete the Shape After --------------" << endl;
    cout << mbox1->area() << endl;
    cout << mbox1->perimeter() << endl;
    cout << mbox1->info() << endl;

    cout << "------------ search the Shape --------------" << endl;
    Shape* shape;
    try {
        shape = ((CompoundShape*)mbox1)->getShapeById("5");
        cout << shape->info() << endl;
    }
    catch (string e) {
        cout << e << endl;
    }

    cout << "------------ utility Test getShapeById--------------" << endl;
    try {
        getShapeById(mbox1, "5");
    }
    catch (string e) {
        cout << e << endl;
    }

    cout << "------------ utility Test Filter--------------" << endl;
    cout << "Compound Shpae => " << mbox1->info() << endl;
    deque<Shape*> dequeShape;
    try {
        dequeShape = filterShape(mbox1, AreaFilter(100,20));
    }
    catch (string e) {
        cout << e << endl;
    }
    cout << "-----------------------------------------------" << endl;
    for (deque<Shape*>::iterator it = dequeShape.begin(); it != dequeShape.end(); ++it) {
        cout << (*it)->info() << endl;
    }
    cout << dequeShape.size() << endl;
    system("PAUSE");
    return 0;
}

