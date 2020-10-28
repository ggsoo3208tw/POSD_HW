#include <gtest/gtest.h>
#include "../src/folder.h"
#include "../src/app.h"

using namespace std;

class FolderTestSuite: public testing::Test {
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

    }

    void addNodes() {
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

TEST(FolderTest, constructor_no_throw) {
    ASSERT_NO_THROW(Folder("0", "rootFolder"));
}

TEST(FolderTest, id) {
    Node* rootFolder = new Folder("0", "rootFolder");
    ASSERT_EQ("0", rootFolder->id());
}

TEST(FolderTest, name) {
    Node* rootFolder = new Folder("0", "rootFolder");
    ASSERT_EQ("rootFolder", rootFolder->name());
}

TEST(FolderTest, route) {
    Node* rootFolder = new Folder("0", "rootFolder");
    ASSERT_EQ("/rootFolder", rootFolder->route());
}

TEST(FolderTest, size) {
    Node* rootFolder = new Folder("0", "rootFolder");
    ASSERT_DOUBLE_EQ(0, rootFolder->size());
}

TEST(FolderTest, update_path) {
    Node* rootFolder = new Folder("0", "rootFolder");
    ASSERT_EQ("/rootFolder", rootFolder->route());

    rootFolder->updatePath("/usr");
    EXPECT_EQ("/usr/rootFolder", rootFolder->route());
}

TEST_F(FolderTestSuite, size_change_after_add_nodes){

    ASSERT_EQ(0, trash->size());
    ASSERT_EQ(0, community->size());
    ASSERT_EQ(0, common->size());
    ASSERT_EQ(0, favorite->size());

    addNodes();

    EXPECT_DOUBLE_EQ(0, trash->size());
    EXPECT_DOUBLE_EQ(101, community->size());
    EXPECT_DOUBLE_EQ(191.28, common->size());
    EXPECT_DOUBLE_EQ(271.75, favorite->size());
}

TEST_F(FolderTestSuite, route_change_after_add_nodes){

    ASSERT_EQ("/favorite", favorite->route());
    ASSERT_EQ("/chrome", chrome->route());
    ASSERT_EQ("/facebook", facebook->route());
    ASSERT_EQ("/common", common->route());

    ASSERT_EQ("/instagram", instagram->route());
    ASSERT_EQ("/youtube", youtube->route());
    ASSERT_EQ("/community", community->route());

    ASSERT_EQ("/ubereat", ubereat->route());
    ASSERT_EQ("/line", line->route());
    ASSERT_EQ("/trash", trash->route());

    addNodes();

    EXPECT_EQ("/favorite", favorite->route());
    EXPECT_EQ("/favorite/chrome", chrome->route());
    EXPECT_EQ("/favorite/facebook", facebook->route());
    EXPECT_EQ("/favorite/common", common->route());

    EXPECT_EQ("/favorite/common/instagram", instagram->route());
    EXPECT_EQ("/favorite/common/youtube", youtube->route());
    EXPECT_EQ("/favorite/common/community", community->route());

    EXPECT_EQ("/favorite/common/community/ubereat", ubereat->route());
    EXPECT_EQ("/favorite/common/community/line", line->route());
    EXPECT_EQ("/favorite/common/community/trash", trash->route());
}

TEST_F(FolderTestSuite, get_node){
    addNodes();

    Node* folder_9 = favorite->getNodeById("9");

    EXPECT_EQ("9", folder_9->id());
    EXPECT_EQ("community", folder_9->name());
    EXPECT_DOUBLE_EQ(101, folder_9->size());

    Node* app_6 = favorite->getNodeById("6");

    EXPECT_EQ("6", app_6->id());
    EXPECT_EQ("line", app_6->name());
    EXPECT_DOUBLE_EQ(60.66, app_6->size());
}

TEST_F(FolderTestSuite, get_not_exist_node_should_throw_exception) {
    addNodes();

    try {
        favorite->getNodeById("-1");
        FAIL();
    }catch(string e) {
        ASSERT_EQ("Expected get node but node not found.", e);
    }

    try {
        community->getNodeById("8");
        FAIL();
    }catch(string e) {
        ASSERT_EQ("Expected get node but node not found.", e);
    }
}

TEST_F(FolderTestSuite, delete_node){

    addNodes();

    ASSERT_DOUBLE_EQ(0, trash->size());
    ASSERT_DOUBLE_EQ(101, community->size());
    ASSERT_DOUBLE_EQ(191.28, common->size());
    ASSERT_DOUBLE_EQ(271.75, favorite->size());

    ASSERT_NO_THROW(favorite->deleteNodeById("9"));

    try {
        favorite->getNodeById("9");
        FAIL();
    }catch(string e) {
        ASSERT_EQ("Expected get node but node not found.", e);
    }

    EXPECT_DOUBLE_EQ(0, trash->size());
    EXPECT_DOUBLE_EQ(101, community->size());
    EXPECT_DOUBLE_EQ(90.28, common->size());
    EXPECT_DOUBLE_EQ(170.75, favorite->size());

    ASSERT_NO_THROW(favorite->deleteNodeById("8"));

    try {
        favorite->getNodeById("8");
        FAIL();
    }catch(string e) {
        ASSERT_EQ("Expected get node but node not found.", e);
    }

    EXPECT_DOUBLE_EQ(0, trash->size());
    EXPECT_DOUBLE_EQ(101, community->size());
    EXPECT_DOUBLE_EQ(90.28, common->size());
    EXPECT_DOUBLE_EQ(80.47, favorite->size());
}

TEST_F(FolderTestSuite, delete_not_exist_node_should_thorw_exception){
    addNodes();
    try {
        favorite->deleteNodeById("-1");
        FAIL();
    }catch(string s) {
        ASSERT_EQ("Expected delete node but node not found.", s);
    }

    try {
        community->deleteNodeById("7");
        FAIL();
    }catch(string s) {
        ASSERT_EQ("Expected delete node but node not found.", s);
    }
}


/*
//對不起我以為測資自己寫
#include "../src/folder.h"
#include "../src/app.h"
#include "../src/node.h"

TEST(FolderTest, CreateFolder){
  ASSERT_NO_THROW(new Folder("1", "myFolder"));
}

TEST(FolderTest, FolderSize){
  Node* folder = new Folder("1", "myFolder");
  ASSERT_EQ(0, folder->size());
}

TEST(FolderTest, FolderId){
  Node* folder = new Folder("1", "myFolder");
  ASSERT_EQ("1", folder->id());
}

TEST(FolderTest, FolderName){
  Node* folder = new Folder("1", "myFolder");
  ASSERT_EQ("myFolder", folder->name());
}

TEST(FolderTest, FolderRoute){
  Node* folder = new Folder("1", "myFolder");
  ASSERT_EQ("/myFolder", folder->route());
}

TEST(FolderTest, FolderAddNodeToAppRoute){
  Node* folder = new Folder("1", "myFolder");
  Node* app = new App("2", "myApp", 1.23);
  Node* app2 = new App("3", "myApp2", 2.34);
  ((Folder*)folder)->addNode(app);
  ((Folder*)folder)->addNode(app2);
  ASSERT_EQ("/myFolder/myApp", app->route());
}

TEST(FolderTest, FolderAddNode){
  Node* folder = new Folder("1", "myFolder");
  Node* app = new App("2", "myApp", 1.23);
  Node* app2 = new App("3", "myApp2", 2.34);
  ((Folder*)folder)->addNode(app);
  ((Folder*)folder)->addNode(app2);
  ASSERT_EQ(3.57, folder->size());
}

TEST(FolderTest, FolderUpdatePath){
  Node* folder = new Folder("1", "myFolder");
  Node* app = new App("2", "myApp", 1.23);
  Node* app2 = new App("3", "myApp2", 2.34);
  ((Folder*)folder)->addNode(app);
  ((Folder*)folder)->addNode(app2);
  folder->updatePath("123");
  ASSERT_EQ("123/myFolder", folder->route());
}

TEST(FolderTest, FolderUpdatePathAppRoute){
  Node* folder = new Folder("1", "myFolder");
  Node* app = new App("2", "myApp", 1.23);
  Node* app2 = new App("3", "myApp2", 2.34);
  ((Folder*)folder)->addNode(app);
  ((Folder*)folder)->addNode(app2);
  folder->updatePath("123");
  ASSERT_EQ("123/myFolder/myApp", app->route());
}

TEST(FolderTest, FolderGetNodeById){
  Node* folder = new Folder("1", "myFolder");
  Node* app = new App("2", "myApp", 1.23);
  Node* app2 = new App("3", "myApp2", 2.34);
  folder->addNode(app);
  folder->addNode(app2);
  Node* app3 = ((Folder*)folder)->getNodeById("2");
  ASSERT_EQ("myApp", app3->name());
}

TEST(FolderTest, FolderDeleteNodeById){
  Node* folder = new Folder("1", "myFolder");
  Node* app = new App("2", "myApp", 1.23);
  Node* app2 = new App("3", "myApp2", 2.34);
  folder->addNode(app);
  folder->addNode(app2);
  folder->deleteNodeById("2");
  ASSERT_EQ(2.34, folder->size());
}

TEST(FolderTest, FolderDeleteNodeByIdToDeep){
  Node* folder = new Folder("1", "myFolder");
  Node* app = new App("2", "myApp", 1.23);
  Node* app2 = new App("3", "myApp2", 2.34);
  Node* folder2 = new Folder("4", "Folder2");
  folder->addNode(app);
  folder->addNode(app2);
  folder2->addNode(folder);
  folder2->deleteNodeById("2");
  ASSERT_EQ(2.34, folder->size());
}

TEST(FolderTest, FolderGetNodeByIdToDeep){
  Node* folder = new Folder("1", "Folder1");
  Node* app = new App("2", "App1", 1.23);
  Node* app2 = new App("3", "App2", 2.34);
  Node* folder2 = new Folder("4", "Folder2");
  folder->addNode(app);
  folder->addNode(app2);
  folder2->addNode(folder);
  Node* app3 = folder2->getNodeById("2");
  ASSERT_EQ("App1", app3->name());
}

TEST(FolderTest, Exception_FolderGetNodeById){
  Node* folder = new Folder("1", "myFolder");
  Node* app = new App("2", "myApp", 1.23);
  Node* app2 = new App("3", "myApp2", 2.34);
  folder->addNode(app);
  folder->addNode(app2);
  Node* app3;
  try{
    app3 = folder->getNodeById("4");
    std::cout << app3->name();
  }catch(std::string e){
    ASSERT_EQ("Expected get node but node not found.", e);
  }
}

TEST(FolderTest, Exception_FolderGetNodeByIdByDeep){
  Node* folder = new Folder("1", "Folder1");
  Node* app = new App("2", "App1", 1.23);
  Node* app2 = new App("3", "App2", 2.34);
  Node* folder2 = new Folder("4", "Folder2");
  folder->addNode(app);
  folder->addNode(app2);
  folder2->addNode(folder);
  try{
    Node* app3 = folder2->getNodeById("99");
    std::cout << app3->name();
  }catch(std::string e){
    ASSERT_EQ("Expected get node but node not found.", e);
  }
}
*/
