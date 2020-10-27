#include "../src/shape_iterator.h"
#include "../src/shape.h"
#include "../src/rectangle.h"
#include "../src/ellipse.h"
#include "../src/triangle.h"

class IteratorTest : public ::testing::Test {
protected:
  void SetUp() override {
     r34 = new Rectangle("1", 3, 4);
     r22 = new Rectangle("2", 2, 2);
     e4737 = new Ellipse("3", 4.2, 3.7);
     std::vector<TwoDimensionalCoordinate*> triangleVector;
     triangleVector.push_back(new TwoDimensionalCoordinate(0, 0));
     triangleVector.push_back(new TwoDimensionalCoordinate(3, 0));
     triangleVector.push_back(new TwoDimensionalCoordinate(0, 4));
     t345 = new Triangle("4", triangleVector);
     std::list<Shape*> mboxList = {r34, e4737, t345};
     mbox = new CompoundShape("100", mboxList);
     std::list<Shape*> mbox2List = {r22, t345};
     mbox2 = new CompoundShape("101", mbox2List);
     mbox->addShape(mbox2);
  }

  void TearDown() override {
      delete mbox;
      delete mbox2;
      delete r34;
      delete r22;
      delete e4737;
      delete t345;
  }

  Shape * r34;
  Shape * r22;
  Shape * e4737;
  Shape * t345;
  Shape * mbox;
  Shape * mbox2;
};

TEST_F(IteratorTest, ListIteratot){
  std::list<int> l = {0, 1, 2};
  std::list<int>::iterator it = l.begin();
  ASSERT_EQ(0, *it++);
  ASSERT_EQ(1, *it++);
  ASSERT_EQ(2, *it++);
  ASSERT_EQ(l.end(), it);
}


TEST_F(IteratorTest, CompoundShapeIteratorNew) {
  Iterator * it = mbox2->createIterator();
  ASSERT_EQ(4, it->currentItem()->area());
  it->next();
  ASSERT_EQ(6, it->currentItem()->area());
  it->next();
  ASSERT_TRUE(it->isDone());
}

TEST_F(IteratorTest, NullIteratorIsDone) {
  Iterator * it = r34->createIterator();
  ASSERT_TRUE(it->isDone());
}

TEST_F(IteratorTest, NullIteratorCurrentItem) {
  Iterator * it = r34->createIterator();
  try{
    it->currentItem();
  }catch(std::string e){
    ASSERT_EQ("No child member!", e);
  }
}

TEST_F(IteratorTest, NullIteratorNext) {
  Iterator * it = r34->createIterator();
  try{
    it->next();
  }catch(std::string e){
    ASSERT_EQ("No child member!", e);
  }
}

TEST_F(IteratorTest, NullIteratorFirst) {
  Iterator * it = r34->createIterator();
  try{
    it->first();
  }catch(std::string e){
    ASSERT_EQ("No child member!", e);
  }
}

TEST_F(IteratorTest, RectangleIterator_Exception) {
  Iterator * it = r34->createIterator();
  try{
    it->currentItem();
  }catch(std::string e){
    ASSERT_EQ("No child member!", e);
  }
}

TEST_F(IteratorTest, EllipseIterator_Exception) {
  Iterator * it = e4737->createIterator();
  try{
    it->currentItem();
  }catch(std::string e){
    ASSERT_EQ("No child member!", e);
  }
}

TEST_F(IteratorTest, TriangleIterator_Exception) {
  Iterator * it = t345->createIterator();
  try{
    it->currentItem();
  }catch(std::string e){
    ASSERT_EQ("No child member!", e);
  }
}

TEST_F(IteratorTest, CompoundShapeIteratorToMbox1Area) {
  Iterator * it = mbox->createIterator();
  ASSERT_EQ(12, it->currentItem()->area());
  it->next();
  char ellipseArea[100];
  sprintf(ellipseArea, "%.3f", it->currentItem()->area());
  ASSERT_EQ("48.820", std::string(ellipseArea));
  it->next();
  ASSERT_EQ(6, it->currentItem()->area());
  it->next();
  ASSERT_EQ(10, it->currentItem()->area());
  it->next();
  ASSERT_TRUE(it->isDone());
}

TEST_F(IteratorTest, CompoundShapeIteratorToMbox1Perimeter) {
  Iterator * it = mbox->createIterator();
  ASSERT_EQ(14, it->currentItem()->perimeter());
  it->next();
  char ellipsePerimeter[100];
  sprintf(ellipsePerimeter, "%.3f", it->currentItem()->perimeter());
  ASSERT_EQ("25.248", std::string(ellipsePerimeter));
  it->next();
  ASSERT_EQ(12, it->currentItem()->perimeter());
  it->next();
  ASSERT_EQ(20, it->currentItem()->perimeter());
  it->next();
  ASSERT_TRUE(it->isDone());
}

