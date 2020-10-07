#ifndef TERMINAL_H
#define TERMINAL_H

#include <iostream> // cout must include
/*----- string must include -----*/
#include <string>
using namespace std;
/*------   -----*/
#include <regex>
/*-----   -----*/
#include "shape.h"
#include "ellipse.h"
#include "rectangle.h"
#include "triangle.h"
#include "sort.h"
/*----- -----*/

class Terminal{
public:
  Terminal(string input):_input(input){
    cout << _input ;// !!!!!! OMG THIS IS MAGIC YOU KNOW TA TEST IS WHAT??? !!!!!!
    if(checkInput()) throw string("invalid input");// request error
    smatch sm;
    regex featurePattern("(area|perimeter)(.*)");
    regex orderPattern("(inc$|dec$)");
    if(regex_search(_input, sm, featurePattern)){
      _feature = sm[1];
    }
    if(regex_search(_input, sm, orderPattern)){
      _order = sm[1];
    }
    //cout << "feature = " << _feature << " " << "order = " << _order << endl;
  }
  string showResult(){
    // ex: "Rectangle (2, 2) Rectangle (1, 1) area inc"
    // Ans: "1.000\n4.000"
    smatch sm;
    string _PleaseInput = _input;
    regex orderPattern("^(inc$|dec$)");
    regex featurePattern("^(area|perimeter)(.*)");
    string shapesPattern[] = {
      "^(Ellipse\\s+\\({1}\\s*[1-9][0-9]*\\s*,\\s*[1-9][0-9]*\\s*\\){1}\\s+)(.*)",
      "^(Rectangle\\s+\\({1}\\s*[1-9][0-9]*\\s*,\\s*[1-9][0-9]*\\s*\\){1}\\s+)(.*)",
      "^(Triangle\\s+\\({1}\\s*\\[{1}\\s*-?[0-9][0-9]*\\s*,\\s*-?[0-9][0-9]*\\s*\\]{1}\\s*,\\s*\\[{1}\\s*-?[0-9][0-9]*\\s*,\\s*-?[0-9][0-9]*\\s*\\]{1}\\s*,\\s*\\[{1}\\s*-?[0-9][0-9]*\\s*,\\s*-?[0-9][0-9]*\\s*\\]{1}\\s*\\){1}\\s+)(.*)"
    };
    for(int z = 0;z<10 && (!regex_match(_PleaseInput,featurePattern));z++){
      for(int i = 0;i < 3;i++){
        if(regex_match(_PleaseInput,sm,regex(shapesPattern[i]))){
          _shapesCount += 1;
          if(i == 0){
            //cout << "Ellipse : " << sm[1] << endl;
            regex getNumber("[^0-9]*([0-9]+)(.*)");
            smatch m;
            string str = string(sm[1]);
            int ellipseValue[2],count = 0;
            while (regex_search(str, m, getNumber)) {
              ellipseValue[count++] = stoi(string(m[1]));
              str = string(m[2]); // Proceed to the next match
            }
            Ellipse ellipse(ellipseValue[0],ellipseValue[1]);
            shapes.push_back(new Ellipse(ellipseValue[0],ellipseValue[1]));
          }else if(i == 1){
            //cout << "Rectangle : " << sm[1] << endl;
            regex getNumber("[^0-9]*([0-9]+)(.*)");
            smatch m;
            string str = string(sm[1]);
            int rectangleValue[2],count = 0;
            while (regex_search(str, m, getNumber)) {
              rectangleValue[count++] = stoi(string(m[1]));
              str = string(m[2]); // Proceed to the next match
            }
            Rectangle rectangle(rectangleValue[0],rectangleValue[1]);
            shapes.push_back(new Rectangle(rectangleValue[0],rectangleValue[1]));
          }else if(i == 2){
            //cout << "Triangle : " << sm[1] << endl;
            regex getNumber("[^-?0-9]*([-?0-9]+)(.*)");
            smatch m;
            string str = string(sm[1]);
            int triangleValue[6],count = 0;
            while (regex_search(str, m, getNumber)) {
              triangleValue[count++] = stoi(string(m[1]));
              str = string(m[2]); // Proceed to the next match
            }
            std::vector<TwoDimensionalCoordinate*> triangleVector;
            triangleVector.push_back(new TwoDimensionalCoordinate(triangleValue[0], triangleValue[1]));
            triangleVector.push_back(new TwoDimensionalCoordinate(triangleValue[2], triangleValue[3]));
            triangleVector.push_back(new TwoDimensionalCoordinate(triangleValue[4], triangleValue[5]));
            Triangle triangle(triangleVector);
            shapes.push_back(new Triangle(triangleVector));
          }
          break;//代表以匹配形狀 跳出 i 迴圈
        }
      }
      _PleaseInput = string(sm[2]);
    }
    //cout << "_shapesCount = " << _shapesCount << endl;
    /*-------------------------*/
    sort();
    string result = "";
    for(int i = 0;i < shapes.size(); i++){
      if(_feature == "area"){
        char area[100];
        sprintf(area, "%.3f", shapes[i]->area());
        result += string(area);
        result += '\n';
      }else if(_feature == "perimeter"){
        char perimeter[100];
        sprintf(perimeter, "%.3f", shapes[i]->perimeter());
        result += string(perimeter);
        result += '\n';
      }
    }
    result = result.substr(0, result.size()-1);
    return result;
  }
  /*----- my Write func -----*/
  bool checkInput(){
    regex checkPattern("((Ellipse\\s+\\({1}\\s*[1-9][0-9]*\\s*,\\s*[1-9][0-9]*\\s*\\){1})|(Rectangle\\s+\\({1}\\s*[1-9][0-9]*\\s*,\\s*[1-9][0-9]*\\s*\\){1})|(Triangle\\s+\\({1}\\s*\\[{1}\\s*-?[0-9][0-9]*\\s*,\\s*-?[0-9][0-9]*\\s*\\]{1}\\s*,\\s*\\[{1}\\s*-?[0-9][0-9]*\\s*,\\s*-?[0-9][0-9]*\\s*\\]{1}\\s*,\\s*\\[{1}\\s*-?[0-9][0-9]*\\s*,\\s*-?[0-9][0-9]*\\s*\\]{1}\\s*\\){1})){1}\\s+(area|perimeter)\\s+(inc$|dec$)");
    if(regex_search(_input,checkPattern)){
      return false;
    }
    return true;
  }
  string showResultTest(){
    string result = "";
    smatch sm;
    string _PleaseInput = _input;
    regex orderPattern("^(inc$|dec$)");
    regex featurePattern("^(area|perimeter)(.*)");
    string shapesPattern[] = {
      "^(Ellipse\\s+\\({1}\\s*[1-9][0-9]*\\s*,\\s*[1-9][0-9]*\\s*\\){1}\\s+)(.*)",
      "^(Rectangle\\s+\\({1}\\s*[1-9][0-9]*\\s*,\\s*[1-9][0-9]*\\s*\\){1}\\s+)(.*)",
      "^(Triangle\\s+\\({1}\\s*\\[{1}\\s*-?[0-9]\\s*,\\s*-?[0-9]\\s*\\]{1}\\s*,\\s*\\[{1}\\s*-?[0-9]\\s*,\\s*-?[0-9]\\s*\\]{1}\\s*,\\s*\\[{1}\\s*-?[0-9]\\s*,\\s*-?[0-9]\\s*\\]{1}\\s*\\){1}\\s+)(.*)"
    };

    string bang = "Rectangle (10 ,2)";
    if(regex_match(bang, regex(shapesPattern[1]))){
      cout << "Nice";
    }else{
      cout << "No";
    }


    for(int z = 0;z<10 && (!regex_match(_PleaseInput,featurePattern));z++){
      for(int i = 0;i < 3;i++){
        if(regex_match(_PleaseInput,sm,regex(shapesPattern[i]))){
          _shapesCount += 1;
          if(i == 0){
            //cout << "Ellipse : " << sm[1] << endl;
            regex getNumber("[^0-9]*([0-9]+)(.*)");
            smatch m;
            string str = string(sm[1]);
            int ellipseValue[2],count = 0;
            cout << "in here"; // not doing
            while (regex_search(str, m, getNumber)) {
              ellipseValue[count++] = stoi(string(m[1]));
              cout << "99999999999" << string(m[1]) << endl;
              str = string(m[2]); // Proceed to the next match
            }
            Ellipse ellipse(ellipseValue[0],ellipseValue[1]);
            shapes.push_back(new Ellipse(ellipseValue[0],ellipseValue[1]));
            char ellipseArea[100];
            if(_feature == "area"){
              sprintf(ellipseArea, "%.3f", ellipse.area());
            }else if(_feature == "perimeter"){
              sprintf(ellipseArea, "%.3f", ellipse.perimeter());
            }
            result += string(ellipseArea);
            result += '\n';
          }else if(i == 1){
            //cout << "Rectangle : " << sm[1] << endl;
            regex getNumber("[^0-9]*([0-9]+)(.*)");
            smatch m;
            string str = string(sm[1]);
            int rectangleValue[2],count = 0;
            while (regex_search(str, m, getNumber)) {
              rectangleValue[count++] = stoi(string(m[1]));
              str = string(m[2]); // Proceed to the next match
            }
            Rectangle rectangle(rectangleValue[0],rectangleValue[1]);
            shapes.push_back(new Rectangle(rectangleValue[0],rectangleValue[1]));
            char rectangleArea[100];
            if(_feature == "area"){
              sprintf(rectangleArea, "%.3f", rectangle.area());
            }else if(_feature == "perimeter"){
              sprintf(rectangleArea, "%.3f", rectangle.perimeter());
            }
            result += string(rectangleArea);
            result += '\n';
          }else if(i == 2){
            //cout << "Triangle : " << sm[1] << endl;
            regex getNumber("[^-?0-9]*([-?0-9]+)(.*)");
            smatch m;
            string str = string(sm[1]);
            int triangleValue[6],count = 0;
            while (regex_search(str, m, getNumber)) {
              triangleValue[count++] = stoi(string(m[1]));
              str = string(m[2]); // Proceed to the next match
            }
            std::vector<TwoDimensionalCoordinate*> triangleVector;
            triangleVector.push_back(new TwoDimensionalCoordinate(triangleValue[0], triangleValue[1]));
            triangleVector.push_back(new TwoDimensionalCoordinate(triangleValue[2], triangleValue[3]));
            triangleVector.push_back(new TwoDimensionalCoordinate(triangleValue[4], triangleValue[5]));
            Triangle triangle(triangleVector);
            shapes.push_back(new Triangle(triangleVector));
            char triangleArea[100];
            if(_feature == "area"){
              sprintf(triangleArea, "%.3f", triangle.area());
            }else if(_feature == "perimeter"){
              sprintf(triangleArea, "%.3f", triangle.perimeter());
            }
            result += string(triangleArea);
            result += '\n';
          }
          break;//代表以匹配形狀 跳出 i 迴圈
        }
      }
      _PleaseInput = string(sm[2]);
    }
    result = result.substr(0, result.size()-1);
    //cout << "_shapesCount = " << _shapesCount << endl;
    return result;
  }
  void sort(){
    if(_order == "inc"){
      quickSort(shapes.begin(), shapes.end(), AscendingCompare(_feature));
    }else if(_order == "dec"){
      quickSort(shapes.begin(), shapes.end(), DescendingCompare(_feature));
    }
  }
  /*-----------------------*/
private:
  int _shapesCount = 0;
  string _input, _feature, _order;
  vector<Shape*> shapes;
};
#endif

