#include <gtest/gtest.h>

#include <cstddef>
#include <datastructs/queue.hpp>

TEST(QueueTests, Construction) {
    datastructs::Queue<int> queue1(5);
    for (int i = 1; i < 6; ++i) {
        queue1.enqueue(i);
    }

    // 1. Validate front is first item pushed
    ASSERT_EQ(queue1.front(), 1);

    // 2. Validate last-in first-out operation
    for (int i = 1; i < 6; ++i) {
        ASSERT_EQ(queue1.dequeue(), i);
    }

    // 3. Check if queue is empty
    ASSERT_TRUE(queue1.IsEmpty());
}

TEST(QueueTests, CopySemantics) {
    datastructs::Queue<int> queue1(5);
    for (int i = 1; i < 6; ++i) {
        queue1.enqueue(i);
    }

    datastructs::Queue<int> queue2 = queue1;

    // 2. Validate queue was copied
    for (int i = 1; i < 6; ++i) {
        ASSERT_EQ(queue2.dequeue(), i);
    }
}

TEST(QueueTests, MoveSemantics) {
    datastructs::Queue<int> queue1(5);
    for (int i = 1; i < 6; ++i) {
        queue1.enqueue(i);
    }

    datastructs::Queue<int> queue2 = std::move(queue1);

    // 2. Validate queue was moved
    for (int i = 1; i < 6; ++i) {
        ASSERT_EQ(queue2.dequeue(), i);
    }

    ASSERT_THROW(queue1.dequeue(), std::length_error);
}
