#include "../src/utility.h"
#include "../src/shape.h"
#include "../src/rectangle.h"
#include "../src/ellipse.h"
#include "../src/triangle.h"
#include "../src/compound_shape.h"

class UtilityTest : public ::testing::Test {
protected:
  void SetUp() override {
     r22 = new Rectangle("1", 2, 2);
     e4237 = new Ellipse("2", 4.2, 3.7);
     r56 = new Rectangle("4", 5, 6);
     std::vector<TwoDimensionalCoordinate*> triangleVector;
     triangleVector.push_back(new TwoDimensionalCoordinate(0, 0));
     triangleVector.push_back(new TwoDimensionalCoordinate(3, 0));
     triangleVector.push_back(new TwoDimensionalCoordinate(0, 4));
     t345 = new Triangle("3", triangleVector);
     std::list<Shape*> mboxList = {e4237, r22, t345};
     mbox = new CompoundShape("100", mboxList);
     std::list<Shape*> mbox2List = {e4237};
     mbox2 = new CompoundShape("101", mbox2List);
     std::list<Shape*> mbox3List = {r22, t345, r56};
     mbox3 = new CompoundShape("102", mbox3List);
     mbox2->addShape(mbox3);
     mbox->addShape(mbox2);
  }

  void TearDown() override {
      delete mbox3;
      delete mbox2;
      delete mbox;
      delete r22;
      delete e4237;
      delete t345;
      delete r56;
  }


  Shape * r22;
  Shape * e4237;
  Shape * t345;
  Shape * r56;
  Shape * mbox;
  Shape * mbox2;
  Shape * mbox3;
};

TEST_F(UtilityTest, getShapeByIdExceptionRectangle){
  Shape* getShape;
  try{
    getShape = getShapeById(r22, "2");
    getShape->info();
  }catch(std::string e){
    ASSERT_EQ("Only compound shape can get shape!", e);
  }
}

TEST_F(UtilityTest, getShapeByIdExceptionEllipse){
  Shape* getShape;
  try{
    getShape = getShapeById(e4237, "2");
    getShape->info();
  }catch(std::string e){
    ASSERT_EQ("Only compound shape can get shape!", e);
  }
}

TEST_F(UtilityTest, getShapeByIdExceptionTriangle){
  Shape* getShape;
  try{
    getShape = getShapeById(t345, "2");
    getShape->info();
  }catch(std::string e){
    ASSERT_EQ("Only compound shape can get shape!", e);
  }
}

TEST_F(UtilityTest, getShapeByIdNoException){
  ASSERT_NO_THROW(getShapeById(mbox3, "1"));
}

TEST_F(UtilityTest, getShapeByIdNoExceptionTo2){
  ASSERT_NO_THROW(getShapeById(mbox2, "2"));
}

TEST_F(UtilityTest, getShapeByIdNoExceptionTo22){
  ASSERT_NO_THROW(getShapeById(mbox2, "1"));
}

TEST_F(UtilityTest, getShapeByIdNoExceptionToVeryDeep){
  ASSERT_NO_THROW(getShapeById(mbox, "102"));
}

TEST_F(UtilityTest, getShapeByIdExceptionButNotId){
  try{
    Shape* getShape = getShapeById(mbox3, "-123");
    getShape->info();
  }catch(std::string e){
    ASSERT_EQ("Expected get shape but shape not found", e);
  }
}

TEST_F(UtilityTest, getShapeByIdExceptionToVeryDeepButNotId){
  try{
    Shape* getShape = getShapeById(mbox, "-123");
    getShape->info();
  }catch(std::string e){
    ASSERT_EQ("Expected get shape but shape not found", e);
  }
}

TEST_F(UtilityTest, getShapeByIdRectangle){
  Shape* getShape = getShapeById(mbox3, "1");
  ASSERT_EQ(4, getShape->area());
  ASSERT_EQ(8, getShape->perimeter());
  ASSERT_EQ("Rectangle (2.000, 2.000)", getShape->info());
  ASSERT_EQ("1", getShape->id());
  ASSERT_EQ("white", getShape->color());
  ASSERT_EQ("Rectangle", getShape->type());
}

TEST_F(UtilityTest, getShapeByIdTriangle){
  Shape* getShape = getShapeById(mbox3, "3");
  ASSERT_EQ(6, getShape->area());
  ASSERT_EQ(12, getShape->perimeter());
  ASSERT_EQ("Triangle ([0.000, 0.000], [3.000, 0.000], [0.000, 4.000])", getShape->info());
  ASSERT_EQ("3", getShape->id());
  ASSERT_EQ("white", getShape->color());
  ASSERT_EQ("Triangle", getShape->type());
}

TEST_F(UtilityTest, getShapeByIdCompoundshapeHaveCompoundhape){
  Shape* getShape = getShapeById(mbox2, "2");
  char ellipseArea[100];
  sprintf(ellipseArea, "%.3f", getShape->area());
  ASSERT_EQ("48.820", std::string(ellipseArea));
  char ellipsePerimeter[100];
  sprintf(ellipsePerimeter, "%.3f", getShape->perimeter());
  ASSERT_EQ("25.248", std::string(ellipsePerimeter));
  ASSERT_EQ("Ellipse (4.200, 3.700)", getShape->info());
  ASSERT_EQ("2", getShape->id());
  ASSERT_EQ("white", getShape->color());
  ASSERT_EQ("Ellipse", getShape->type());
}

