#include <algorithm>
#include <array>
#include <cstddef>
#include <datastructs/binary_search_tree.hpp>
#include <iostream>

template <typename T, std::size_t N>
void intialise_tree(datastructs::BinarySearchTree<T>& tree, std::array<T, N>& nodes) {
    for (const auto& val : nodes) {
        tree.insert_node(val);
    }
}

int main() {
    /****************************************************************************************************
     * DOUBLY LINKED LIST DEMO                                                                         **
     * **************************************************************************************************
     */

    // --- Tree Initialisation --------------------------------------------------------------------------

    std::array nodes{5, 10, 20, 8, 12, 17, 25};
    datastructs::BinarySearchTree<int> tree_1;
    intialise_tree<int, 7>(tree_1, nodes);
    std::cout << tree_1 << "\n\n";

    // --- Tree Operations ------------------------------------------------------------------------------

    // 1. search_node()

    // auto result = tree_1.search_node(10);
    // if (result) {
    //     std::cout << "Node " << result.value() << " found \n";
    // }

    // result = tree_1.search_node(25);
    // if (result) {
    //     std::cout << "Node " << result.value() << " found \n";
    // }

    // 2. delete_node()
    tree_1.delete_node(17);
    std::cout << tree_1 << "\n\n";

    // 3. find_minimum()
    const datastructs::Node_bst<int>& min_node = tree_1.find_minimum();
    std::cout << min_node.m_value << "\n";

    // 4. find_maximum()
    const datastructs::Node_bst<int>& max_node = tree_1.find_maximum();
    std::cout << max_node.m_value << "\n\n";

    // --- Custom Iterators Usage -----------------------------------------------------------------------

    // 1. For-each loop
    for (const auto& node : tree_1) {
        std::cout << node << " -> ";
    }
    std::cout << "\n\n";

    // 2. const iterator
    datastructs::BinarySearchTree<int> tree_sample;
    intialise_tree<int, 7>(tree_sample, nodes);

    const datastructs::BinarySearchTree constant_tree = std::move(tree_sample);

    std::cout << " Const iterator: ";
    for (const auto& node : constant_tree) {
        std::cout << node << " -> ";
    }
    std::cout << "\n\n";

    // ---Binary Search Tree + STL algorithms (via custom iterators) ------------------------------------------

    datastructs::BinarySearchTree<int> tree_2;
    std::array nodes_2{5, 7, 60, 3, 65, 13, 12};
    intialise_tree<int, 7>(tree_2, nodes_2);
    std::cout << "Tree 2: " << tree_2 << "\n";

    datastructs::BinarySearchTree<int> tree_3;
    std::array nodes_3{8, 28, 18, 72, 5, 23, 11};
    intialise_tree<int, 7>(tree_3, nodes_3);
    std::cout << "Tree 3: " << tree_3 << "\n";

    datastructs::BinarySearchTree<int> tree_4;
    std::array nodes_4{12, 14, 18, 32, 5, 17, 19};
    intialise_tree<int, 7>(tree_4, nodes_4);
    std::cout << "Tree 4: " << tree_4 << "\n\n";

    // 1. std::copy
    std::copy(tree_2.begin(), tree_2.end(), tree_3.begin());
    std::cout << "Tree 2: " << tree_2 << "\n";
    std::cout << "Tree 3: " << tree_3 << "\n\n";

    // 2. std::copy_if
    auto is_even = [](int x) { return x % 2 == 0; };
    std::copy_if(tree_4.begin(), tree_4.end(), tree_3.begin(), is_even);
    std::cout << "Tree 3: " << tree_3 << "\n";
    std::cout << "Tree 4: " << tree_4 << "\n\n";

    // 3. std::fill
    std::fill(tree_1.begin(), tree_1.end(), -10);
    std::cout << "Tree 1: " << tree_1 << "\n\n";

    // 4. std::for_each
    auto multiply_2 = [](int& x) { x = x * 2; };
    std::for_each(tree_2.begin(), tree_2.end(), multiply_2);
    std::cout << "Tree 2: " << tree_2 << "\n\n";

    // 5. std::find
    auto it_2 = std::find(tree_2.begin(), tree_2.end(), 120);
    if (it_2 != tree_2.end()) {
        std::cout << "Value: " << *it_2 << " found in Tree 2\n\n";
    } else {
        std::cout << "Value not found\n";
    }

    return 0;
}
