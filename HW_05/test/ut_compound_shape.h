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
    //Triangle triangle(trianglelist);
    t345 = new Triangle("4", triangleVector);

    r78 = new Rectangle("5", 7, 8);
    r1010 = new Rectangle("6", 10, 10);
    r89 = new Rectangle("7", 8, 9);
  }

  void TearDown() override {
    delete r34;
    delete r55;
    delete e22;
    delete t345;
    delete r78;
    delete r1010;
    delete r89;
  }

  Shape *r34;
  Shape *r55;
  Shape *e22;
  Shape *t345;
  Shape *r78;
  Shape *r1010;
  Shape *r89;
};

TEST_F(CompoundShapeTest, CreateCompoundShapeNoThrow){
  list<Shape*> _shapes{r34, r55, e22, t345};
  ASSERT_NO_THROW(CompoundShape("99", _shapes));
}

TEST_F(CompoundShapeTest, CreateCompoundShapeHaveThrow){
  list<Shape*> _shapes{};
  try{
    CompoundShape("99", _shapes);
  }catch(std::string e){
    ASSERT_EQ("This is not a compound shape!", e);
  }
}

TEST_F(CompoundShapeTest, CompoundShapeArea){
  list<Shape*> _shapes{r34, r55};
  Shape* mbox = new CompoundShape("99", _shapes);
  ASSERT_EQ(37.000,((CompoundShape*)mbox)->area());
}

TEST_F(CompoundShapeTest, CompoundShapePerimeter){
  list<Shape*> _shapes{r34, r55};
  Shape* mbox = new CompoundShape("99", _shapes);
  ASSERT_EQ(34.000,((CompoundShape*)mbox)->perimeter());
}

TEST_F(CompoundShapeTest, CompoundShapeInfo){
  list<Shape*> _shapes{r34, r55};
  Shape* mbox = new CompoundShape("99", _shapes);
  ASSERT_EQ("Compound Shape {Rectangle (3.000, 4.000), Rectangle (5.000, 5.000)}",((CompoundShape*)mbox)->info());
}

TEST_F(CompoundShapeTest, CompoundShapeAddShapeArea){
  list<Shape*> _shapes{r34, r55};
  Shape* mbox = new CompoundShape("99", _shapes);
  ((CompoundShape*)mbox)->addShape(e22);

  char compoundShapeAreaArray[100];
  sprintf(compoundShapeAreaArray, "%.3f", ((CompoundShape*)mbox)->area());
  ASSERT_EQ("49.566",std::string(compoundShapeAreaArray));
}

TEST_F(CompoundShapeTest, CompoundShapeAddShapePerimeter){//
  list<Shape*> _shapes{r34, r55};
  Shape* mbox = new CompoundShape("99", _shapes);
  ((CompoundShape*)mbox)->addShape(e22);

  char compoundShapePerimeterArray[100];
  sprintf(compoundShapePerimeterArray, "%.3f", ((CompoundShape*)mbox)->perimeter());
  ASSERT_EQ("46.566",std::string(compoundShapePerimeterArray));
}

TEST_F(CompoundShapeTest, CompoundShapeDeleteShapeArea){
  list<Shape*> _shapes{r34, r55, e22};
  Shape* mbox = new CompoundShape("99", _shapes);
  ((CompoundShape*)mbox)->deleteShapeById("3");
  ASSERT_EQ(37.000,((CompoundShape*)mbox)->area());
}

TEST_F(CompoundShapeTest, CompoundShapeGetShapeById){
  list<Shape*> _shapes{r34, r55, e22};
  Shape* mbox = new CompoundShape("99", _shapes);
  Shape* shape = ((CompoundShape*)mbox)->getShapeById("2");
  ASSERT_EQ(25.000,shape->area());
}

