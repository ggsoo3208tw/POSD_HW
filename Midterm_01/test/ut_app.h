#include <gtest/gtest.h>
#include "../src/app.h"

using namespace std;

class AppTestSuite: public testing::Test {
protected:
    virtual void SetUp() {
        googleMap = new App("1", "googleMap", 130.67);
        gmail = new App("2", "gmail", 90.21);
    }

    virtual void TearDown() {}

    Node* googleMap;
    Node* gmail;
};

TEST(AppTest, constructor_no_throw) {
    ASSERT_NO_THROW(App("0", "myApp", 123.456));
}

TEST(AppTest, id) {
    Node* myApp = new App("0", "myApp", 123.456);
    ASSERT_EQ("0", myApp->id());
}

TEST(AppTest, name) {
    Node* myApp = new App("0", "myApp", 123.456);
    ASSERT_EQ("myApp", myApp->name());
}

TEST(AppTest, size) {
    Node* myApp = new App("0", "myApp", 123.456);
    ASSERT_DOUBLE_EQ(123.456, myApp->size());
}

TEST(AppTest, route) {
    Node* myApp = new App("0", "myApp", 123.456);
    ASSERT_EQ("/myApp", myApp->route());
}

TEST(AppTest, update_path) {
    Node* myApp = new App("0", "myApp", 123.456);
    ASSERT_EQ("/myApp", myApp->route());

    myApp->updatePath("/RootFolder");
    EXPECT_EQ("/RootFolder/myApp", myApp->route());

    myApp->updatePath("/favortie");
    EXPECT_EQ("/favortie/myApp", myApp->route());
}

TEST_F(AppTestSuite, add_node_should_throw_exception) {
    try {
        googleMap->addNode(gmail);
    }catch(string e) {
        ASSERT_EQ("only folder can add node.", e);
    }
}

TEST_F(AppTestSuite, delete_node_should_throw_exception) {
    try {
        googleMap->deleteNodeById("2");
    }catch(string e) {
        ASSERT_EQ("only folder can delete node.", e);
    }
}

TEST_F(AppTestSuite, get_node_should_throw_exception) {
    try {
        googleMap->getNodeById("2");
    }catch(string e) {
        ASSERT_EQ("only folder can get node.", e);
    }
}

/*
//對不起我以為測資要自己寫
#include "../src/app.h"
#include "../src/node.h"

TEST(AppTest, CreateApp) {
  ASSERT_NO_THROW(new App("1", "game", 123.456));
}

TEST(AppTest, AppId) {
  Node* app = new App("1", "game", 123.456);
  ASSERT_EQ("1", app->id());
}

TEST(AppTest, AppName) {
  Node* app = new App("1", "game", 123.456);
  ASSERT_EQ("game", app->name());
}

TEST(AppTest, AppSize) {
  Node* app = new App("1", "game", 123.456);
  ASSERT_EQ(123.456, app->size());
}

TEST(AppTest, AppRoute) {
  Node* app = new App("1", "game", 123.456);
  ASSERT_EQ("/game", app->route());
}

TEST(AppTest, AppUpdatePath) {
  Node* app = new App("1", "game", 123.456);
  app->updatePath("file");
  ASSERT_EQ("file/game", app->route());
}

TEST(AppTest, Exception_AppAddNode) {
  Node* app = new App("1", "game", 123.456);
  Node* app2 = new App("2", "book", 456.789);
  try{
    app->addNode(app2);
  }catch(std::string e){
    ASSERT_EQ("only folder can add node.", e);
  }
}

TEST(AppTest, Exception_AppGetNodeById) {
  Node* app = new App("1", "game", 123.456);
  try{
    app->getNodeById("2");
  }catch(std::string e){
    ASSERT_EQ("only folder can get node.", e);
  }
}

TEST(AppTest, Exception_AppDeleteNodeById) {
  Node* app = new App("1", "game", 123.456);
  try{
    app->deleteNodeById("2");
  }catch(std::string e){
    ASSERT_EQ("only folder can delete node.", e);
  }
}
*/
