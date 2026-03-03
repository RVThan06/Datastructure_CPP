#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <memory>
#include <stdexcept>

namespace datastructs {
template <typename T>
struct Node {
    T m_value{};
    std::unique_ptr<Node<T>> m_nextptr{nullptr};
};

template <typename T>
class LinkedList {
public:
    // default constructor for empty list
    LinkedList() : m_headptr{nullptr} {}

    LinkedList(T);
    LinkedList(const LinkedList&);
    LinkedList(LinkedList&&) noexcept;
    LinkedList(std::initializer_list<T>);
    LinkedList& operator=(const LinkedList&);
    LinkedList& operator=(LinkedList&&) noexcept;
    ~LinkedList();
    void insert_front(T);
    void insert_back(T);
    const Node<T>& search(T) const;
    void delete_front();
    void delete_back();
    bool is_empty() const;
    int length() const;

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

    template <typename U>
    class Iterator {
    public:
        using value_type = std::remove_const_t<U>;
        using difference_type = std::ptrdiff_t;
        using pointer = U*;
        using reference = U&;
        using iterator_category = std::forward_iterator_tag;

        Iterator(Node<std::remove_const_t<U>>* headptr) : current_ptr{headptr} {}

        // dereferencing
        reference operator*() const { return current_ptr->m_value; }
        pointer operator->() const { return &(current_ptr->m_value); }

        // Pre-increment
        Iterator& operator++() {
            current_ptr = current_ptr->m_nextptr.get();
            return *this;
        }

        // Post-increment
        Iterator operator++(int) {
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        bool operator!=(const Iterator& other_node) const { return current_ptr != other_node.current_ptr; }
        bool operator==(const Iterator& other_node) const { return current_ptr == other_node.current_ptr; }

    private:
        Node<std::remove_const_t<U>>* current_ptr; // Node is not const event for a constant object
    };

    // Node<T>

    using iterator = Iterator<T>;
    using const_iterator = Iterator<const T>;

    iterator begin() { return iterator(m_headptr.get()); }
    iterator end() { return iterator(nullptr); }

    const_iterator begin() const { return const_iterator(m_headptr.get()); }
    const_iterator end() const { return const_iterator(nullptr); }

    const_iterator cbegin() const { return const_iterator(m_headptr.get()); }
    const_iterator cend() const { return const_iterator(nullptr); }

private:
    std::unique_ptr<Node<T>> m_headptr;
    int m_length = 0;
};

template <typename T>
LinkedList<T>::LinkedList(T value) : m_headptr{new Node<T>{value}} {}

// copy constructur - use insert back
template <typename T>
LinkedList<T>::LinkedList(const LinkedList& other_list) : m_headptr{nullptr} {
    Node<T>* next_nodeptr = other_list.m_headptr.get();

    while (next_nodeptr) {
        insert_back(next_nodeptr->m_value);
        next_nodeptr = next_nodeptr->m_nextptr.get();
    }
}

// move constructor
template <typename T>
LinkedList<T>::LinkedList(LinkedList&& other_list) noexcept
    : m_headptr{std::move(other_list.m_headptr)}, m_length{other_list.m_length} {
    // leave other list in valid state
    other_list.m_length = 0;
}

// list constructor
template <typename T>
LinkedList<T>::LinkedList(std::initializer_list<T> list) : LinkedList() {
    for (std::size_t i = 0; i < list.size(); i++) {
        insert_back(list.begin()[i]);
    }
    m_length = static_cast<int>(list.size());
}

// copy assignment
template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList& other_list) {
    // self assignment check
    if (this == &other_list) {
        return *this;
    }

    // delete current list
    while (m_headptr) {
        std::unique_ptr<Node<T>> temp_node = std::move_if_noexcept(m_headptr);
        m_headptr = std::move_if_noexcept(temp_node->m_nextptr);
        // temp_node goes out of scope and dynamic memory is destroyed
    }

    // copy value to new list
    Node<T>* next_nodeptr = other_list.m_headptr.get();
    while (next_nodeptr) {
        insert_back(next_nodeptr->m_value);
        next_nodeptr = next_nodeptr->m_nextptr.get();
    }
    m_length = other_list.m_length;

    return *this;
}

// move assignment
template <typename T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList&& other_list) noexcept {
    // self assignment check
    if (this == &other_list) {
        return *this;
    }

    // delete current list
    while (m_headptr) {
        std::unique_ptr<Node<T>> temp_node = std::move(m_headptr);
        m_headptr = std::move(temp_node->m_nextptr);
        // temp_node goes out of scope and dynamic memory is destroyed
    }

    // move the list
    m_headptr = std::move(other_list.m_headptr);
    m_length = other_list.m_length;
    other_list.m_length = 0;

    return *this;
}

// destructor
template <typename T>
LinkedList<T>::~LinkedList() {}

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

// returns a const reference to node
template <typename T>
const Node<T>& LinkedList<T>::search(T val) const {
    if (!m_headptr) {
        throw std::length_error("Error: Empty list cannot be searched");
    }

    Node<T>* next_nodeptr = m_headptr.get();

    // if there is at least 1 node
    while (next_nodeptr) {
        if (next_nodeptr->m_value == val) {
            return *next_nodeptr;
        }

        next_nodeptr = next_nodeptr->m_nextptr.get();
    }

    throw std::runtime_error("Error: Value not found in list");
}

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

template <typename T>
bool LinkedList<T>::is_empty() const {
    if (m_headptr) {
        return false;
    }

    return true;
}

template <typename T>
int LinkedList<T>::length() const {
    return m_length;
}

} // namespace datastructs

#endif
