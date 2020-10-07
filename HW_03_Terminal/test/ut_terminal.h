#include "../src/terminal.h"
TEST(Terminal, NotHaveShapes) {
  try {
      Terminal("perimeter inc");
      FAIL();
  }catch(std::string e) {
      ASSERT_EQ("invalid input", e);
  }
}
TEST(Terminal, NotHaveFeature) {
  try {
      Terminal("Ellipse (3, 4) Rectangle (5, 6) Triangle ([0,-3], [-3,0], [0,-4]) inc");
      FAIL();
  }catch(std::string e) {
      ASSERT_EQ("invalid input", e);
  }
}
TEST(Terminal, NotHaveOrder) {
  try {
      Terminal("Ellipse (3, 4) Rectangle (5, 6) Triangle ([0,-3], [-3,0], [0,-4]) area");
      FAIL();
  }catch(std::string e) {
      ASSERT_EQ("invalid input", e);
  }
}
TEST(Terminal, NotTrueToWightOrHeight) {
  try {
      Terminal("Ellipse (0, 0) Rectangle (-1, -2) area inc");
      FAIL();
  }catch(std::string e) {
      ASSERT_EQ("invalid input", e);
  }
}

TEST(Terminal, MyTest02){
  Terminal terminal("Ellipse (2, 2) Rectangle (2, 2) Triangle ([0, 0], [4, 0], [0, 3]) perimeter inc");
  ASSERT_EQ("8.000\n12.000\n12.566", terminal.showResult());
}
TEST(Terminal, MyTest03){
  Terminal terminal("Ellipse (2, 2) Triangle ([0, 0], [4, 0], [0, 3]) Rectangle (3 ,5 ) perimeter dec");
  ASSERT_EQ("16.000\n12.566\n12.000", terminal.showResult());
}
TEST(Terminal, MyTest04){
  Terminal terminal("Rectangle (1, 2) Triangle ([0, 0], [-4, 0], [0, -3]) Rectangle (30 ,5) perimeter dec");
  ASSERT_EQ("70.000\n12.000\n6.000", terminal.showResult());
}
TEST(Terminal, MyTest05){
  Terminal terminal("Rectangle (1, 2) Triangle ([0, 0], [-4, 0], [0, -3]) Rectangle (30 ,5) Rectangle (60, 18) perimeter dec");
  ASSERT_EQ("156.000\n70.000\n12.000\n6.000", terminal.showResult());
}
TEST(Terminal, MyTest06){
  Terminal terminal("Rectangle (1, 2) Triangle ([0, 0], [-4, 0], [0, -3]) Rectangle (30 ,5) Rectangle (60, 18) area inc");
  ASSERT_EQ("2.000\n6.000\n150.000\n1080.000", terminal.showResult());
}
