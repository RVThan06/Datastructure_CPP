#include <gtest/gtest.h>

#include <algorithm>
#include <array>
#include <cstddef>
#include <datastructs/doubly_linked_list.hpp>

TEST(DoublyListTest, DefaultConstruction) {
    std::array primes{2, 3, 5, 7, 11};
    datastructs::DLinkedList<int> prime_numbers;

    // 1. default constructor -> empty list
    ASSERT_TRUE(prime_numbers.is_empty());
    ASSERT_EQ(prime_numbers.length(), 0);

    // 2. insert front test
    for (std::size_t i = 0; i < 5; ++i) {
        prime_numbers.insert_front(primes[i]);
    }

    ASSERT_FALSE(prime_numbers.is_empty());
    ASSERT_EQ(prime_numbers.length(), 5);

    // 3. Check delete front works
    prime_numbers.delete_front();
    ASSERT_EQ(prime_numbers.length(), 4);
}

TEST(DoublyListTest, ParamConstruction) {
    // Construction via parameterizewd constructor
    std::array evens{4, 6, 8, 10, 12};
    datastructs::DLinkedList<int> even_numbers(2);

    // 1. validate size
    ASSERT_FALSE(even_numbers.is_empty());
    ASSERT_EQ(even_numbers.length(), 1);

    // 2. Use insert back
    for (std::size_t i = 0; i < 5; ++i) {
        even_numbers.insert_rear(evens[i]);
    }

    ASSERT_FALSE(even_numbers.is_empty());
    ASSERT_EQ(even_numbers.length(), 6);

    // 3. test delete back
    even_numbers.delete_rear();
    ASSERT_EQ(even_numbers.length(), 5);
}

TEST(DoublyListTest, ListConstruction) {
    // test to check intialisation via intialiser list
    datastructs::DLinkedList<int> even_numbers{2, 4, 6, 8, 10, 12};
    ASSERT_FALSE(even_numbers.is_empty());
    ASSERT_EQ(even_numbers.length(), 6);
}

TEST(DoublyListTest, CopyConstruction) {
    datastructs::DLinkedList<int> even_numbers{2, 4, 6, 8, 10, 12};
    datastructs::DLinkedList<int> even_numbers_2 = even_numbers;

    // 1. Verify copying was done to second list
    ASSERT_FALSE(even_numbers_2.is_empty());
    ASSERT_EQ(even_numbers_2.length(), 6);

    // 2. Verify first list still has data after copying
    ASSERT_FALSE(even_numbers.is_empty());
    ASSERT_EQ(even_numbers.length(), 6);
}

TEST(DoublyListTest, MoveConstruction) {
    datastructs::DLinkedList<int> even_numbers{2, 4, 6, 8, 10, 12};
    datastructs::DLinkedList<int> even_numbers_2 = std::move(even_numbers);

    // 1. Verify moving was done to second list
    ASSERT_FALSE(even_numbers_2.is_empty());
    ASSERT_EQ(even_numbers_2.length(), 6);

    // 2. Verify first list is empty after moving
    ASSERT_TRUE(even_numbers.is_empty());
    ASSERT_EQ(even_numbers.length(), 0);
}

TEST(DoublyListTest, CustomIterator) {
    datastructs::DLinkedList<int> even_numbers{2, 4, 6, 8, 10, 12};

    // 1. for-each loop - forward iteration
    int sum = 0;
    for (const auto& val : even_numbers) {
        sum += val;
    }
    ASSERT_EQ(sum, 42);

    // 2. reverse iteration
    sum = 0;
    for (auto pos = even_numbers.rbegin(); pos != even_numbers.rend(); ++pos) {
        sum += (*pos);
    }
    ASSERT_EQ(sum, 42);
}

TEST(DoublyListTest, STLCopy) {
    // Test std::copy
    datastructs::DLinkedList<int> even_numbers{2, 4, 6, 8, 10, 12};
    datastructs::DLinkedList<int> even_numbers_2{20, 22, 24, 26, 28, 30};

    std::copy(even_numbers_2.begin(), even_numbers_2.end(), even_numbers.begin());

    // validate list 2 size remains the same after copying
    EXPECT_EQ(even_numbers_2.length(), 6);

    int sum = 0;
    for (const auto& val : even_numbers) {
        sum += val;
    }
    ASSERT_EQ(sum, 150);
}

TEST(DoublyListTest, STLForEach) {
    // Test std::for_each
    datastructs::DLinkedList<int> even_numbers{2, 4, 6, 8, 10, 12};

    auto multiply_2 = [](int& x) { x = x * 2; };
    std::for_each(even_numbers.begin(), even_numbers.end(), multiply_2);

    int sum = 0;
    for (const auto& val : even_numbers) {
        sum += val;
    }
    ASSERT_EQ(sum, 84);
}
