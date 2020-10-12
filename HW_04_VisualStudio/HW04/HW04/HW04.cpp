// HW04.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//
#define _USE_MATH_DEFINES // for C++
#include <cmath>

#include <iostream>
#include <vector>
#include <iterator>


using namespace std;

class Shape {
public:
    string _id, _color;
    Shape(string id) :_id(id) {};
    Shape(string id, string color) :_id(id), _color(color) {};
    virtual double area() const = 0;
    virtual double perimeter() const = 0;
    virtual string info() const = 0;  
    virtual string id() const { return _id; };
    virtual string color() const { return _color; };
    virtual void addShape(Shape* shape) { throw (string)"Only compound shape can add shape!";  }; // throw std::string "Only compound shape can add shape!"
    virtual void deleteShapeById(std::string id) { throw (string)"Only compound shape can delete shape!"; }; // throw std::string "Only compound shape can delete shape!"
    virtual Shape* getShapeById(std::string id) { throw (string)"Only compound shape can get shape!"; }; // throw std::string "Only compound shape can get shape!"
};

class Rectangle : public Shape {
public:
    Rectangle(string id, double width, double height) :Shape(id) {
        if (width < 0 || height < 0) throw (string)"This is not a Rectangle!";

        _width = width;
        _height = height;
    }
    Rectangle(string id, double width, double height, string color) :Shape(id,color){
        if (width < 0 || height < 0) throw (string)"That is not a Rectangle!";

        _width = width;
        _height = height;
    }

    double area() const {
        return _width * _height;
    }

    double perimeter() const {
        return (_width + _height) * 2;
    }

    string info() const {
        char temporarilyArray[100] = "";
        sprintf_s(temporarilyArray, "Rectangle (%.3f, %.3f)", _height, _width);
        return string(temporarilyArray);
    }
private:
    double _width, _height;
};

class Ellipse : public Shape {
public:
    Ellipse(string id, double semiMajorAxes, double semiMinorAxes) :Shape(id) {
        if (semiMajorAxes <= 0 || semiMinorAxes <= 0) throw (string)"This is not a Ellipse!";

        _semiMajorAxes = semiMajorAxes;
        _semiMinorAxes = semiMinorAxes;
    }
    Ellipse(string id, double semiMajorAxes, double semiMinorAxes, string color) :Shape(id, color) {
        if (semiMajorAxes < 0 || semiMinorAxes < 0) throw (string)"That is not Ellipse!";

        _semiMajorAxes = semiMajorAxes;
        _semiMinorAxes = semiMinorAxes;
    }

    double area() const {
        return M_PI * _semiMajorAxes * _semiMinorAxes;
    }

    double perimeter() const {
        return 2 * M_PI * _semiMinorAxes + 4 * (_semiMajorAxes - _semiMinorAxes);
    }

    string info() const {
        char temporarilyArray[100] = "";
        sprintf_s(temporarilyArray, "Ellipse (%.3f, %.3f)", _semiMajorAxes, _semiMinorAxes);
        return string(temporarilyArray);
    }
private:
    double _semiMajorAxes, _semiMinorAxes;
};

class CompoundShape : public Shape {
public:
    CompoundShape(string id, vector<Shape*>* shapes):Shape(id) {
        if (shapes->size() < 2) throw (string)"This is not a compound shape!";
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
        cout << "info() = " << _shapes->size() << endl;
        return totalInfo;
    }

    void addShape(Shape* shape) {
        _shapes->push_back(shape);
    }

    void deleteShape(string id) {
        bool noValue = true;
        vector<Shape*>* __shapes = new vector<Shape*>(0);
        __shapes->assign(_shapes->begin(), _shapes->end());
        _shapes-> clear();
        cout << __shapes->size() << endl;
        for (vector<Shape*>::iterator it = __shapes->begin(); it != __shapes->end(); it++) {
            if (id != (*it)->id()) {
                _shapes->push_back(*it);
            }
            else {//have value
                noValue = false;
            }
        }
        if (noValue) throw (string)"Expected delete shape but shape not found";
        /*
        int count = 0;
        bool noValue = true;
        for (vector<Shape*>::iterator it = _shapes->begin(); it != _shapes->end(); it++,count++) {
            if (id == (*it)->id()) {
                _shapes->erase(_shapes->begin()+count);
                //cout << "delete is Yes" << endl;
                noValue = false;
            }
        }
        if (noValue) {
            cout << "delete No" << endl;
            throw (string)"Expected delete shape but shape not found";
        }
        */
    }

