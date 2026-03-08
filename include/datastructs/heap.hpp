#ifndef HEAP_HPP
#define HEAP_HPP

#include <cmath>
#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <stdexcept>
#include <vector>

namespace datastructs {

/**
 * @brief A template class for Max heap data structure.
 * The root node for any given subtree is larger than or equal to the child nodes.
 * @tparam T is the type of the data stored by the underlying datastructure.
 */
template <typename T>
class MaxHeap {
public:
    /// @brief constructors and assignment
    MaxHeap();
    explicit MaxHeap(T);
    MaxHeap(const MaxHeap&);
    MaxHeap(MaxHeap&&) noexcept;
    MaxHeap(std::initializer_list<T>);
    MaxHeap& operator=(const MaxHeap&);
    MaxHeap& operator=(MaxHeap&& other_heap) noexcept;

    /// @brief heap operations
    void insert_node(T);
    T delete_node();
    bool is_empty() { return max_heap.empty(); }
    std::size_t size() { return max_heap.size(); }

    /// @brief ostream overload for printing
    friend std::ostream& operator<<(std::ostream& out, const MaxHeap& heap) {
        for (const auto& val : heap.max_heap) {
            out << val << " -> ";
        }
        return out;
    }

private:
    std::vector<T> max_heap;
};

/// @brief Default constructor to initialise empty heap.
template <typename T>
MaxHeap<T>::MaxHeap() : max_heap{} {}

/**
 * @brief Constructor with arguement to initialise heap.
 * @param val, the value for first node in heap.
 */
template <typename T>
MaxHeap<T>::MaxHeap(T val) : max_heap{val} {}

/**
 * @brief Copy constructor.
 * Deep copying is done.
 * @param other_heap, heap object to copy from.
 */
template <typename T>
MaxHeap<T>::MaxHeap(const MaxHeap& other_heap) : max_heap{other_heap.max_heap} {}

/**
 * @brief Move constructor.
 * * Moves resources from another heap object, leaves the moved object in valid state.
 * @param other_heap heap object to move resource from.
 */
template <typename T>
MaxHeap<T>::MaxHeap(MaxHeap&& other_heap) noexcept : max_heap{std::move(other_heap.max_heap)} {}

/**
 * @brief List constructor.
 * * Initialises a heap using initilizer list by copying all the values in it
 * to create a node for each value and form a heap eventually.
 * @param llist, std::initializer list object.
 */
template <typename T>
MaxHeap<T>::MaxHeap(std::initializer_list<T> llist) : MaxHeap() {
    std::copy(llist.begin(), llist.end(), std::back_inserter(max_heap));
}

/**
 * @brief Copy assignment.
 * Deep copying is done.
 * @param other_heap heap object to copy from.
 */
template <typename T>
MaxHeap<T>& MaxHeap<T>::operator=(const MaxHeap<T>& other_heap) {
    // self assignment check
    if (*this == &other_heap) {
        return *this;
    }

    // copy from other heap - since vector, existing memory is auto deallocated
    max_heap = other_heap.max_heap;

    // to chain assignment
    return *this;
}

/**
 * @brief Move assignment.
 * * Moves resources from another heap object, leaves the moved object in valid state.
 * @param other_heap heap object to move resource from.
 */
template <typename T>
MaxHeap<T>& MaxHeap<T>::operator=(MaxHeap<T>&& other_heap) noexcept {
    // self assignment check
    if (*this == &other_heap) {
        return *this;
    }

    // move the underlying vector
    max_heap = std::move(other_heap.max_heap);

    // to chain assignments
    return *this;
}

/**
 * @brief Function to insert a new node into heap.
 * Ensure after each insertion the max heap property is preserved.
 * @note Complexity: O(logn)
 */
template <typename T>
void MaxHeap<T>::insert_node(T val) {
    // 1. Add node to last element
    max_heap.push_back(val);

    // 2. Get index of added element and its parent
    double index = static_cast<double>(max_heap.size()) - 1.0;
    double parent = std::ceil(index / 2) - 1;

    // 3. Check if the new node is larger than parent
    while (parent >= 0) {
        // If node > parent then swap repeat till this is false --> max swap till root node
        if (max_heap[static_cast<std::size_t>(index)] >= max_heap[static_cast<std::size_t>(parent)]) {
            T temp = max_heap[static_cast<std::size_t>(parent)];
            max_heap[static_cast<std::size_t>(parent)] = val;
            max_heap[static_cast<std::size_t>(index)] = temp;

            // move up the heap
            index = parent;
            parent = std::ceil(parent / 2) - 1;
        } else {
            break;
        }
    }
}

/**
 * @brief Function to delete a given node.
 * Ensure after each deletion the max heap property is preserved.
 * @note Complexity: O(logn)
 * @throws std::length_error when attempting to delete from an empty heap.
 */
template <typename T>
T MaxHeap<T>::delete_node() {
    // Exception when empty heap
    if (max_heap.empty()) {
        throw std::length_error("Heap is empty");
    }

    // 1. if only one item, pop it directly
    if (max_heap.size() == 1) {
        T temp = max_heap[0];
        max_heap.pop_back();
        return temp;
    }

    // 2. Remove the root and replace it with the last element
    T leaf = max_heap[max_heap.size() - 1];
    max_heap.pop_back();
    T root = max_heap[0];
    max_heap[0] = leaf;

    std::size_t current = 0;
    std::size_t left = (2 * current) + 1;
    std::size_t right = (2 * current) + 2;

    // 3. Propagate down from root to swap root with larger children
    while (left < max_heap.size() || right < max_heap.size()) {
        std::size_t larger_child;

        // check if the children index is valid
        if (left < max_heap.size() && right < max_heap.size()) {
            larger_child = (max_heap[left] > max_heap[right]) ? left : right;
        } else if (left < max_heap.size()) {
            larger_child = left;
        } else {
            larger_child = right;
        }

        // Check if current node < largest child, then swap
        if (max_heap[current] <= max_heap[larger_child]) {
            T temp = max_heap[current];
            max_heap[current] = max_heap[larger_child];
            max_heap[larger_child] = temp;

            // propagate down the tree
            current = larger_child;
            left = (2 * current) + 1;
            right = (2 * current) + 2;
        } else {
            break;
        }
    }
    return root;
}

} // namespace datastructs

#endif