TEST_F(CompoundShapeTest, CompoundShapeDeleteShapeByDeepArea){
  list<Shape*> _shapes{r34, r55, e22};
  Shape* mbox = new CompoundShape("99", _shapes);
  list<Shape*> _shapes2{r78, r1010};
  Shape* mbox2 = new CompoundShape("100", _shapes2);
  ((CompoundShape*)mbox)->addShape(mbox2);
  char compoundShapeAreaArray1[100];
  sprintf(compoundShapeAreaArray1, "%.3f", ((CompoundShape*)mbox)->area());
  ASSERT_EQ("205.566",std::string(compoundShapeAreaArray1));

  ((CompoundShape*)mbox)->deleteShapeById("5");
  char compoundShapeAreaArray2[100];
  sprintf(compoundShapeAreaArray2, "%.3f", ((CompoundShape*)mbox)->area());
  ASSERT_EQ("149.566",std::string(compoundShapeAreaArray2));
}

TEST_F(CompoundShapeTest, CompoundShapeDeleteShapeByDeepArea2){
  list<Shape*> _shapes{r34, r55, e22};
  Shape* mbox = new CompoundShape("99", _shapes);
  list<Shape*> _shapes2{r78, r1010};
  Shape* mbox2 = new CompoundShape("100", _shapes2);
  ((CompoundShape*)mbox)->addShape(mbox2);
  char compoundShapeAreaArray1[100];
  sprintf(compoundShapeAreaArray1, "%.3f", ((CompoundShape*)mbox)->area());
  ASSERT_EQ("205.566",std::string(compoundShapeAreaArray1));

  ((CompoundShape*)mbox)->deleteShapeById("3");
  char compoundShapeAreaArray2[100];
  sprintf(compoundShapeAreaArray2, "%.3f", ((CompoundShape*)mbox)->area());
  ASSERT_EQ("193.000",std::string(compoundShapeAreaArray2));
}

TEST_F(CompoundShapeTest, CompoundShapeDeleteShapeByDeepPerimeter){
  list<Shape*> _shapes{r34, r55, e22};
  Shape* mbox = new CompoundShape("99", _shapes);
  list<Shape*> _shapes2{r78, r1010};
  Shape* mbox2 = new CompoundShape("100", _shapes2);
  ((CompoundShape*)mbox)->addShape(mbox2);
  char compoundShapeArray1[100];
  sprintf(compoundShapeArray1, "%.3f", ((CompoundShape*)mbox)->perimeter());
  ASSERT_EQ("116.566",std::string(compoundShapeArray1));

  ((CompoundShape*)mbox)->deleteShapeById("5");
  char compoundShapeArray2[100];
  sprintf(compoundShapeArray2, "%.3f", ((CompoundShape*)mbox)->perimeter());
  ASSERT_EQ("86.566",std::string(compoundShapeArray2));
}

TEST_F(CompoundShapeTest, CompoundShapeDeleteShapeByDeepPerimeter2){
  list<Shape*> _shapes{r34, r55, e22};
  Shape* mbox = new CompoundShape("99", _shapes);
  list<Shape*> _shapes2{r78, r1010};
  Shape* mbox2 = new CompoundShape("100", _shapes2);
  ((CompoundShape*)mbox)->addShape(mbox2);
  char compoundShapeArray1[100];
  sprintf(compoundShapeArray1, "%.3f", ((CompoundShape*)mbox)->perimeter());
  ASSERT_EQ("116.566",std::string(compoundShapeArray1));

  ((CompoundShape*)mbox)->deleteShapeById("3");
  char compoundShapeArray2[100];
  sprintf(compoundShapeArray2, "%.3f", ((CompoundShape*)mbox)->perimeter());
  ASSERT_EQ("104.000",std::string(compoundShapeArray2));
}

TEST_F(CompoundShapeTest, CompoundShapeDeleteShapeByDeepInfo){
  list<Shape*> _shapes{r34, r55, e22};
  Shape* mbox = new CompoundShape("99", _shapes);
  list<Shape*> _shapes2{r78, r1010};
  Shape* mbox2 = new CompoundShape("100", _shapes2);
  ((CompoundShape*)mbox)->addShape(mbox2);
  ((CompoundShape*)mbox)->deleteShapeById("5");

  ASSERT_EQ("Compound Shape {Rectangle (3.000, 4.000), Rectangle (5.000, 5.000), Ellipse (2.000, 2.000), Compound Shape {Rectangle (10.000, 10.000)}}",((CompoundShape*)mbox)->info());
}