    Shape* getShapeById(string id) {
        bool noValue = true;
        vector<Shape*>* __shapes = new vector<Shape*>(0);
        __shapes->assign(_shapes->begin(), _shapes->end());
        _shapes->clear();
        cout << __shapes->size() << endl;
        vector<Shape*>::iterator it = __shapes->begin();
        for (it; it != __shapes->end(); it++) {
            if (id != (*it)->id()) {
                _shapes->push_back(*it);
            }
            else {//have value
                noValue = false;
                break;
            }
        }
        if (noValue) throw (string)"Expected get shape but shape not found";
        /*
        int count = 0;
        vector<Shape*>::iterator it = _shapes->begin();
        for (it; it != _shapes->end(); it++, count++) {
            if (id == (*it)->id()) {
                cout << "search is Yes" << endl;
                break;
            }
            if (count == _shapes->size() - 1) {
                cout << "search is No" << endl;
                throw (string)"Expected get shape but shape not found";
            }
        }
        */
        return *it;
    }
private:
    vector<Shape*>* _shapes;
};

int main(){
    cout << "Hello World!\n";

    Shape* r34 = new Rectangle("1", 3, 4);
    Shape* r55 = new Rectangle("2", 5, 5);
    Shape* e22 = new Ellipse("3", 2, 2);
    vector<Shape*>* _shapes = new vector<Shape*> {r34, r55};
    Shape* mbox = new CompoundShape("99", _shapes);
    //((CompoundShape*)mbox)->addShape(r34);
    //((CompoundShape*)mbox)->addShape(r22);
    ((CompoundShape*)mbox)->addShape(e22);
    /*
    cout << "Compound Shape Area = " << ((CompoundShape*)mbox)->area() << endl;
    cout << "Compound Shape Perimeter = " << ((CompoundShape*)mbox)->perimeter() << endl;
    cout << "Compound Shape Info = " << ((CompoundShape*)mbox)->info() << endl;
    ((CompoundShape*)mbox)->deleteShape("1");
    cout << "Compound Shape Info = " << ((CompoundShape*)mbox)->info() << endl;
    try {
        ((CompoundShape*)mbox)->deleteShape("1");
    }
    catch (string e) {
        if (e == "Expected delete shape but shape not found") cout << "Nice";
        else cout << "NO!!!!!!!!!!!!!!!!!!!!!";
    }
    cout << "Compound Shape Info = " << ((CompoundShape*)mbox)->info() << endl;
    
    Shape* searchShape;
    searchShape = ((CompoundShape*)mbox)->getShapeById("2");
    cout << searchShape->area() << endl;
    */
    /*----- Compound Shape have Compound Shape -------*/
    // mbox1 = {r34, r55, e22}
    vector<Shape*>* compoundShape = new vector<Shape*>{r34, r55};
    Shape* mbox2 = new CompoundShape("100", compoundShape);
    ((CompoundShape*)mbox2)->addShape(mbox);
    cout << "Compound Shape mbox2 Area = " << ((CompoundShape*)mbox2)->area() << endl;
    cout << "Compound Shape mbox2 Info = " << ((CompoundShape*)mbox2)->info() << endl;
    //((CompoundShape*)mbox2)->deleteShape("1");
    try {
        ((CompoundShape*)mbox2)->deleteShape("3");
    }
    catch (string e) {
        cout << e << endl;
    }
    try {
        ((CompoundShape*)mbox2)->deleteShape("3");
    }
    catch (string e) {
        cout << e << endl;
    }
    cout << "Compound Shape mbox2 Area = " << ((CompoundShape*)mbox2)->area() << endl;
    cout << "Compound Shape mbox2 Info = " << ((CompoundShape*)mbox2)->info() << endl;



    delete mbox;
    delete _shapes;
    delete r34;
    delete r55;
    delete e22;
    //delete searchShape;
    
}

// 執行程式: Ctrl + F5 或 [偵錯] > [啟動但不偵錯] 功能表
// 偵錯程式: F5 或 [偵錯] > [啟動偵錯] 功能表

// 開始使用的提示: 
//   1. 使用 [方案總管] 視窗，新增/管理檔案
//   2. 使用 [Team Explorer] 視窗，連線到原始檔控制
//   3. 使用 [輸出] 視窗，參閱組建輸出與其他訊息
//   4. 使用 [錯誤清單] 視窗，檢視錯誤
//   5. 前往 [專案] > [新增項目]，建立新的程式碼檔案，或是前往 [專案] > [新增現有項目]，將現有程式碼檔案新增至專案
//   6. 之後要再次開啟此專案時，請前往 [檔案] > [開啟] > [專案]，然後選取 .sln 檔案
