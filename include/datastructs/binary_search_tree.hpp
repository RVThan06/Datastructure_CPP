#ifndef BINARY_S_TREE_HPP
#define BINARY_S_TREE_HPP

#include <iostream>
#include <memory>
#include <optional>
#include <stack>
#include <stdexcept>

namespace datastructs {

/**
 * @brief Node_bst struct that forms each node in binary search tree.
 * m_value -> stores data.
 * m_leftptr -> stores pointer to left node.
 * m_rightptr -> stores pointer to right node.
 */
template <typename T>
struct Node_bst {
    T m_value{};
    std::unique_ptr<Node_bst<T>> m_leftptr{nullptr};
    std::unique_ptr<Node_bst<T>> m_rightptr{nullptr};
};

/**
 * @brief A template class forbinary search tree data structure.
 * @note This class has forward iterators implementation for integration into
 * STL algorithms.
 * @tparam T is the type of the data stored by the underlying datastructure.
 */
template <typename T>
class BinarySearchTree {
public:
    /// @brief Default consrtuctor -> initialises an empty binary tree
    BinarySearchTree() : m_root{nullptr} {}

    /// @brief Constructor to initialise tree using value for the first node
    explicit BinarySearchTree(T value) : m_root{std::make_unique<Node_bst<T>>(value)} {}

    /// @brief Destructor
    ~BinarySearchTree() {}

    /// @brief No copy semantics since its very expensive to copy
    BinarySearchTree(const BinarySearchTree& other_tree) = delete;
    BinarySearchTree& operator=(BinarySearchTree& other_tree) = delete;

    /// @brief Move semantics
    BinarySearchTree(BinarySearchTree&& other_tree) noexcept : m_root{std::move(other_tree.m_root)} {}
    BinarySearchTree& operator=(BinarySearchTree&& other_tree) noexcept;

    /// @brief Binary Search Tree operations
    void insert_node(T value) { insert(value, m_root); }
    std::optional<T> search_node(T value) const { return search(value, m_root); }
    void delete_node(T value) { deletion(value, m_root); }
    const Node_bst<T>& find_minimum();
    const Node_bst<T>& find_maximum();

    /**
     * @brief ostream overload to print linked list
     * @param out, the ostream object -> std::cout
     * @param tree, binary search tree object to be printed
     * @returns ostream object by reference
     */
    friend std::ostream& operator<<(std::ostream& out, const BinarySearchTree& tree) {
        tree.in_order(tree.m_root, out);
        return out;
    }

    /**
     * @brief iterator class for binary search tree
     * This is a forward iterator class.
     */
    template <typename U>
    class Iterator {
    public:
        using value_type = std::remove_const_t<U>;
        using pointer = U*;
        using reference = U&;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::forward_iterator_tag;

        Iterator(Node_bst<std::remove_const_t<U>>* node) : tree_stack{} { push_left(node); }

        // Dereferencing
        reference operator*() const { return tree_stack.top()->m_value; }
        pointer operator->() const { return *(tree_stack.top()->m_value); }

        // Pre-Increment
        Iterator& operator++() {
            Node_bst<std::remove_const_t<U>>* node = tree_stack.top();
            tree_stack.pop();
            if (node->m_rightptr) {
                push_left(node->m_rightptr.get());
            }
            return *this;
        }

        bool operator!=(const Iterator& other_iterator) { return tree_stack != other_iterator.tree_stack; }
        bool operator==(const Iterator& other_iterator) { return tree_stack == other_iterator.tree_stack; }

    private:
        std::stack<Node_bst<std::remove_const_t<U>>*> tree_stack;

        void push_left(Node_bst<std::remove_const_t<U>>* node) {
            while (node) {
                tree_stack.push(node);
                node = node->m_leftptr.get();
            }
            return;
        }
    };

    /// @brief Iterator alias
    using iterator = Iterator<T>;
    using const_iterator = Iterator<const T>;

    iterator begin() { return iterator(m_root.get()); }
    iterator end() { return iterator(nullptr); }

    const_iterator begin() const { return const_iterator(m_root.get()); }
    const_iterator end() const { return const_iterator(nullptr); }