TEST_F(CompoundShapeTest, CompoundShapeDeleteShapeByDeepInfo2){
  list<Shape*> _shapes{r34, r55, e22};
  Shape* mbox = new CompoundShape("99", _shapes);
  list<Shape*> _shapes2{r78, r1010};
  Shape* mbox2 = new CompoundShape("100", _shapes2);
  ((CompoundShape*)mbox)->addShape(mbox2);
  ((CompoundShape*)mbox)->deleteShapeById("3");

  ASSERT_EQ("Compound Shape {Rectangle (3.000, 4.000), Rectangle (5.000, 5.000), Compound Shape {Rectangle (7.000, 8.000), Rectangle (10.000, 10.000)}}",((CompoundShape*)mbox)->info());
}

TEST_F(CompoundShapeTest, CompoundShapeGetShapeByIdToDeepArea){
  list<Shape*> _shapes{r34, r55, e22};
  Shape* mbox = new CompoundShape("99", _shapes);
  list<Shape*> _shapes2{r78, r1010};
  Shape* mbox2 = new CompoundShape("100", _shapes2);
  ((CompoundShape*)mbox)->addShape(mbox2);
  Shape* shape = ((CompoundShape*)mbox)->getShapeById("2");
  ASSERT_EQ(25, shape->area());
}

TEST_F(CompoundShapeTest, CompoundShapeGetShapeByIdToDeepPerimeter){
  list<Shape*> _shapes{r34, r55, e22};
  Shape* mbox = new CompoundShape("99", _shapes);
  list<Shape*> _shapes2{r78, r1010};
  Shape* mbox2 = new CompoundShape("100", _shapes2);
  ((CompoundShape*)mbox)->addShape(mbox2);
  Shape* shape = ((CompoundShape*)mbox)->getShapeById("2");
  ASSERT_EQ(20, shape->perimeter());
}

TEST_F(CompoundShapeTest, CompoundShapeGetShapeByIdToDeepInfo){
  list<Shape*> _shapes{r34, r55, e22};
  Shape* mbox = new CompoundShape("99", _shapes);
  list<Shape*> _shapes2{r78, r1010};
  Shape* mbox2 = new CompoundShape("100", _shapes2);
  ((CompoundShape*)mbox)->addShape(mbox2);
  Shape* shape = ((CompoundShape*)mbox)->getShapeById("2");
  ASSERT_EQ("Rectangle (5.000, 5.000)", shape->info());
}

TEST_F(CompoundShapeTest, CompoundShapeGetShapeByIdToDeepArea2){
  list<Shape*> _shapes{r34, r55, e22};
  Shape* mbox = new CompoundShape("99", _shapes);
  list<Shape*> _shapes2{r78, r1010};
  Shape* mbox2 = new CompoundShape("100", _shapes2);
  ((CompoundShape*)mbox)->addShape(mbox2);
  Shape* shape = ((CompoundShape*)mbox)->getShapeById("5");
  ASSERT_EQ(56, shape->area());
}

TEST_F(CompoundShapeTest, CompoundShapeGetShapeByIdToDeepPerimeter2){
  list<Shape*> _shapes{r34, r55, e22};
  Shape* mbox = new CompoundShape("99", _shapes);
  list<Shape*> _shapes2{r78, r1010};
  Shape* mbox2 = new CompoundShape("100", _shapes2);
  ((CompoundShape*)mbox)->addShape(mbox2);
  Shape* shape = ((CompoundShape*)mbox)->getShapeById("5");
  ASSERT_EQ(30, shape->perimeter());
}

TEST_F(CompoundShapeTest, CompoundShapeGetShapeByIdToDeepInfo2){
  list<Shape*> _shapes{r34, r55, e22};
  Shape* mbox = new CompoundShape("99", _shapes);
  list<Shape*> _shapes2{r78, r1010};
  Shape* mbox2 = new CompoundShape("100", _shapes2);
  ((CompoundShape*)mbox)->addShape(mbox2);
  Shape* shape = ((CompoundShape*)mbox)->getShapeById("5");
  ASSERT_EQ("Rectangle (7.000, 8.000)", shape->info());
}

