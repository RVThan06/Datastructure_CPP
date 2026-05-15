#include <gtest/gtest.h>

#include <datastructs/heap.hpp>

TEST(HeapTest, Construction) {
    int arr[6] = {10, 20, 15, 30, 40, 30};
    datastructs::MaxHeap<int> heap_1;
    for (int i = 0; i < 6; ++i) {
        heap_1.insert_node(arr[i]);
    }

    // check size
    ASSERT_EQ(heap_1.size(), 6);

    // validate heap behaviour preserved after deletion
    ASSERT_EQ(heap_1.delete_node(), 40);
    ASSERT_EQ(heap_1.delete_node(), 30);
    ASSERT_EQ(heap_1.delete_node(), 30);
    ASSERT_EQ(heap_1.delete_node(), 20);
    ASSERT_EQ(heap_1.delete_node(), 15);
    ASSERT_EQ(heap_1.delete_node(), 10);
}

TEST(HeapTest, CopySemantics) {
    int arr[6] = {10, 20, 15, 30, 40, 30};
    datastructs::MaxHeap<int> heap_1;
    for (int i = 0; i < 6; ++i) {
        heap_1.insert_node(arr[i]);
    }

    datastructs::MaxHeap<int> heap_2 = heap_1;

    // check size
    ASSERT_EQ(heap_2.size(), 6);

    // validate heap behaviour preserved after deletion
    ASSERT_EQ(heap_2.delete_node(), 40);
    ASSERT_EQ(heap_2.delete_node(), 30);
    ASSERT_EQ(heap_2.delete_node(), 30);
    ASSERT_EQ(heap_2.delete_node(), 20);
    ASSERT_EQ(heap_2.delete_node(), 15);
    ASSERT_EQ(heap_2.delete_node(), 10);
}

TEST(HeapTest, MoveSemantics) {
    int arr[6] = {10, 20, 15, 30, 40, 30};
    datastructs::MaxHeap<int> heap_1;
    for (int i = 0; i < 6; ++i) {
        heap_1.insert_node(arr[i]);
    }

    datastructs::MaxHeap<int> heap_2 = std::move(heap_1);

    // check size
    ASSERT_EQ(heap_1.size(), 0);
    ASSERT_EQ(heap_2.size(), 6);

    // validate heap behaviour preserved after deletion
    ASSERT_EQ(heap_2.delete_node(), 40);
    ASSERT_EQ(heap_2.delete_node(), 30);
    ASSERT_EQ(heap_2.delete_node(), 30);
    ASSERT_EQ(heap_2.delete_node(), 20);
    ASSERT_EQ(heap_2.delete_node(), 15);
    ASSERT_EQ(heap_2.delete_node(), 10);
}
