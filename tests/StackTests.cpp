#include <gtest/gtest.h>

#include <cstddef>
#include <datastructs/stack.hpp>

TEST(StackTest, Construction) {
    datastructs::Stack<int> stack1(5);

    // 1. Testing push operations
    for (int i = 1; i < 6; ++i) {
        stack1.push(i);
    }
    ASSERT_EQ(stack1.size(), 5);

    // 2. testing pop operations
    for (int i = 5; i > 0; --i) {
        ASSERT_EQ(stack1.pop(), i);
    }
    ASSERT_EQ(stack1.size(), 0);
    ASSERT_TRUE(stack1.isEmpty());
}

TEST(StackTest, CopySemantics) {
    datastructs::Stack<int> stack1(5);
    for (int i = 1; i < 6; ++i) {
        stack1.push(i);
    }

    // 1. Test copy constructor
    datastructs::Stack<int> stack2 = stack1;
    ASSERT_EQ(stack2.size(), 5);
    for (int i = 5; i > 0; --i) {
        ASSERT_EQ(stack2.pop(), i);
    }

    // 2. Test copy assignment
    datastructs::Stack<int> stack3(5);
    for (int i = 1; i < 6; ++i) {
        stack3.push(9);
    }
    stack2 = stack3;
    for (int i = 5; i > 0; --i) {
        ASSERT_EQ(stack2.pop(), 9);
    }
}

TEST(StackTest, MoveSemantics) {
    datastructs::Stack<int> stack1(5);
    for (int i = 1; i < 6; ++i) {
        stack1.push(i);
    }

    // 1. Test move constructor
    datastructs::Stack<int> stack2 = std::move(stack1);
    ASSERT_EQ(stack1.size(), 0);
    ASSERT_EQ(stack2.size(), 5);

    // 2. Move assignment
    stack1 = std::move(stack2);
    ASSERT_EQ(stack1.size(), 5);
    ASSERT_EQ(stack2.size(), 0);

    // validate the values are correct after moving
    for (int i = 5; i > 0; --i) {
        ASSERT_EQ(stack1.pop(), i);
    }
}
