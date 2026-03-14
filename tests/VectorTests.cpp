#include <gtest/gtest.h>

#include <datastructs/vector.hpp>
#include <iterator>

TEST(VectorTest, Construction) {
    datastructs::Myvector<int> vector1;

    // 1. default initialisation expect empty vector
    EXPECT_EQ(vector1.get_size(), 0);

    // 2. to validate vector capacity is independant of size
    EXPECT_GT(vector1.get_capacity(), 0);

    // 3. Validate push_back upon construction
    for (int i = 0; i < 5; ++i) {
        vector1.push_back(i);
    }

    EXPECT_EQ(vector1.get_size(), 5);
    EXPECT_EQ(vector1[3], 3);
}

TEST(VectorTest, ListConstructor) {
    datastructs::Myvector<int> vector1{1, 2, 3, 4, 5};

    EXPECT_EQ(vector1.get_size(), 5);
    EXPECT_EQ(vector1[3], 4);
}

TEST(VectorTest, CopySemantics) {
    // 1. Copy construction test - deep copying
    datastructs::Myvector<int> vector1{0, 1, 2, 3, 4};
    datastructs::Myvector<int> vector2 = vector1;

    EXPECT_EQ(vector2.get_size(), 5);

    for (std::size_t i = 0; i < vector2.get_size(); ++i) {
        ASSERT_EQ(vector2[i], i);
    }

    // 2. Copy assignment test - deep copying
    datastructs::Myvector<int> vector3{1, 1, 1, 1, 1};
    vector2 = vector3;

    EXPECT_EQ(vector2.get_size(), 5);

    for (std::size_t i = 0; i < vector2.get_size(); ++i) {
        ASSERT_EQ(vector2[i], 1);
    }
}

TEST(VectorTest, MoveSemantics) {
    // 1. Move construction
    datastructs::Myvector<int> vector1{0, 1, 2, 3, 4};
    datastructs::Myvector<int> vector2 = std::move_if_noexcept(vector1);

    // Valdiate vector size has changeed upon moving
    EXPECT_EQ(vector1.get_size(), 0);
    EXPECT_EQ(vector2.get_size(), 5);

    for (std::size_t i = 0; i < vector2.get_size(); ++i) {
        ASSERT_EQ(vector2[i], i);
    }

    // 2. Move assignment
    vector1 = std::move_if_noexcept(vector2);

    // Valdiate vector size has changeed upon moving
    EXPECT_EQ(vector1.get_size(), 5);
    EXPECT_EQ(vector2.get_size(), 0);

    for (std::size_t i = 0; i < vector1.get_size(); ++i) {
        ASSERT_EQ(vector1[i], i);
    }
}

TEST(VectorTest, CustomIterator) {
    datastructs::Myvector<int> vector1{0, 1, 2, 3, 4};

    // 1. for-each loop - must have valid begin() & end()
    int sum = 0;
    for (const auto& val : vector1) {
        sum += val;
    }

    ASSERT_EQ(sum, 10);

    // 2. iterator airthmetic (Contiguous iterator)

    // begin() iterator check
    auto it_1 = vector1.begin();
    ASSERT_EQ(*it_1, 0); // index 0

    // iterator increment
    ++it_1;
    ASSERT_EQ(*it_1, 1);

    // end() iterator check
    auto it_2 = vector1.end();
    ASSERT_EQ(*(it_2 - 1), 4); // index 4

    it_2 -= 3;
    ASSERT_EQ(*it_2, 2); // index 3
}

TEST(Vectortest, STLCopy) {
    // Test std::copy
    datastructs::Myvector<int> vector_1{1, 2, 3, 4, 5};
    datastructs::Myvector<int> vector_2;

    std::copy(vector_1.begin(), vector_1.end(), std::back_inserter(vector_2));

    // validate vector 2 size increment upon copying
    EXPECT_EQ(vector_2.get_size(), 5);

    for (std::size_t i = 0; i < 5; ++i) {
        ASSERT_EQ(vector_2[i], i + 1);
    }
}

TEST(VectorTest, STLForEach) {
    // Test std::for_each
    datastructs::Myvector<int> vector_1{0, 1, 2, 3, 4};

    auto multiply_2 = [](int& x) { x = x * 2; };
    std::for_each(vector_1.begin(), vector_1.end(), multiply_2);

    for (std::size_t i = 0; i < 5; ++i) {
        ASSERT_EQ(vector_1[i], i * 2);
    }
}
