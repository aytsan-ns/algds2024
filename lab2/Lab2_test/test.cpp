#include "pch.h"
#include "C:\Users\nasty\3D Objects\Цифровой практикум\CloneRep1\algds2024\lab2\Project1\Function.c"
#include "C:\Users\nasty\3D Objects\Цифровой практикум\CloneRep1\algds2024\lab2\Project1\Header.h"

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

TEST(FatherTest, EmptyTree) {
    struct tree* T = NULL;
    EXPECT_EQ(Father(T, 5), NULL);
}

TEST(FatherTest, ElementNotFound) {
    struct tree* T = (struct tree*)malloc(sizeof(struct tree));
    T->key = 10;
    T->left = NULL;
    T->right = NULL;
    EXPECT_EQ(Father(T, 5), NULL);
    free(T);
}

TEST(FatherTest, ElementIsRoot) {
    struct tree* T = (struct tree*)malloc(sizeof(struct tree));
    T->key = 10;
    T->left = NULL;
    T->right = NULL;
    EXPECT_EQ(Father(T, 10), NULL);
    free(T);
}

TEST(FatherTest, ElementIsLeftChild) {
    struct tree* T = (struct tree*)malloc(sizeof(struct tree));
    T->key = 10;
    T->left = (struct tree*)malloc(sizeof(struct tree));
    T->left->key = 5;
    T->left->left = NULL;
    T->left->right = NULL;
    T->right = NULL;
    EXPECT_EQ(Father(T, 5), T);
    free(T->left);
    free(T);
}

TEST(GrandFatherTest, EmptyTree) {
    struct tree* T = NULL;
    EXPECT_EQ(GrandFather(T, 5), NULL);
}

TEST(GrandFatherTest, NoGrandFather) {
    struct tree* T = (struct tree*)malloc(sizeof(struct tree));
    T->key = 10;
    T->left = (struct tree*)malloc(sizeof(struct tree));
    T->left->key = 5;
    T->left->left = NULL;
    T->left->right = NULL;
    T->right = NULL;
    EXPECT_EQ(GrandFather(T, 10), NULL);
    EXPECT_EQ(GrandFather(T, 5), NULL);
    free(T->left);
    free(T);
}

TEST(GrandFatherTest, WithGrandparent) {
    struct tree* T = (struct tree*)malloc(sizeof(struct tree));
    T->key = 10;
    T->left = (struct tree*)malloc(sizeof(struct tree));
    T->left->key = 5;
    T->left->left = NULL;
    T->left->right = (struct tree*)malloc(sizeof(struct tree));
    T->left->right->key = 15;
    T->left->right->left = NULL;
    T->left->right->right = NULL;
    T->right = NULL;
    EXPECT_EQ(GrandFather(T, 15), T);
    free(T->left->right);
    free(T->left);
    free(T);
}

TEST(ListTest, EmptyTree) {
    struct tree* T = NULL;
    EXPECT_EQ(List(T, 5), NULL);
}

TEST(ListTest, KeyInRoot) {
    struct tree* T = (struct tree*)malloc(sizeof(struct tree));
    T->key = 10;
    T->left = NULL;
    T->right = NULL;
    EXPECT_EQ(List(T, 10), T);
    free(T);
}

TEST(ListTest, KeyInSubtree) {
    struct tree* T = (struct tree*)malloc(sizeof(struct tree));
    T->key = 10;
    T->left = (struct tree*)malloc(sizeof(struct tree));
    T->left->key = 5;
    T->left->left = NULL;
    T->left->right = NULL;
    T->right = (struct tree*)malloc(sizeof(struct tree));
    T->right->key = 15;
    T->right->left = NULL;
    T->right->right = NULL;
    EXPECT_EQ(List(T, 5), T->left);
    EXPECT_EQ(List(T, 15), T->right);
    free(T->right);
    free(T->left);
    free(T);
}

TEST(BalanceTest, EmptyTree) {
    struct tree* T = NULL;
    T = Balance(T, 5);
    EXPECT_EQ(T, NULL);
}

TEST(BalanceTest, ElementNotFound) {
    struct tree* T = (struct tree*)malloc(sizeof(struct tree));
    T->key = 10;
    T->color = "BLACK";
    T->left = NULL;
    T->right = NULL;
    T = Balance(T, 5);
    EXPECT_EQ(T->color, "BLACK");
    free(T);
}

TEST(AppendElementTest, MemoryAllocated) {
    int key = 10;
    struct tree* element = AppendElement(key);
    EXPECT_EQ(element->key, key);
    EXPECT_STREQ(element->color, "RED");
    EXPECT_EQ(element->left, NULL);
    EXPECT_EQ(element->right, NULL);
    free(element);
}

TEST(DeleteTest, DeleteRoot) {
    struct tree* T = (struct tree*)malloc(sizeof(struct tree));
    T->key = 10;
    T->left = NULL;
    T->right = NULL;
    T = Delete(T, 10);
    EXPECT_EQ(T, NULL);
    free(T);
}

