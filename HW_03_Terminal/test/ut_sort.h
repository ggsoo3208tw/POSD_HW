#include "../src/shape.h"
#include "../src/rectangle.h"
#include "../src/triangle.h"
#include "../src/ellipse.h"
#include "../src/sort.h"

class ShapeSort : public ::testing::Test {
protected:
  void SetUp() override {
     r34 = new Rectangle(3, 4);
     r22 = new Rectangle(2, 2);
     e1010 = new Ellipse(2, 1);
     std::vector<TwoDimensionalCoordinate*> triangleVector;
     triangleVector.push_back(new TwoDimensionalCoordinate(0, 0));
     triangleVector.push_back(new TwoDimensionalCoordinate(3, 0));
     triangleVector.push_back(new TwoDimensionalCoordinate(0, 4));
     t345 = new Triangle(triangleVector);
  }

  void TearDown() override {
      delete r34;
      delete r22;
      delete t345;
      delete e1010;
  }

  Shape * r34;
  Shape * r22;
  Shape * t345;
  Shape * e1010;
};

TEST_F(ShapeSort, SubtypePolymorphism){
  Shape * shapes[4] = {t345, r34, r22, e1010};
  EXPECT_EQ(6, shapes[0]->area());
  EXPECT_EQ(12, shapes[1]->area());
  EXPECT_EQ(4, shapes[2]->area());
  EXPECT_NEAR(6.283, shapes[3]->area(), 0.01);
}

TEST_F(ShapeSort, Sort_areaAscendingCompare){
  std::array<Shape *, 4> shapes = {t345, r34, r22, e1010};
  quickSort(shapes.begin(), shapes.end(), areaAscendingCompare);
  EXPECT_EQ(4, shapes[0]->area());
  EXPECT_EQ(6, shapes[1]->area());
  EXPECT_NEAR(6.283, shapes[2]->area(), 0.01);
  EXPECT_EQ(12, shapes[3]->area());
}
TEST_F(ShapeSort, Sort_areaDescendingCompare){
  std::array<Shape *, 4> shapes = {t345, r34, r22, e1010};
  quickSort(shapes.begin(), shapes.end(), areaDescendingCompare);
  EXPECT_EQ(12, shapes[0]->area());
  EXPECT_NEAR(6.283, shapes[1]->area(), 0.01);
  EXPECT_EQ(6, shapes[2]->area());
  EXPECT_EQ(4, shapes[3]->area());
}
TEST_F(ShapeSort, Sort_perimeterAscendingCompare){
  std::array<Shape *, 4> shapes = {t345, r34, r22, e1010};
  quickSort(shapes.begin(), shapes.end(), perimeterAscendingCompare);
  EXPECT_EQ(8, shapes[0]->perimeter());
  EXPECT_NEAR(10.283, shapes[1]->perimeter(), 0.01);
  EXPECT_EQ(12, shapes[2]->perimeter());
  EXPECT_EQ(14, shapes[3]->perimeter());
}
TEST_F(ShapeSort, Sort_perimeterDescendingCompare){
  std::array<Shape *, 4> shapes = {t345, r34, r22, e1010};
  quickSort(shapes.begin(), shapes.end(), perimeterDescendingCompare);
  EXPECT_EQ(14, shapes[0]->perimeter());
  EXPECT_EQ(12, shapes[1]->perimeter());
  EXPECT_NEAR(10.283, shapes[2]->perimeter(), 0.01);
  EXPECT_EQ(8, shapes[3]->perimeter());
}

TEST_F(ShapeSort, Sort_AscendingCompare_area){
  std::array<Shape *, 4> shapes = {t345, r34, r22, e1010};
  quickSort(shapes.begin(), shapes.end(), AscendingCompare("area"));
  EXPECT_EQ(4, shapes[0]->area());
  EXPECT_EQ(6, shapes[1]->area());
  EXPECT_NEAR(6.283, shapes[2]->area(), 0.01);
  EXPECT_EQ(12, shapes[3]->area());
}

TEST_F(ShapeSort, Sort_AscendingCompare_perimeter){
  std::array<Shape *, 4> shapes = {t345, r34, r22, e1010};
  quickSort(shapes.begin(), shapes.end(), AscendingCompare("perimeter"));
  EXPECT_EQ(8, shapes[0]->perimeter());
  EXPECT_NEAR(10.283, shapes[1]->perimeter(), 0.01);
  EXPECT_EQ(12, shapes[2]->perimeter());
  EXPECT_EQ(14, shapes[3]->perimeter());
}

TEST_F(ShapeSort, Sort_DescendingCompare_area){
  std::array<Shape *, 4> shapes = {t345, r34, r22, e1010};
  quickSort(shapes.begin(), shapes.end(), DescendingCompare("area"));
  EXPECT_EQ(12, shapes[0]->area());
  EXPECT_NEAR(6.283, shapes[1]->area(), 0.01);
  EXPECT_EQ(6, shapes[2]->area());
  EXPECT_EQ(4, shapes[3]->area());
}

TEST_F(ShapeSort, Sort_DescendingCompare_perimeter){
  std::array<Shape *, 4> shapes = {t345, r34, r22, e1010};
  quickSort(shapes.begin(), shapes.end(), DescendingCompare("perimeter"));
  EXPECT_EQ(14, shapes[0]->perimeter());
  EXPECT_EQ(12, shapes[1]->perimeter());
  EXPECT_NEAR(10.283, shapes[2]->perimeter(), 0.01);
  EXPECT_EQ(8, shapes[3]->perimeter());
}