TEST_F(CompoundShapeTest, CompoundShapeDeleteShapeByTree3){
  list<Shape*> _shapes{r34, r55, e22};
  Shape* mbox = new CompoundShape("99", _shapes);
  list<Shape*> _shapes2{r78, r1010};
  Shape* mbox2 = new CompoundShape("100", _shapes2);
  list<Shape*> _shapes3{r89};
  Shape* mbox3 = new CompoundShape("101", _shapes3);
  ((CompoundShape*)mbox2)->addShape(mbox3);
  ((CompoundShape*)mbox)->addShape(mbox2);
  ((CompoundShape*)mbox)->deleteShapeById("5");
  ASSERT_EQ("Compound Shape {Rectangle (3.000, 4.000), Rectangle (5.000, 5.000), Ellipse (2.000, 2.000), Compound Shape {Rectangle (10.000, 10.000), Compound Shape {Rectangle (8.000, 9.000)}}}", mbox->info());
}

TEST_F(CompoundShapeTest, CompoundShapeDelete2ShapeByTree3){
  list<Shape*> _shapes{r34, r55, e22};
  Shape* mbox = new CompoundShape("99", _shapes);
  list<Shape*> _shapes2{r78, r1010};
  Shape* mbox2 = new CompoundShape("100", _shapes2);
  list<Shape*> _shapes3{r89};
  Shape* mbox3 = new CompoundShape("101", _shapes3);
  ((CompoundShape*)mbox2)->addShape(mbox3);
  ((CompoundShape*)mbox)->addShape(mbox2);
  ((CompoundShape*)mbox)->deleteShapeById("5");
  ((CompoundShape*)mbox)->deleteShapeById("3");
  ASSERT_EQ("Compound Shape {Rectangle (3.000, 4.000), Rectangle (5.000, 5.000), Compound Shape {Rectangle (10.000, 10.000), Compound Shape {Rectangle (8.000, 9.000)}}}", mbox->info());
}

TEST_F(CompoundShapeTest, CompoundShapeDelete2ShapeByTree3Area){
  list<Shape*> _shapes{r34, r55, e22};
  Shape* mbox = new CompoundShape("99", _shapes);
  list<Shape*> _shapes2{r78, r1010};
  Shape* mbox2 = new CompoundShape("100", _shapes2);
  list<Shape*> _shapes3{r89};
  Shape* mbox3 = new CompoundShape("101", _shapes3);
  ((CompoundShape*)mbox2)->addShape(mbox3);
  ((CompoundShape*)mbox)->addShape(mbox2);
  ((CompoundShape*)mbox)->deleteShapeById("5");
  ((CompoundShape*)mbox)->deleteShapeById("3");
  ASSERT_EQ(209, mbox->area());
}

TEST_F(CompoundShapeTest, CompoundShapeDelete2ShapeByTree3Perimeter){
  list<Shape*> _shapes{r34, r55, e22};
  Shape* mbox = new CompoundShape("99", _shapes);
  list<Shape*> _shapes2{r78, r1010};
  Shape* mbox2 = new CompoundShape("100", _shapes2);
  list<Shape*> _shapes3{r89};
  Shape* mbox3 = new CompoundShape("101", _shapes3);
  ((CompoundShape*)mbox2)->addShape(mbox3);
  ((CompoundShape*)mbox)->addShape(mbox2);
  ((CompoundShape*)mbox)->deleteShapeById("1");
  ((CompoundShape*)mbox)->deleteShapeById("3");
  ASSERT_EQ(124, mbox->perimeter());
}

