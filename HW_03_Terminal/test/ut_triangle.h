#include "../src/triangle.h"
TEST(Shapes, CreateTriangle) {
  try {
        std::vector<TwoDimensionalCoordinate*> triangleVector;
        triangleVector.push_back(new TwoDimensionalCoordinate(0, 0));
        triangleVector.push_back(new TwoDimensionalCoordinate(0, 0));
        triangleVector.push_back(new TwoDimensionalCoordinate(0, 0));
        Triangle triangle(triangleVector);
        FAIL();
  }catch(std::string e) {
        ASSERT_EQ("This is not a triangle!", e);
  }
   std::vector<TwoDimensionalCoordinate*> triangleVector;
   triangleVector.push_back(new TwoDimensionalCoordinate(0, 0));
   triangleVector.push_back(new TwoDimensionalCoordinate(3, 0));
   triangleVector.push_back(new TwoDimensionalCoordinate(0, 4));
   ASSERT_NO_THROW(Triangle triangle(triangleVector));

}

TEST(Shapes, AreaTriangle) {
    std::vector<TwoDimensionalCoordinate*> triangleVector;
    triangleVector.push_back(new TwoDimensionalCoordinate(0, 0));
    triangleVector.push_back(new TwoDimensionalCoordinate(3, 0));
    triangleVector.push_back(new TwoDimensionalCoordinate(0, 4));
    Triangle triangle(triangleVector);
    ASSERT_EQ(6, triangle.area());
}

TEST(Shapes, PerimeterTriangle) {
    std::vector<TwoDimensionalCoordinate*> triangleVector;
    triangleVector.push_back(new TwoDimensionalCoordinate(0, 0));
    triangleVector.push_back(new TwoDimensionalCoordinate(3, 0));
    triangleVector.push_back(new TwoDimensionalCoordinate(0, 4));
    Triangle triangle(triangleVector);
    ASSERT_EQ(12, triangle.perimeter());
}

TEST(Shapes, InfoTriangle) {
    std::vector<TwoDimensionalCoordinate*> triangleVector;
    triangleVector.push_back(new TwoDimensionalCoordinate(0, 0));
    triangleVector.push_back(new TwoDimensionalCoordinate(3, 0));
    triangleVector.push_back(new TwoDimensionalCoordinate(0, 4));
    Triangle triangle(triangleVector);
    ASSERT_EQ("Triangle ([0.000, 0.000], [3.000, 0.000], [0.000, 4.000])", triangle.info());
}
