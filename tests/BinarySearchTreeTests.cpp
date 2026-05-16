#include <gtest/gtest.h>

#include <algorithm>
#include <array>
#include <cstddef>
#include <datastructs/binary_search_tree.hpp>
#include <vector>

TEST(BinarySearchTreeTest, DefaultConstruction) {
    std::array nodes{5, 10, 20, 8, 12, 17, 25};
    datastructs::BinarySearchTree<int> tree;

    for (const auto& val : nodes) {
        tree.insert_node(val);
    }

    // 2. delete_node()
    tree.delete_node(5);

    // 3. find_minimum()
    const datastructs::Node_bst<int>& min_node = tree.find_minimum();
    ASSERT_EQ(min_node.m_value, 8);

    // 4. find_maximum()
    const datastructs::Node_bst<int>& max_node = tree.find_maximum();
    ASSERT_EQ(max_node.m_value, 25);
}

TEST(BinarySearchTreeTest, CustomIterators) {
    std::array nodes{5, 10, 20, 8, 12, 17, 25};
    datastructs::BinarySearchTree<int> tree;

    for (const auto& val : nodes) {
        tree.insert_node(val);
    }

    std::vector<int> expected_values{5, 8, 10, 12, 17, 20, 25};
    std::vector<int> actual_values;

    for (const auto& node : tree) {
        actual_values.push_back(node);
    }

    ASSERT_EQ(expected_values.size(), actual_values.size());
    for (std::size_t i = 0; i < expected_values.size(); ++i) {
        ASSERT_EQ(expected_values[i], actual_values[i]);
    }
}

TEST(BinarySearchTreeTest, STLAlgorithms) {
    std::array nodes{5, 10, 20, 8, 12, 17, 25};
    datastructs::BinarySearchTree<int> tree;

    for (const auto& val : nodes) {
        tree.insert_node(val);
    }

    // 1. std::copy
    std::vector<int> copied_values(tree.begin(), tree.end());
    std::vector<int> expected_values{5, 8, 10, 12, 17, 20, 25};
    ASSERT_EQ(copied_values.size(), expected_values.size());
    for (std::size_t i = 0; i < expected_values.size(); ++i) {
        ASSERT_EQ(expected_values[i], copied_values[i]);
    }

    // 2. std::find
    auto it = std::find(tree.begin(), tree.end(), 12);
    ASSERT_NE(it, tree.end());
    ASSERT_EQ(*it, 12);

    // 30 not in tree
    it = std::find(tree.begin(), tree.end(), 30);
    ASSERT_EQ(it, tree.end());
}
