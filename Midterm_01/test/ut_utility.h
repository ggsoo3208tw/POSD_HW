#include "../src/folder.h"
#include "../src/app.h"
#include "../src/utility.h"

using namespace std;

class UtilityTestSuite: public testing::Test {
protected:
    virtual void SetUp() {
        chrome = new App("1", "chrome", 50.15);
        facebook = new App("2", "facebook", 30.32);
        instagram = new App("3", "instagram", 20.21);
        youtube = new App("4", "youtube", 70.07);
        ubereat = new App("5", "ubereat", 40.34);
        line = new App("6", "line", 60.66);

        favorite = new Folder("7", "favorite");
        common = new Folder("8", "common");
        community = new Folder("9", "community");
        trash = new Folder("10", "trash");

        favorite->addNode(chrome);
        favorite->addNode(facebook);
        favorite->addNode(common);
        common->addNode(instagram);
        common->addNode(community);
        common->addNode(youtube);
        community->addNode(ubereat);
        community->addNode(line);
        community->addNode(trash);
    }

    virtual void TearDown() {}

    Node* chrome;
    Node* facebook;
    Node* instagram;
    Node* youtube;
    Node* ubereat;
    Node* line;

    Node* favorite;
    Node* common;
    Node* community;
    Node* trash;
};

TEST_F(UtilityTestSuite, exception_for_app_filter_by_size) {
    try {
        filterNode(chrome, SizeFilter(100, 1));
        FAIL();
    }catch(string e) {
        ASSERT_EQ("Only folder can filter node!", e);
    }
}

TEST_F(UtilityTestSuite, folder_filter_by_size_between_80_and_50) {
    deque<Node *> nodes = filterNode(favorite, SizeFilter(80, 50));

    ASSERT_EQ(3, nodes.size());

    EXPECT_EQ("1", nodes[0]->id());
    EXPECT_DOUBLE_EQ(50.15, nodes[0]->size());

    EXPECT_EQ("6", nodes[1]->id());
    EXPECT_DOUBLE_EQ(60.66, nodes[1]->size());

    EXPECT_EQ("4", nodes[2]->id());
    EXPECT_DOUBLE_EQ(70.07, nodes[2]->size());
}

TEST_F(UtilityTestSuite, folder_filter_by_size_between_999_and_0) {
    deque<Node *> nodes = filterNode(favorite, SizeFilter(999, 0));

    ASSERT_EQ(9, nodes.size());

    EXPECT_EQ("1", nodes[0]->id());
    EXPECT_DOUBLE_EQ(50.15, nodes[0]->size());

    EXPECT_EQ("2", nodes[1]->id());
    EXPECT_DOUBLE_EQ(30.32, nodes[1]->size());

    EXPECT_EQ("8", nodes[2]->id());
    EXPECT_DOUBLE_EQ(191.28, nodes[2]->size());

    EXPECT_EQ("3", nodes[3]->id());
    EXPECT_DOUBLE_EQ(20.21, nodes[3]->size());

    EXPECT_EQ("9", nodes[4]->id());
    EXPECT_DOUBLE_EQ(101, nodes[4]->size());

    EXPECT_EQ("5", nodes[5]->id());
    EXPECT_DOUBLE_EQ(40.34, nodes[5]->size());

    EXPECT_EQ("6", nodes[6]->id());
    EXPECT_DOUBLE_EQ(60.66, nodes[6]->size());

    EXPECT_EQ("10", nodes[7]->id());
    EXPECT_DOUBLE_EQ(0, nodes[7]->size());

    EXPECT_EQ("4", nodes[8]->id());
    EXPECT_DOUBLE_EQ(70.07, nodes[8]->size());
}


TEST_F(UtilityTestSuite, folder_filter_by_size_equal_to_zero) {
    deque<Node *> nodes = filterNode(favorite, SizeFilter(0, 0));
    ASSERT_EQ(1, nodes.size());

    EXPECT_EQ("10", nodes[0]->id());
    EXPECT_EQ(0, nodes[0]->size());
}

/* //對不起我以為測資要自己寫 捨不得刪掉
#include "../src/utility.h"
#include "../src/node.h"
#include "../src/app.h"
#include "../src/folder.h"

class UtilityTest : public ::testing::Test {
protected:
  void SetUp() override {
     app1 = new App("1", "app1", 1);
     app2 = new App("2", "app2", 11);
     app3 = new App("3", "app2", 21);
     folder1 = new Folder("4", "folder1");
     folder2 = new Folder("5", "folder2");
     folder1->addNode(app1);
     folder1->addNode(app2);
     folder2->addNode(app3);
     folder2->addNode(folder1);
  }

  void TearDown() override {
      delete app1;
      delete app2;
      delete app3;
      delete folder1;
      delete folder2;
  }


  Node * app1;
  Node * app2;
  Node * app3;
  Node * folder1;
  Node * folder2;
};
TEST_F(UtilityTest, filterNodeTestCreate){
  ASSERT_NO_THROW(std::deque<Node*> nodes = filterNode(folder2, SizeFilter(30, 0)));
}

TEST_F(UtilityTest, filterNodeTestCreateApp1eException){
  try{
    std::deque<Node*> nodes = filterNode(app1, SizeFilter(30, 0));
  }catch(string e){
    ASSERT_EQ("Only folder can filter node!", e);
  }
}

TEST_F(UtilityTest, filterNodeTesSize){
    std::deque<Node*> nodes = filterNode(folder2, SizeFilter(10, 0));
    ASSERT_EQ(1, nodes.size());
}

TEST_F(UtilityTest, filterNodeTesSize2){
    std::deque<Node*> nodes = filterNode(folder1, SizeFilter(10, 0));
    ASSERT_EQ(1, nodes.size());
}

TEST_F(UtilityTest, filterNodeTesSize3){
    std::deque<Node*> nodes = filterNode(folder2, SizeFilter(20, 0));
    ASSERT_EQ(3, nodes.size());
}
*/