TEST_F(UtilityTest, getShapeByIdToDeep){
  Shape* getShape = getShapeById(mbox, "4");
  ASSERT_EQ(30, getShape->area());
  ASSERT_EQ(22, getShape->perimeter());
  ASSERT_EQ("Rectangle (5.000, 6.000)", getShape->info());
  ASSERT_EQ("4", getShape->id());
  ASSERT_EQ("white", getShape->color());
  ASSERT_EQ("Rectangle", getShape->type());
}

TEST_F(UtilityTest, filterShapeTestCreate){
  ASSERT_NO_THROW(std::deque<Shape*> shapes = filterShape(mbox3, AreaFilter(30, 0)));
}

TEST_F(UtilityTest, filterShapeTestCreateRectangleException){
  try{
    std::deque<Shape*> shapes = filterShape(r22, AreaFilter(30, 0));
  }catch(string e){
    ASSERT_EQ("Only compound shape can filter shape!", e);
  }
}

TEST_F(UtilityTest, filterShapeTestCreateEllipseException){
  try{
    std::deque<Shape*> shapes = filterShape(e4237, AreaFilter(30, 0));
  }catch(string e){
    ASSERT_EQ("Only compound shape can filter shape!", e);
  }
}

TEST_F(UtilityTest, filterShapeTestCreateTriangleException){
  try{
    std::deque<Shape*> shapes = filterShape(t345, AreaFilter(30, 0));
  }catch(string e){
    ASSERT_EQ("Only compound shape can filter shape!", e);
  }
}

TEST_F(UtilityTest, filterShapeTestArea){
    std::deque<Shape*> shapes = filterShape(mbox3, AreaFilter(30, 0));
    ASSERT_EQ(3, shapes.size());
}

TEST_F(UtilityTest, filterShapeTestArea2){
    std::deque<Shape*> shapes = filterShape(mbox3, AreaFilter(25, 5));
    ASSERT_EQ(1, shapes.size());
}

TEST_F(UtilityTest, filterShapeTestPerimeter){
    std::deque<Shape*> shapes = filterShape(mbox3, PerimeterFilter(30, 0));
    ASSERT_EQ(3, shapes.size());
}

TEST_F(UtilityTest, filterShapeTestPerimeter2){
    std::deque<Shape*> shapes = filterShape(mbox3, PerimeterFilter(20, 10));
    ASSERT_EQ(1, shapes.size());
}

TEST_F(UtilityTest, filterShapeTestColor){
    std::deque<Shape*> shapes = filterShape(mbox3, ColorFilter("white"));
    ASSERT_EQ(3, shapes.size());
}

TEST_F(UtilityTest, filterShapeTestType){
    std::deque<Shape*> shapes = filterShape(mbox3, TypeFilter("Rectangle"));
    ASSERT_EQ(2, shapes.size());
}

TEST_F(UtilityTest, filterShapeTestType2){
    std::deque<Shape*> shapes = filterShape(mbox3, TypeFilter("Ellipse"));
    ASSERT_EQ(0, shapes.size());
}

TEST_F(UtilityTest, filterShapeTestAreaTo2CompoundShape){
    std::deque<Shape*> shapes = filterShape(mbox2, AreaFilter(50, 30));
    ASSERT_EQ(3, shapes.size());
}

TEST_F(UtilityTest, filterShapeTestPerimeterTo2CompoundShape){
    std::deque<Shape*> shapes = filterShape(mbox2, PerimeterFilter(30, 20));
    ASSERT_EQ(2, shapes.size());
}

TEST_F(UtilityTest, filterShapeTestColorTo2CompoundShape){
    std::deque<Shape*> shapes = filterShape(mbox2, ColorFilter("white"));
    ASSERT_EQ(4, shapes.size());
}

TEST_F(UtilityTest, filterShapeTestTypeTo2CompoundShape){
    std::deque<Shape*> shapes = filterShape(mbox2, TypeFilter("Compound Shape"));
    ASSERT_EQ(1, shapes.size());
}

TEST_F(UtilityTest, filterShapeTestAreaToDeep){
    std::deque<Shape*> shapes = filterShape(mbox, AreaFilter(50, 30));
    ASSERT_EQ(4, shapes.size());
}

TEST_F(UtilityTest, filterShapeTestPerimeterToDeep){
    std::deque<Shape*> shapes = filterShape(mbox, PerimeterFilter(30, 20));
    ASSERT_EQ(3, shapes.size());
}

TEST_F(UtilityTest, filterShapeTestColorToDeep){
    std::deque<Shape*> shapes = filterShape(mbox, ColorFilter("white"));
    ASSERT_EQ(7, shapes.size());
}

TEST_F(UtilityTest, filterShapeTestTypeToDeep){
    std::deque<Shape*> shapes = filterShape(mbox, TypeFilter("Compound Shape"));
    ASSERT_EQ(2, shapes.size());
}
