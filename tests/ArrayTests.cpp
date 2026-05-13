#include <gtest/gtest.h>

#include <cstddef>
#include <datastructs/Array.hpp>
#include <iterator>

TEST(ArrayTest, DefaultConstruction) {
    datastructs::MyArray<std::size_t, 5> arr1;
    for (std::size_t i = 0; i < 5; ++i) {
        EXPECT_EQ(arr1[i], 0);
    }
}

TEST(ArrayTest, ListConstruction) {
    // 1. testing intializer list of the same size
    datastructs::MyArray<std::size_t, 5> arr2{1, 2, 3, 4, 5};

    for (std::size_t i = 0; i < 5; ++i) {
        EXPECT_EQ(arr2[i], i + 1);
    }

    // 2. testing initialiser list of a smaller size
    datastructs::MyArray<int, 5> arr3{1, 2, 3};

    for (std::size_t i = 0; i < 3; ++i) {
        EXPECT_EQ(arr3[i], i + 1);
    }

    // others should be default initialised
    for (std::size_t i = 3; i < 5; ++i) {
        EXPECT_EQ(arr3[i], 0);
    }

    // 3. Test when the initializer list is larger, throws exception
    auto contruct_larger = []() { datastructs::MyArray<int, 2> arr4{1, 2, 3}; };
    EXPECT_THROW(contruct_larger(), std::out_of_range);
}

TEST(ArrayTest, CopySemantics) {
    // 1. Copy construction test
    datastructs::MyArray<std::size_t, 5> arr1{1, 2, 3, 4, 5};
    datastructs::MyArray<std::size_t, 5> arr2 = arr1;

    for (std::size_t i = 0; i < 5; ++i) {
        EXPECT_EQ(arr2[i], i + 1);
    }

    // 2. Copy assignment test
    datastructs::MyArray<std::size_t, 5> arr3{2, 2, 2, 2, 2};
    arr1 = arr3;

    for (std::size_t i = 0; i < 5; ++i) {
        EXPECT_EQ(arr1[i], 2);
    }
}

TEST(ArrayTest, CustomIterators) {
    datastructs::MyArray<std::size_t, 5> arr1{2, 2, 2, 2, 2};

    // 1. for-each loop - must have valid begin() & end()
    for (const auto& val : arr1) {
        EXPECT_EQ(val, 2);
    }

    // 2. iterator airthmetic (Contiguous iterator)
    arr1 = {1, 2, 3, 4, 5};

    // begin() iterator check
    auto it_1 = arr1.begin();
    ASSERT_EQ(*it_1, 1); // index 0

    // iterator increment
    ++it_1;
    ASSERT_EQ(*it_1, 2);

    // end() iterator check
    auto it_2 = arr1.end();
    ASSERT_EQ(*(it_2 - 1), 5); // index 4

    it_2 -= 3;
    ASSERT_EQ(*it_2, 3); // index 2
}

TEST(ArrayTest, STLCopy) {
    // Test std::copy
    datastructs::MyArray<std::size_t, 5> arr1{1, 2, 3, 4, 5};
    datastructs::MyArray<std::size_t, 5> arr2;

    std::copy(arr1.begin(), arr1.end(), arr2.begin());

    for (std::size_t i = 0; i < 5; ++i) {
        ASSERT_EQ(arr2[i], i + 1);
    }
}

TEST(ArrayTest, STLForEach) {
    // Test std::for_each
    datastructs::MyArray<std::size_t, 5> arr1{0, 1, 2, 3, 4};

    auto multiply_2 = [](std::size_t& x) { x = x * 2; };
    std::for_each(arr1.begin(), arr1.end(), multiply_2);

    for (std::size_t i = 0; i < 5; ++i) {
        ASSERT_EQ(arr1[i], i * 2);
    }
}