TEST_F(IteratorTest, CompoundShapeIteratorToMbox1Info) {
  Iterator * it = mbox->createIterator();
  ASSERT_EQ("Rectangle (3.000, 4.000)", it->currentItem()->info());
  it->next();
  ASSERT_EQ("Ellipse (4.200, 3.700)", it->currentItem()->info());
  it->next();
  ASSERT_EQ("Triangle ([0.000, 0.000], [3.000, 0.000], [0.000, 4.000])", it->currentItem()->info());
  it->next();
  ASSERT_EQ("Compound Shape {Rectangle (2.000, 2.000), Triangle ([0.000, 0.000], [3.000, 0.000], [0.000, 4.000])}", it->currentItem()->info());
  it->next();
  ASSERT_TRUE(it->isDone());
}

TEST_F(IteratorTest, CompoundShapeIteratorToMbox1Type) {
  Iterator * it = mbox->createIterator();
  ASSERT_EQ("Rectangle", it->currentItem()->type());
  it->next();
  ASSERT_EQ("Ellipse", it->currentItem()->type());
  it->next();
  ASSERT_EQ("Triangle", it->currentItem()->type());
  it->next();
  ASSERT_EQ("Compound Shape", it->currentItem()->type());
  it->next();
  ASSERT_TRUE(it->isDone());
}

TEST_F(IteratorTest, CompoundShapeIteratorToMbox1Id) {
  Iterator * it = mbox->createIterator();
  ASSERT_EQ("1", it->currentItem()->id());
  it->next();
  ASSERT_EQ("3", it->currentItem()->id());
  it->next();
  ASSERT_EQ("4", it->currentItem()->id());
  it->next();
  ASSERT_EQ("101", it->currentItem()->id());
  it->next();
  ASSERT_TRUE(it->isDone());
}

TEST_F(IteratorTest, CompoundShapeIteratorToMbox1Color) {
  Iterator * it = mbox->createIterator();
  ASSERT_EQ("white", it->currentItem()->color());
  it->next();
  ASSERT_EQ("white", it->currentItem()->color());
  it->next();
  ASSERT_EQ("white", it->currentItem()->color());
  it->next();
  ASSERT_EQ("transparent", it->currentItem()->color());
  it->next();
  ASSERT_TRUE(it->isDone());
}

TEST_F(IteratorTest, CompoundShapeIteratorExceptionOfRange) {
  Iterator * it = mbox2->createIterator();
  ASSERT_EQ("white", it->currentItem()->color());
  it->next();
  ASSERT_EQ("white", it->currentItem()->color());
  it->next();
  ASSERT_TRUE(it->isDone());
  try{
    it->next();
  }catch(std::string e){
    ASSERT_EQ("Moving past the end!", e);
  }
}

TEST_F(IteratorTest, CompoundShapeIteratorFirst) {
  Iterator * it = mbox2->createIterator();
  ASSERT_EQ("white", it->currentItem()->color());
  it->next();
  ASSERT_EQ("white", it->currentItem()->color());
  it->next();
  ASSERT_TRUE(it->isDone());
  it->first();
  ASSERT_EQ("white", it->currentItem()->color());
  it->next();
  ASSERT_EQ("white", it->currentItem()->color());
  it->next();
  ASSERT_TRUE(it->isDone());
}

TEST_F(IteratorTest, CompoundShapeIteratorCurrentItem) {
  Iterator * it = mbox2->createIterator();
  ASSERT_EQ(4, it->currentItem()->area());
  it->next();
  ASSERT_EQ(6, it->currentItem()->area());
  it->next();
  ASSERT_TRUE(it->isDone());
}

TEST_F(IteratorTest, CompoundShapeIteratorIsDone) {
  Iterator * it = mbox2->createIterator();
  ASSERT_EQ(8, it->currentItem()->perimeter());
  it->next();
  ASSERT_EQ(12, it->currentItem()->perimeter());
  it->next();
  ASSERT_TRUE(it->isDone());
}

TEST_F(IteratorTest, CompoundShapeIteratorIsNext) {
  Iterator * it = mbox2->createIterator();
  ASSERT_EQ("Rectangle (2.000, 2.000)", it->currentItem()->info());
  it->next();
  ASSERT_EQ("Triangle ([0.000, 0.000], [3.000, 0.000], [0.000, 4.000])", it->currentItem()->info());
  it->next();
  ASSERT_TRUE(it->isDone());
}
