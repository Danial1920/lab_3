#include <gtest/gtest.h>
#include <vector>
#include <algorithm>
#include "../KwayMerge.h"

class MergeTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(MergeTest, EmptyArray) {
    std::vector<int> tmp;
    EXPECT_EQ(KwayMergeSort(tmp).size(), 0);
}

TEST_F(MergeTest, BasicSorting) {
    std::vector<int> input = {5, 3, 8, 1, 9, 2, 7, 4};
    std::vector<int> expected = {1, 2, 3, 4, 5, 7, 8, 9};
    
    auto result = KwayMergeSort(input, 2, 2);
    EXPECT_EQ(result, expected);
}

TEST_F(MergeTest, DuplicatesAndNegatives) {
    std::vector<int> input = {10, -1, 5, 5, -10, 0, 2};
    std::vector<int> expected = {-10, -1, 0, 2, 5, 5, 10};
    
    auto result = KwayMergeSort(input, 3, 3);
    EXPECT_EQ(result, expected);
}

TEST_F(MergeTest, AlreadySorted) {
    std::vector<int> input = {1, 2, 3, 4, 5};
    std::vector<int> expected = {1, 2, 3, 4, 5};
    
    auto result = KwayMergeSort(input, 2, 1);
    EXPECT_EQ(result, expected);
}

TEST_F(MergeTest, SingleElement) {
    std::vector<int> input = {42};
    std::vector<int> expected = {42};
    
    auto result = KwayMergeSort(input);
    EXPECT_EQ(result, expected);
}