TEST_F(CompoundShapeTest, CompoundShapeGetShapeByIdByTree3){
  list<Shape*> _shapes{r34, r55, e22};
  Shape* mbox = new CompoundShape("99", _shapes);
  list<Shape*> _shapes2{r78, r1010};
  Shape* mbox2 = new CompoundShape("100", _shapes2);
  list<Shape*> _shapes3{r89};
  Shape* mbox3 = new CompoundShape("101", _shapes3);
  ((CompoundShape*)mbox2)->addShape(mbox3);
  ((CompoundShape*)mbox)->addShape(mbox2);
  Shape* shape = ((CompoundShape*)mbox)->getShapeById("5");
  ASSERT_EQ("Rectangle (7.000, 8.000)", shape->info());
}

TEST_F(CompoundShapeTest, CompoundShapeGetShapeByIdByTree3Area){
  list<Shape*> _shapes{r34, r55, e22, t345};
  Shape* mbox = new CompoundShape("99", _shapes);
  list<Shape*> _shapes2{r78, r1010};
  Shape* mbox2 = new CompoundShape("100", _shapes2);
  list<Shape*> _shapes3{r89};
  Shape* mbox3 = new CompoundShape("101", _shapes3);
  ((CompoundShape*)mbox2)->addShape(mbox3);
  ((CompoundShape*)mbox)->addShape(mbox2);
  Shape* shape = ((CompoundShape*)mbox)->getShapeById("4");
  ASSERT_EQ(6, shape->area());
}

TEST_F(CompoundShapeTest, CompoundShapeGetShapeByIdByTree3Perimeter){
  list<Shape*> _shapes{r34, r55, e22};
  Shape* mbox = new CompoundShape("99", _shapes);
  list<Shape*> _shapes2{r78, r1010};
  Shape* mbox2 = new CompoundShape("100", _shapes2);
  list<Shape*> _shapes3{r89};
  Shape* mbox3 = new CompoundShape("101", _shapes3);
  ((CompoundShape*)mbox2)->addShape(mbox3);
  ((CompoundShape*)mbox)->addShape(mbox2);
  Shape* shape = ((CompoundShape*)mbox)->getShapeById("7");
  ASSERT_EQ(34, shape->perimeter());
}

TEST_F(CompoundShapeTest, CompoundShapeGetShapeByIdByTree3Id){
  list<Shape*> _shapes{r34, r55, e22};
  Shape* mbox = new CompoundShape("99", _shapes);
  list<Shape*> _shapes2{r78, r1010};
  Shape* mbox2 = new CompoundShape("100", _shapes2);
  list<Shape*> _shapes3{r89};
  Shape* mbox3 = new CompoundShape("101", _shapes3);
  ((CompoundShape*)mbox2)->addShape(mbox3);
  ((CompoundShape*)mbox)->addShape(mbox2);
  Shape* shape = ((CompoundShape*)mbox)->getShapeById("6");
  ASSERT_EQ("6", shape->id());
}

TEST_F(CompoundShapeTest, CompoundShapeGetShapeByIdByTree3Color){
  list<Shape*> _shapes{r34, r55, e22};
  Shape* mbox = new CompoundShape("99", _shapes);
  list<Shape*> _shapes2{r78, r1010};
  Shape* mbox2 = new CompoundShape("100", _shapes2);
  list<Shape*> _shapes3{r89};
  Shape* mbox3 = new CompoundShape("101", _shapes3);
  ((CompoundShape*)mbox2)->addShape(mbox3);
  ((CompoundShape*)mbox)->addShape(mbox2);
  Shape* shape = ((CompoundShape*)mbox)->getShapeById("3");
  ASSERT_EQ("white", shape->color());
}

TEST_F(CompoundShapeTest, CompoundShapeGetShapeByIdByTree3Type){
  list<Shape*> _shapes{r34, r55, e22};
  Shape* mbox = new CompoundShape("99", _shapes);
  list<Shape*> _shapes2{r78, r1010};
  Shape* mbox2 = new CompoundShape("100", _shapes2);
  list<Shape*> _shapes3{r89};
  Shape* mbox3 = new CompoundShape("101", _shapes3);
  ((CompoundShape*)mbox2)->addShape(mbox3);
  ((CompoundShape*)mbox)->addShape(mbox2);
  Shape* shape = ((CompoundShape*)mbox)->getShapeById("6");
  ASSERT_EQ("Rectangle", shape->type());
}

