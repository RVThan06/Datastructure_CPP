#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <memory>
#include <optional>
#include <stdexcept>

namespace datastructs {

/**
 * @brief Node struct that forms each node in linked list.
 * m_value -> stores data.
 * m_nextptr -> stores pointer to next node.
 */
template <typename T>
struct Node {
    T m_value{};
    std::unique_ptr<Node<T>> m_nextptr{nullptr};
};

/**
 * @brief A template class for singly linked list data structure.
 * @tparam T is the type of the data stored by the underlying datastructure.
 */
template <typename T>
class LinkedList {
public:
    /// @brief Constructors and assignment
    LinkedList() : m_headptr{nullptr} {}
    explicit LinkedList(T);
    LinkedList(const LinkedList&);
    LinkedList(LinkedList&&) noexcept;
    LinkedList(std::initializer_list<T>);
    LinkedList& operator=(const LinkedList&);
    LinkedList& operator=(LinkedList&&) noexcept;
    ~LinkedList() {};

    /// @brief Linked list operations
    void insert_front(T);
    void insert_back(T);
    std::optional<T> search(T) const;
    void delete_front();
    void delete_back();
    bool is_empty() const;
    int length() const;

    /// @brief Ostream overload for printing of linked list
    friend std::ostream& operator<<(std::ostream& out, const LinkedList& list) {
        Node<T>* next_nodeptr = list.m_headptr.get();

        // if there is at least 1 node
        while (next_nodeptr) {
            std::cout << next_nodeptr->m_value;
            next_nodeptr = next_nodeptr->m_nextptr.get();

            if (next_nodeptr) {
                out << " --> ";
            }
        }
        return out;
    }

    /**
     * @brief iterator class for linked list
     * This is a forward iterator class.
     * @tparam U is the value type of container item.
     * * U could be const T or T depending on whether the underlying container is const or not.
     */
    template <typename U>
    class Iterator {
    public:
        /// @brief Iterator traits
        using value_type = std::remove_const_t<U>; // remove const since container item type is always T not const T
        using difference_type = std::ptrdiff_t;
        using pointer = U*;
        using reference = U&;
        using iterator_category = std::forward_iterator_tag;

        /**
         * @brief Constructor
         * @param headptr, the head pointer of list.
         */
        explicit Iterator(Node<std::remove_const_t<U>>* headptr) : current_ptr{headptr} {}

        /// @brief Dereferencing operators
        reference operator*() const { return current_ptr->m_value; }
        pointer operator->() const { return &(current_ptr->m_value); }

        /// @brief pre-increment
        Iterator& operator++() {
            current_ptr = current_ptr->m_nextptr.get();
            return *this;
        }

        /// @brief Post-increment
        Iterator operator++(int) {
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        /// @brief Equality overloads
        bool operator!=(const Iterator& other_node) const { return current_ptr != other_node.current_ptr; }
        bool operator==(const Iterator& other_node) const { return current_ptr == other_node.current_ptr; }

    private:
        Node<std::remove_const_t<U>>* current_ptr; // Node<T> not Node<const T> even for const list objects
    };

    /// @brief Iterator alias
    using iterator = Iterator<T>;
    using const_iterator = Iterator<const T>;

    /// @brief Non -const Forward iterator member function
    iterator begin() { return iterator(m_headptr.get()); }
    iterator end() { return iterator(nullptr); }

    /// @brief Implicit constant forward iterators - overloads to begin & end
    const_iterator begin() const { return const_iterator(m_headptr.get()); }
    const_iterator end() const { return const_iterator(nullptr); }

    /// @brief Explicit const forward interators
    const_iterator cbegin() const { return const_iterator(m_headptr.get()); }
    const_iterator cend() const { return const_iterator(nullptr); }

private:
    std::unique_ptr<Node<T>> m_headptr;
    int m_length = 0;
};

/**
 * @brief construcot to initialise linked list with a single node.
 * @param value the value for the first node created in list.
 */
template <typename T>
LinkedList<T>::LinkedList(T value) : m_headptr{new Node<T>{value}} {}

/**
 * @brief Copy constructor.
 * Deep copying is done.
 * @param other_list, list object to copy from.
 */
template <typename T>
LinkedList<T>::LinkedList(const LinkedList& other_list) : m_headptr{nullptr} {
    for (const auto& node : other_list) {
        insert_back(node);
    }
}

/**
 * @brief Move constructor.
 * * Moves resources from another list object, leaves the moved object in valid state.
 * @param other_list list object to move resource from.
 */
template <typename T>
LinkedList<T>::LinkedList(LinkedList&& other_list) noexcept
    : m_headptr{std::move(other_list.m_headptr)}, m_length{other_list.m_length} {
    // leave movedlist in valid state
    other_list.m_length = 0;
}

/**
 * @brief List constructor.
 * * Initialises a list using initilizer list by copying all the values in it
 * to create a node for each value and form a list eventually.
 * @param list, std::initializer list object.
 */
template <typename T>
LinkedList<T>::LinkedList(std::initializer_list<T> list) : LinkedList() {
    for (std::size_t i = 0; i < list.size(); i++) {
        insert_back(list.begin()[i]);
    }
    m_length = static_cast<int>(list.size());
}

/**
 * @brief Copy assignment.
 * Deep copying is done.
 * @param other_list list object to copy from.
 */
template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList& other_list) {
    // self assignment check
    if (this == &other_list) {
        return *this;
    }

    // delete current list
    m_headptr.reset();

    // copy data by interating other_list
    for (const auto& node : other_list) {
        insert_back(node);
    }
    m_length = other_list.m_length;

    return *this;
}

/**
 * @brief Move assignment.
 * * Moves resources from another list object, leaves the moved object in valid state.
 * @param other_list list object to move resource from.
 */
template <typename T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList&& other_list) noexcept {
    // self assignment check
    if (this == &other_list) {
        return *this;
    }

    // move the list - inherently will deallocate current list
    m_headptr = std::move(other_list.m_headptr);
    m_length = other_list.m_length;

    // leave moved list in valid state
    other_list.m_length = 0;

    return *this;
}

