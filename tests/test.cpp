/*
Glushkova Eva st108255@student.spbu.ru
*/

#include <gtest/gtest.h>
#include "../CyclicalList.h"
#include <vector>
#include <string>

TEST(CyclicalListTest, AddAndAccessElements) {
    CyclicalList<int> numbers;
    numbers.append(10);
    numbers.append(20);
    numbers.append(30);

    EXPECT_EQ(numbers.front(), 10);  
    EXPECT_EQ(numbers.back(), 30);   
    EXPECT_EQ(numbers.size(), 3);     
}


TEST(CyclicalListTest, RemoveFromStartAndEnd) {
    CyclicalList<int> numbers;
    numbers.append(1);
    numbers.append(2);
    numbers.append(3);

    numbers.remove_front();
    EXPECT_EQ(numbers.front(), 2);
    EXPECT_EQ(numbers.size(), 2);     

    numbers.remove_back();
    EXPECT_EQ(numbers.back(), 2);
    EXPECT_EQ(numbers.size(), 1);   
}

TEST(CyclicalListTest, InsertAtEnd) {
    CyclicalList<int> numbers;
    numbers.append(1);
    numbers.append(2);
    numbers.insert(numbers.end(), 3);
    EXPECT_EQ(numbers.back(), 3);
    EXPECT_EQ(numbers.size(), 3);     
}

TEST(CyclicalListTest, CopyInitialization) {
    CyclicalList<int> original;
    original.append(10);
    original.append(20);

    CyclicalList<int> duplicate = original;

    EXPECT_EQ(duplicate.size(), 2);    
    EXPECT_EQ(duplicate.front(), 10);  
    EXPECT_EQ(duplicate.back(), 20);
}

TEST(CyclicalListTest, CopyAssignmentOperation) {
    CyclicalList<int> first;
    first.append(5);
    first.append(10);

    CyclicalList<int> second;
    second.append(15);
    second = first;

    EXPECT_EQ(second.size(), 2);   
    EXPECT_EQ(second.front(), 5);
    EXPECT_EQ(second.back(), 10);
}

TEST(CyclicalListTest, EqualityCheckEmptyLists) {
    CyclicalList<int> first;
    CyclicalList<int> second;
    EXPECT_TRUE(first == second); 
    EXPECT_FALSE(first != second);
}

TEST(CyclicalListTest, EqualityCheckSameElements) {
    CyclicalList<int> first;
    CyclicalList<int> second;

    first.append(1);
    first.append(2);
    first.append(3);

    second.append(1);
    second.append(2);
    second.append(3);

    EXPECT_TRUE(first == second);
    EXPECT_FALSE(first != second);
}

TEST(CyclicalListTest, InequalityCheckDifferentValues) {
    CyclicalList<int> first;
    CyclicalList<int> second;

    first.append(1);
    first.append(2);
    first.append(3);

    second.append(1);
    second.append(99);
    second.append(3);

    EXPECT_FALSE(first == second);      
    EXPECT_TRUE(first != second);
}

TEST(CyclicalListTest, EqualityAfterCopyOperation) {
    CyclicalList<std::string> original;
    original.append("alpha");
    original.append("beta");

    CyclicalList<std::string> copy = original;

    EXPECT_TRUE(original == copy);
    EXPECT_FALSE(original != copy);
}

TEST(CyclicalListTest, EqualityAfterMoveOperation) {
    CyclicalList<int> original;
    original.append(10);
    original.append(20);

    CyclicalList<int> moved = std::move(original);

    CyclicalList<int> expected_result;
    expected_result.append(10);
    expected_result.append(20);

    EXPECT_TRUE(moved == expected_result); 
}

TEST(CyclicalListTest, EmptyListRemoveFrontError) {
    CyclicalList<int> empty_list;
    EXPECT_THROW(empty_list.remove_front(), std::out_of_range);
}

TEST(CyclicalListTest, EmptyListRemoveBackError) {
    CyclicalList<int> empty_list;
    EXPECT_THROW(empty_list.remove_back(), std::out_of_range);
}

TEST(CyclicalListTest, InvalidIteratorEraseError) {
    CyclicalList<int> numbers;
    EXPECT_THROW(numbers.erase(numbers.end()), std::out_of_range);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}