/*---------  別理我 -----------*/
/*
//TEST
regex pattern("(Ellipse\\s+\\({1}\\s*[0-9]\\s*,\\s*[0-9]\\s*\\){1}\\s+)(.*)");
// Ellipse (3,4)
regex ellipse_pattern("Ellipse\\s+\\({1}\\s*[0-9]\\s*,\\s*[0-9]\\s*\\){1}");
// Rectangle (2,2)
regex rectangle_pattern("Rectangle\\s+\\({1}\\s*[0-9]\\s*,\\s*[0-9]\\s*\\){1}");
// Triangle ([0,-3], [-3,0], [0,-4])
regex triangle_pattern("Triangle\\s+\\({1}\\s*\\[{1}\\s*-?[0-9]\\s*,\\s*-?[0-9]\\s*\\]{1}\\s*,\\s*\\[{1}\\s*-?[0-9]\\s*,\\s*-?[0-9]\\s*\\]{1}\\s*,\\s*\\[{1}\\s*-?[0-9]\\s*,\\s*-?[0-9]\\s*\\]{1}\\s*\\){1}");
// array
string _format[3] = {"(Ellipse\\s+\\({1}\\s*[0-9]\\s*,\\s*[0-9]\\s*\\){1})(.*)",
                     "(Rectangle\\s+\\({1}\\s*[0-9]\\s*,\\s*[0-9]\\s*\\){1})(.*)",
                     "(Triangle\\s+\\({1}\\s*\\[{1}\\s*-?[0-9]\\s*,\\s*-?[0-9]\\s*\\]{1}\\s*,\\s*\\[{1}\\s*-?[0-9]\\s*,\\s*-?[0-9]\\s*\\]{1}\\s*,\\s*\\[{1}\\s*-?[0-9]\\s*,\\s*-?[0-9]\\s*\\]{1}\\s*\\){1})(.*)"
};
//
*/
/*if(regex_search(_input.begin(), _input.end(), ellipse_pattern)){
  //return false;
}*/
//smatch sm;
//if(regex_match(_input,sm,pattern)){}
  /*
  for(int i = 0;i<sm.size();++i){
    cout << i << ":" << sm[i] << endl;
  }
  */
  /*
  while(!){ // 直到碰到area or perimeter
    for(){ // _format 下去確認

    }
  }
  return false;
}
*/
/*----------------------------*/