/**
 * @brief To insert a new node at the start of the list.
 * Time complexity: O(1)
 * @param value, the value for the new node to insert.
 */
template <typename T>
void LinkedList<T>::insert_front(T value) {
    std::unique_ptr<Node<T>> new_node{new Node<T>{value}};

    // list is empty
    if (!m_headptr) {
        m_headptr = std::move(new_node);
        ++m_length;
        return;
    }

    // list is not empty
    new_node->m_nextptr = std::move(m_headptr);
    m_headptr = std::move(new_node);
    ++m_length;
    return;
}

/**
 * @brief To insert a new node at the end of the list.
 * Time complexity: O(n).
 * This operation requires full list traversal.
 * @param value, the value for the new node to insert.
 */
template <typename T>
void LinkedList<T>::insert_back(T value) {
    std::unique_ptr<Node<T>> new_node{new Node<T>{value}};

    if (!m_headptr) {
        m_headptr = std::move(new_node);
        ++m_length;
        return;
    }

    // list is not empty
    Node<T>* next_nodeptr = m_headptr.get();

    // if there is at least 1 node
    while (next_nodeptr) {
        if (next_nodeptr->m_nextptr.get()) {
            next_nodeptr = next_nodeptr->m_nextptr.get();
            continue;
        }
        next_nodeptr->m_nextptr = std::move(new_node);
        ++m_length;
        return;
    }
}

/**
 * @brief To search for a given node based on the value it stores.
 * Time complexity: O(n).
 * This operation requires full list traversal.
 * @param val, the value to search for
 * @returns std::optional containing value if found, nullopt if not found
 * @throws std::length_error, if list is empty
 */
template <typename T>
std::optional<T> LinkedList<T>::search(T val) const {
    if (!m_headptr) {
        throw std::length_error("Error: Empty list cannot be searched");
    }
    Node<T>* next_nodeptr = m_headptr.get();

    // if there is at least 1 node
    while (next_nodeptr) {
        if (next_nodeptr->m_value == val) {
            return next_nodeptr->m_value;
        }
        next_nodeptr = next_nodeptr->m_nextptr.get();
    }

    // value not found
    return std::nullopt;
}

/**
 * @brief To delete node from the front of list.
 * Time complexity: O(1).
 * @throws std::length_error, when trying to delete from an empty list.
 */
template <typename T>
void LinkedList<T>::delete_front() {
    if (!m_headptr) {
        throw std::length_error("Error: Empty list cannot be deleted.");
    }

    std::unique_ptr<Node<T>> temp_node = std::move_if_noexcept(m_headptr);
    m_headptr = std::move_if_noexcept(temp_node->m_nextptr);
    --m_length;
    return;
}

/**
 * @brief To delete node from the rear of list.
 * Time complexity: O(n).
 * This operation requires full list traversal.
 * @throws std::length_error, when trying to delete from an empty list.
 */
template <typename T>
void LinkedList<T>::delete_back() {
    if (!m_headptr) {
        throw std::length_error("Error: Empty list cannot be deleted.");
    }

    // if only one node
    if (!m_headptr->m_nextptr.get()) {
        m_headptr.reset(nullptr);
        --m_length;
        return;
    }

    Node<T>* next_nodeptr = m_headptr.get();
    Node<T>* prev_nodeptr = nullptr;
    while (next_nodeptr) {
        if (next_nodeptr->m_nextptr.get()) {
            prev_nodeptr = next_nodeptr;
            next_nodeptr = next_nodeptr->m_nextptr.get();
            continue;
        }
        prev_nodeptr->m_nextptr.reset(nullptr);
        --m_length;
        return;
    }
}

/**
 * @brief To check if list is empty.
 * @return boolean data, true if list is empty, false if otherwise.
 */
template <typename T>
bool LinkedList<T>::is_empty() const {
    if (m_headptr) {
        return false;
    }
    return true;
}

/**
 * @brief To get the length of list.
 * @return number of nodes in list.
 */
template <typename T>
int LinkedList<T>::length() const {
    return m_length;
}

} // namespace datastructs

#endif
