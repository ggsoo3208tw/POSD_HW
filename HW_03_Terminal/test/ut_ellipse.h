#include "../src/ellipse.h"

TEST(Shapes, CreateEllipse) {
    try {
        Ellipse(1, 0);
        FAIL();
    }catch(std::string e) {
        ASSERT_EQ("This is not an ellipse!", e);
    }
    ASSERT_NO_THROW(Ellipse(2, 1));
}

TEST(Shapes, AreaEllipse) {
  Ellipse ellipse(20, 10);
  char ellipseArea[100];
  sprintf(ellipseArea, "%.3f", ellipse.area());
  ASSERT_EQ("628.319",std::string(ellipseArea));
}

TEST(Shapes, PerimeterEllipse) {
  Ellipse ellipse(10, 5);
  char ellipseArea[100];
  sprintf(ellipseArea, "%.3f", ellipse.area());
  ASSERT_EQ("157.080",std::string(ellipseArea));
}

TEST(Shapes, InfoEllipse) {
  Ellipse ellipse(4, 3);
  ASSERT_EQ("Ellipse (4.000, 3.000)", ellipse.info());
}