TEST(DeleteTest, DeleteChild) {
    struct tree* T = (struct tree*)malloc(sizeof(struct tree));
    T->key = 10;
    T->left = (struct tree*)malloc(sizeof(struct tree));
    T->left->key = 5;
    T->left->left = NULL;
    T->left->right = NULL;
    T->right = (struct tree*)malloc(sizeof(struct tree));
    T->right->key = 15;
    T->right->left = NULL;
    T->right->right = NULL;
    T = Delete(T, 15);
    EXPECT_EQ(T->right, NULL);
    T = Delete(T, 5);
    EXPECT_EQ(T->left, NULL);
    free(T);
}

TEST(MaxLeftTest, EmptyTree) {
    struct tree* T = NULL;
    struct tree* maxLeft = MaxLeft(T);
    EXPECT_EQ(maxLeft, NULL);
}

TEST(MaxLeftTest, SingleElement) {
    struct tree* T = (struct tree*)malloc(sizeof(struct tree));
    T->key = 10;
    T->left = NULL;
    T->right = NULL;
    struct tree* maxLeft = MaxLeft(T);
    EXPECT_EQ(maxLeft->key, 10);
    free(T);
}

TEST(MaxLeftTest, MaxInRightSubtree) {
    struct tree* T = (struct tree*)malloc(sizeof(struct tree));
    T->key = 10;
    T->left = (struct tree*)malloc(sizeof(struct tree));
    T->left->key = 5;
    T->left->left = NULL;
    T->left->right = NULL;
    T->right = (struct tree*)malloc(sizeof(struct tree));
    T->right->key = 15;
    T->right->left = NULL;
    T->right->right = NULL;
    struct tree* maxLeft = MaxLeft(T);
    EXPECT_EQ(maxLeft->key, 15);
    free(T->right);
    free(T->left);
    free(T);
}

TEST(MinRightTest, EmptyTree) {
    struct tree* T = NULL;
    struct tree* minRight = MinRight(T);
    EXPECT_EQ(minRight, NULL);
}

TEST(MinRightTest, SingleElement) {
    struct tree* T = (struct tree*)malloc(sizeof(struct tree));
    T->key = 10;
    T->left = NULL;
    T->right = NULL;
    struct tree* minRight = MinRight(T);
    EXPECT_EQ(minRight->key, 10);
    free(T);
}

TEST(MinRightTest, MinInLeftSubtree) {
    struct tree* T = (struct tree*)malloc(sizeof(struct tree));
    T->key = 10;
    T->left = (struct tree*)malloc(sizeof(struct tree));
    T->left->key = 5;
    T->left->left = NULL;
    T->left->right = NULL;
    T->right = (struct tree*)malloc(sizeof(struct tree));
    T->right->key = 15;
    T->right->left = NULL;
    T->right->right = NULL;
    struct tree* minRight = MinRight(T);
    EXPECT_EQ(minRight->key, 5);
    free(T->right);
    free(T->left);
    free(T);
}

TEST(DeleteBlackTest, NoChildren) {
    struct tree* T = (struct tree*)malloc(sizeof(struct tree));
    T->key = 10;
    T->left = NULL;
    T->right = NULL;
    T->color = "BLACK";
    T = DeleteBlack(T, 10);
    EXPECT_EQ(T, NULL);
    free(T);
}

TEST(DeleteBlackTest, LeftChildOnly) {
    struct tree* T = (struct tree*)malloc(sizeof(struct tree));
    T->key = 10;
    T->left = (struct tree*)malloc(sizeof(struct tree));
    T->left->key = 5;
    T->left->left = NULL;
    T->left->right = NULL;
    T->right = NULL;
    T->color = "BLACK";
    T->left->color = "BLACK";
    T = DeleteBlack(T, 10);
    EXPECT_EQ(T->key, 5);
    free(T->left);
    free(T);
}

TEST(DeleteBlackTest, RightChildOnly) {
    struct tree* T = (struct tree*)malloc(sizeof(struct tree));
    T->key = 10;
    T->right = (struct tree*)malloc(sizeof(struct tree));
    T->right->key = 15;
    T->right->left = NULL;
    T->right->right = NULL;
    T->left = NULL;
    T->color = "BLACK";
    T->right->color = "BLACK";
    T = DeleteBlack(T, 10);
    EXPECT_EQ(T->key, 15);
    free(T->right);
    free(T);
}

TEST(DeleteBlackTest, BothChildren) {
    struct tree* T = (struct tree*)malloc(sizeof(struct tree));
    T->key = 10;
    T->left = (struct tree*)malloc(sizeof(struct tree));
    T->left->key = 5;
    T->left->left = NULL;
    T->left->right = NULL;
    T->right = (struct tree*)malloc(sizeof(struct tree));
    T->right->key = 15;
    T->right->left = NULL;
    T->right->right = NULL;
    T->color = "BLACK";
    T->left->color = "BLACK";
    T->right->color = "BLACK";
    T = DeleteBlack(T, 10);
    EXPECT_TRUE(T->key == 5 || T->key == 15);
    free(T->right);
    free(T->left);
    free(T);
}

TEST(DeleteElementTest, ElementNotFound) {
    struct tree* T = (struct tree*)malloc(sizeof(struct tree));
    T->key = 10;
    T->left = NULL;
    T->right = NULL;
    T->color = "BLACK";
    struct tree* result = DeleteElement(T, 5);
    EXPECT_EQ(result, T);
    free(T);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}