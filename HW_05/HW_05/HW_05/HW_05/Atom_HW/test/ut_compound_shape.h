#include "../src/shape.h"
#include "../src/rectangle.h"
#include "../src/ellipse.h"
#include "../src/triangle.h"
#include "../src/compound_shape.h"

class CompoundShapeTest : public ::testing::Test {
protected:
  void SetUp() override {
    r34 = new Rectangle("1", 3, 4);
    r55 = new Rectangle("2", 5, 5);
    e22 = new Ellipse("3", 2, 2);

    std::vector<TwoDimensionalCoordinate*> triangleVector;
    triangleVector.push_back(new TwoDimensionalCoordinate(0, 0));
    triangleVector.push_back(new TwoDimensionalCoordinate(3, 0));
    triangleVector.push_back(new TwoDimensionalCoordinate(0, 4));
    //Triangle triangle(triangleVector);
    t345 = new Triangle("4", triangleVector);

  }

  void TearDown() override {
    delete r34;
    delete r55;
    delete e22;
    delete t345;
  }

  Shape *r34;
  Shape *r55;
  Shape *e22;
  Shape *t345;
};
/*
TEST_F(CompoundShapeTest, CreateCompoundShapeThrow){
  vector<Shape*>* _shapes = new vector<Shape*>(0);
  try{
    Shape* mbox = new CompoundShape("99", _shapes);
    FAIL();
  }catch(std::string e){
    ASSERT_EQ("This is not a compound shape!", e);
  }
}
*/
TEST_F(CompoundShapeTest, CreateCompoundShape){
  vector<Shape*>* _shapes = new vector<Shape*>{r34, r55};
  ASSERT_NO_THROW(CompoundShape("99", _shapes));
}

TEST_F(CompoundShapeTest, CompoundShapeArea){
  vector<Shape*>* _shapes = new vector<Shape*>{r34, r55};
  Shape* mbox = new CompoundShape("99", _shapes);
  ASSERT_EQ(37.000,((CompoundShape*)mbox)->area());
}

TEST_F(CompoundShapeTest, CompoundShapePerimeter){
  vector<Shape*>* _shapes = new vector<Shape*>{r34, r55};
  Shape* mbox = new CompoundShape("99", _shapes);
  ASSERT_EQ(34.000,((CompoundShape*)mbox)->perimeter());
}

TEST_F(CompoundShapeTest, CompoundShapeInfo){
  vector<Shape*>* _shapes = new vector<Shape*>{r34, r55};
  Shape* mbox = new CompoundShape("99", _shapes);
  ASSERT_EQ("Compound Shape {Rectangle (3.000, 4.000), Rectangle (5.000, 5.000)}",((CompoundShape*)mbox)->info());
}

TEST_F(CompoundShapeTest, CompoundShapeAddShapeArea){//
  vector<Shape*>* _shapes = new vector<Shape*>{r34, r55};
  Shape* mbox = new CompoundShape("99", _shapes);
  ((CompoundShape*)mbox)->addShape(e22);

  char compoundShapeAreaArray[100];
  sprintf(compoundShapeAreaArray, "%.3f", ((CompoundShape*)mbox)->area());
  ASSERT_EQ("49.566",std::string(compoundShapeAreaArray));
}

TEST_F(CompoundShapeTest, CompoundShapeAddShapePerimeter){//
  vector<Shape*>* _shapes = new vector<Shape*>{r34, r55};
  Shape* mbox = new CompoundShape("99", _shapes);
  ((CompoundShape*)mbox)->addShape(e22);

  char compoundShapePerimeterArray[100];
  sprintf(compoundShapePerimeterArray, "%.3f", ((CompoundShape*)mbox)->perimeter());
  ASSERT_EQ("46.566",std::string(compoundShapePerimeterArray));
}

TEST_F(CompoundShapeTest, CompoundShapeDeleteShape){
  vector<Shape*>* _shapes = new vector<Shape*>{r34, r55, e22};
  Shape* mbox = new CompoundShape("99", _shapes);
  ((CompoundShape*)mbox)->deleteShapeById("3");
  ASSERT_EQ(37.000,((CompoundShape*)mbox)->area());
}
