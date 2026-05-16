#include <gtest/gtest.h>

#include <algorithm>
#include <array>
#include <cstddef>
#include <datastructs/singly_linked_list.hpp>

TEST(SinglyListTest, DefaultConstruction) {
    std::array primes{2, 3, 5, 7, 11};
    datastructs::LinkedList<int> prime_numbers;

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

TEST(SinglyListTest, ParamConstruction) {
    // Construction via parameterizewd constructor
    std::array evens{4, 6, 8, 10, 12};
    datastructs::LinkedList<int> even_numbers(2);

    // 1. validate size
    ASSERT_FALSE(even_numbers.is_empty());
    ASSERT_EQ(even_numbers.length(), 1);

    // 2. Use insert back
    for (std::size_t i = 0; i < 5; ++i) {
        even_numbers.insert_back(evens[i]);
    }

    ASSERT_FALSE(even_numbers.is_empty());
    ASSERT_EQ(even_numbers.length(), 6);

    // 3. test delete back
}

TEST(SinglyListTest, ListConstruction) {
    // test to check intialisation via intialiser list
    datastructs::LinkedList<int> even_numbers{2, 4, 6, 8, 10, 12};
    ASSERT_FALSE(even_numbers.is_empty());
    ASSERT_EQ(even_numbers.length(), 6);
}

TEST(SinglyListTest, CopyConstruction) {
    datastructs::LinkedList<int> even_numbers{2, 4, 6, 8, 10, 12};
    datastructs::LinkedList<int> even_numbers_2 = even_numbers;

    // 1. Verify copying was done to second list
    ASSERT_FALSE(even_numbers_2.is_empty());
    ASSERT_EQ(even_numbers_2.length(), 6);

    // 2. Verify first list still has data after copying
    ASSERT_FALSE(even_numbers.is_empty());
    ASSERT_EQ(even_numbers.length(), 6);
}

TEST(SinglyListTest, MoveConstruction) {
    datastructs::LinkedList<int> even_numbers{2, 4, 6, 8, 10, 12};
    datastructs::LinkedList<int> even_numbers_2 = std::move(even_numbers);

    // 1. Verify moving was done to second list
    ASSERT_FALSE(even_numbers_2.is_empty());
    ASSERT_EQ(even_numbers_2.length(), 6);

    // 2. Verify first list is empty after moving
    ASSERT_TRUE(even_numbers.is_empty());
    ASSERT_EQ(even_numbers.length(), 0);
}

TEST(SinglyListTest, CustomIterator) {
    datastructs::LinkedList<int> even_numbers{2, 4, 6, 8, 10, 12};

    // 1. for-each loop
    int sum = 0;
    for (const auto& val : even_numbers) {
        sum += val;
    }
    ASSERT_EQ(sum, 42);

    // 2. iterator object
    auto it = even_numbers.begin();
    ASSERT_EQ(*it, 2);
}

TEST(SinglyListTest, STLCopy) {
    // Test std::copy
    datastructs::LinkedList<int> even_numbers{2, 4, 6, 8, 10, 12};
    datastructs::LinkedList<int> even_numbers_2{20, 22, 24, 26, 28, 30};

    std::copy(even_numbers_2.begin(), even_numbers_2.end(), even_numbers.begin());

    // validate list 2 size remains the same after copying
    EXPECT_EQ(even_numbers_2.length(), 6);

    int sum = 0;
    for (const auto& val : even_numbers) {
        sum += val;
    }
    ASSERT_EQ(sum, 150);
}

TEST(SinglyListTest, STLForEach) {
    // Test std::for_each
    datastructs::LinkedList<int> even_numbers{2, 4, 6, 8, 10, 12};

    auto multiply_2 = [](int& x) { x = x * 2; };
    std::for_each(even_numbers.begin(), even_numbers.end(), multiply_2);

    int sum = 0;
    for (const auto& val : even_numbers) {
        sum += val;
    }
    ASSERT_EQ(sum, 84);
}