    const_iterator cbegin() const { return const_iterator(m_root.get()); }
    const_iterator cend() const { return const_iterator(nullptr); }

protected:
    /// @brief Tree operations for internal class usage not available to public user
    void insert(T value, std::unique_ptr<Node_bst<T>>&);
    void in_order(const std::unique_ptr<Node_bst<T>>&, std::ostream&) const;
    std::optional<T> search(T value, const std::unique_ptr<Node_bst<T>>&) const;
    void deletion(T value, std::unique_ptr<Node_bst<T>>&);
    std::unique_ptr<Node_bst<T>>& find_min(std::unique_ptr<Node_bst<T>>&); // used internally in deletion()

private:
    std::unique_ptr<Node_bst<T>> m_root;
};

/**
 * @brief Move assignment.
 * * Moves resources from another tree object, leaves the moved object in valid state.
 * @param other_tree list object to move resource from.
 */
template <typename T>
BinarySearchTree<T>& BinarySearchTree<T>::operator=(BinarySearchTree&& other_tree) noexcept {
    // self assignment check
    if (*this == &other_tree) {
        return *this;
    }

    m_root = std::move_if_noexcept(other_tree.m_root);
    return *this;
}

/**
 * @brief A function to find the node with the minimum value
 * @return A const reference to the minimum node.
 */
template <typename T>
const Node_bst<T>& BinarySearchTree<T>::find_minimum() {
    Node_bst<T>* temp_node = m_root.get();

    while (temp_node) {
        if (temp_node->m_leftptr) {
            temp_node = temp_node->m_leftptr.get();
            continue;
        }
        break;
    }
    return *temp_node;
}

/**
 * @brief A function to find the node with the maximum value
 * @return A const reference to the maximum node.
 */
template <typename T>
const Node_bst<T>& BinarySearchTree<T>::find_maximum() {
    Node_bst<T>* temp_node = m_root.get();

    while (temp_node) {
        if (temp_node->m_rightptr) {
            temp_node = temp_node->m_rightptr.get();
            continue;
        }
        break;
    }
    return *temp_node;
}

/**
 * @brief Function to insert node into tree
 * If new node <= current node -> insert in left subtree, else insert in right subtree
 * This logic ensures that for any given head node, all nodes
 * on left subtree are smaller and all nodes on right subtree are larger.
 * @note This is an internal class function used in insert_node(), not accessible by public.
 * @note Complexity: O(logn)
 */
template <typename T>
void BinarySearchTree<T>::insert(T value, std::unique_ptr<Node_bst<T>>& node) {
    if (!node) {
        node.reset(new Node_bst<T>{value});
        return;
    }

    if (value <= node->m_value) {
        insert(value, node->m_leftptr);
        return;
    }

    else {
        insert(value, node->m_rightptr);
        return;
    }
}

/**
 * @brief Function to perform in order traversal.
 * @note This function is an internal class function used for printing, not accessible by public.
 * @note Complexity: O(n)
 */
template <typename T>
void BinarySearchTree<T>::in_order(const std::unique_ptr<Node_bst<T>>& node, std::ostream& out) const {
    if (node->m_leftptr) {
        in_order(node->m_leftptr, out);
    }

    out << node->m_value << " --> ";

    if (node->m_rightptr) {
        in_order(node->m_rightptr, out);
    }
    return;
}

/**
 * @brief Function to search for a given node.
 * In each iteration the nodes to search gets halved, thus much faster at searching.
 * @note This function is an internal class function used in search_node(), not accessible by public.
 * @note Complexity: O(logn)
 */
template <typename T>
std::optional<T> BinarySearchTree<T>::search(T value, const std::unique_ptr<Node_bst<T>>& node) const {
    if (!node) {
        throw(std::runtime_error("Node not found"));
    }

    if (value == node->m_value) {
        return node->m_value;
    }

    if (value < node->m_value) {
        search(value, node->m_leftptr);
    } else if (value > node->m_value) {
        search(value, node->m_rightptr);
    }
}

/**
 * @brief Function to perform deleteion if a given node.
 * @note This function is an internal class function used for printing, not accessible by public.
 * @note Complexity: O(n)
 * @throws std::runtime_error is the node to be delete is not present in tree.
 */
template <typename T>
void BinarySearchTree<T>::deletion(T value, std::unique_ptr<Node_bst<T>>& node) {
    if (!node) {
        throw(std::runtime_error("Node to be deleted not found"));
    }

    if (value < node->m_value) {
        deletion(value, node->m_leftptr);
    }

    else if (value > node->m_value) {
        deletion(value, node->m_rightptr);
    }

    else if (value == node->m_value) {
        // leaf node
        if (node->m_rightptr == nullptr && node->m_leftptr == nullptr) {
            node.reset();
        }

        // only right child
        else if (node->m_rightptr != nullptr && node->m_leftptr == nullptr) {
            node = std::move(node->m_rightptr);
        }

        // only left child
        else if (node->m_leftptr != nullptr && node->m_rightptr == nullptr) {
            node = std::move(node->m_leftptr);
        }

        // both children
        else {
            // get the smallest node in right subtree
            std::unique_ptr<Node_bst<T>>& del_node = find_min(node->m_rightptr);
            // copy the value to current node / overwrite current node
            node->m_value = del_node->m_value;
            // delete duplicate node
            deletion(del_node->m_value, node->m_rightptr);
        }
    }
}

/// @brief Internal fucntion used to find the minimum node by traversing the lest subtree till end
template <typename T>
std::unique_ptr<Node_bst<T>>& BinarySearchTree<T>::find_min(std::unique_ptr<Node_bst<T>>& node) {
    if (node->m_leftptr) {
        find_min(node->m_leftptr);
    } else {
        return node;
    }
}

} // namespace datastructs

#endif