TEST_F(CompoundShapeTest, CompoundShapeDeleteShapeByIdByTree3Exception){
  list<Shape*> _shapes{r34, r55, e22};
  Shape* mbox = new CompoundShape("99", _shapes);
  list<Shape*> _shapes2{r78, r1010};
  Shape* mbox2 = new CompoundShape("100", _shapes2);
  list<Shape*> _shapes3{r89};
  Shape* mbox3 = new CompoundShape("101", _shapes3);
  ((CompoundShape*)mbox2)->addShape(mbox3);
  ((CompoundShape*)mbox)->addShape(mbox2);
  try{
    ((CompoundShape*)mbox)->deleteShapeById("6666666666666666");
  }catch(string e){
    ASSERT_EQ("Expected delete shape but shape not found", e);
  }
}

TEST_F(CompoundShapeTest, CompoundShapeGetShapeByIdByTree3Exception){
  list<Shape*> _shapes{r34, r55, e22};
  Shape* mbox = new CompoundShape("99", _shapes);
  list<Shape*> _shapes2{r78, r1010};
  Shape* mbox2 = new CompoundShape("100", _shapes2);
  list<Shape*> _shapes3{r89};
  Shape* mbox3 = new CompoundShape("101", _shapes3);
  ((CompoundShape*)mbox2)->addShape(mbox3);
  ((CompoundShape*)mbox)->addShape(mbox2);
  try{
    Shape* shape = ((CompoundShape*)mbox)->getShapeById("54654654");
    shape->area();
  }catch(string e){
    ASSERT_EQ("Expected get shape but shape not found", e);
  }
}
TEST_F(CompoundShapeTest, CompoundShapeDeleteShapeByIdByTree3DeleteCompoundShape){
  list<Shape*> _shapes{r34, r55, e22};
  Shape* mbox = new CompoundShape("99", _shapes);
  list<Shape*> _shapes2{r78, r1010};
  Shape* mbox2 = new CompoundShape("100", _shapes2);
  list<Shape*> _shapes3{r89};
  Shape* mbox3 = new CompoundShape("101", _shapes3);
  ((CompoundShape*)mbox2)->addShape(mbox3);
  ((CompoundShape*)mbox)->addShape(mbox2);
  ((CompoundShape*)mbox)->deleteShapeById("3");
  ((CompoundShape*)mbox)->deleteShapeById("101");
  ASSERT_EQ(193, mbox->area());
}

TEST_F(CompoundShapeTest, CompoundShapeGetShapeByIdByTree3GetCompoundShape){
  list<Shape*> _shapes{r34, r55, e22};
  Shape* mbox = new CompoundShape("99", _shapes);
  list<Shape*> _shapes2{r78, r1010};
  Shape* mbox2 = new CompoundShape("100", _shapes2);
  list<Shape*> _shapes3{r89};
  Shape* mbox3 = new CompoundShape("101", _shapes3);
  ((CompoundShape*)mbox2)->addShape(mbox3);
  ((CompoundShape*)mbox)->addShape(mbox2);
  Shape* shape = ((CompoundShape*)mbox)->getShapeById("100");
  ASSERT_EQ(228, shape->area());
}

TEST_F(CompoundShapeTest, CompoundShapeGetShapeByIdByTree3GetCompoundShapeInfo){
  list<Shape*> _shapes{r34, r55, e22};
  Shape* mbox = new CompoundShape("99", _shapes);
  list<Shape*> _shapes2{r78, r1010};
  Shape* mbox2 = new CompoundShape("100", _shapes2);
  list<Shape*> _shapes3{r89};
  Shape* mbox3 = new CompoundShape("101", _shapes3);
  ((CompoundShape*)mbox2)->addShape(mbox3);
  ((CompoundShape*)mbox)->addShape(mbox2);
  Shape* shape = ((CompoundShape*)mbox)->getShapeById("100");
  ASSERT_EQ("Compound Shape {Rectangle (7.000, 8.000), Rectangle (10.000, 10.000), Compound Shape {Rectangle (8.000, 9.000)}}", shape->info());
}
