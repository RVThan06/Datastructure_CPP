#ifndef D_LINKED_LIST_HPP
#define D_LINKED_LIST_HPP

#include <initializer_list>
#include <iostream>
#include <memory>
#include <stdexcept>

namespace datastructs {
template <typename T>
struct Node_d {
    T m_value{};
    Node_d<T>* m_nextptr{nullptr};
    Node_d<T>* m_prevptr{nullptr};
};

template <typename T>
class DLinkedList {
public:
    // initialise empty list
    DLinkedList() : m_headptr{nullptr}, m_tailptr{nullptr}, m_length{0} {}

    DLinkedList(T value) : m_headptr{new Node_d<T>{value}}, m_tailptr{m_headptr}, m_length{1} {}

    ~DLinkedList();
    DLinkedList(const DLinkedList& other_list);
    DLinkedList(DLinkedList&& other_list) noexcept;
    DLinkedList(std::initializer_list<T> list);
    DLinkedList& operator=(const DLinkedList& other_list);
    DLinkedList& operator=(DLinkedList&& other_list) noexcept;
    void insert_front(T value);
    void insert_rear(T value);
    void delete_front();
    void delete_rear();
    const Node_d<T>* search(T value) const;
    int length() const { return m_length; }
    bool is_empty() const;

    friend std::ostream& operator<<(std::ostream& out, const DLinkedList& list) {
        Node_d<T>* next_nodeptr = list.m_headptr;
        while (next_nodeptr != nullptr) {
            out << next_nodeptr->m_value;
            next_nodeptr = next_nodeptr->m_nextptr;

            if (next_nodeptr != nullptr) {
                out << "-->";
            }
        }
        return out;
    }

    // Iterator class
    template <typename U>
    class Iterator {
    public:
        using value_type = std::remove_const_t<T>;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;
        using iterator_category = std::bidirectional_iterator_tag;

        explicit Iterator(Node_d<std::remove_const_t<T>>* node) : current(node) {}

        // Dereference
        reference operator*() const { return current->m_value; }
        pointer operator->() const { return &(current->m_value); }

        // Pre-increment
        Iterator& operator++() {
            current = current->m_nextptr;
            return *this;
        }

        // Post-increment
        Iterator operator++(int) {
            Iterator temp = *this;
            ++(*this);
            return temp;
        }

        // Pre-decrement
        Iterator& operator--() {
            current = current->m_prevptr;
            return *this;
        }

        // Post-decrement
        Iterator operator--(int) {
            Iterator temp = *this;
            --(*this);
            return temp;
        }

        // Equality operators
        bool operator!=(const Iterator& other_node) const { return current != other_node.current; }
        bool operator==(const Iterator& other_node) const { return current == other_node.current; }

    private:
        Node_d<std::remove_const_t<T>>* current;
    };

    using iterator = Iterator<T>;
    using const_iterator = Iterator<const T>;

    iterator begin() { return iterator(m_headptr); }
    iterator end() { return iterator(nullptr); }

    iterator rbegin() { return iterator(m_tailptr); }
    iterator rend() { return iterator(nullptr); }

    const_iterator begin() const { return const_iterator(m_headptr); }
    const_iterator end() const { return const_iterator(nullptr); }

    const_iterator cbegin() const { return const_iterator(m_headptr); }
    const_iterator cend() const { return const_iterator(nullptr); }

private:
    Node_d<T>* m_headptr;
    Node_d<T>* m_tailptr;
    int m_length;
};

template <typename T>
DLinkedList<T>::~DLinkedList() {
    // if any node is left at end of program
    if (m_headptr != nullptr) {
        // delete each node by traversing the list till nullptr
        Node_d<T>* temp = nullptr;

        while (m_headptr != nullptr) {
            temp = m_headptr;
            m_headptr = m_headptr->m_nextptr;
            delete temp;
        }
    }
}

template <typename T>
DLinkedList<T>::DLinkedList(const DLinkedList& other_list)
    : m_headptr{nullptr}, m_tailptr{nullptr}, m_length{other_list.m_length} {
    Node_d<T>* next_nodeptr = other_list.m_headptr;
    while (next_nodeptr) {
        insert_rear(next_nodeptr->m_value);
        next_nodeptr = next_nodeptr->m_nextptr;
    }
}

template <typename T>
DLinkedList<T>::DLinkedList(DLinkedList&& other_list) noexcept
    : m_headptr{other_list.m_headptr}, m_tailptr{other_list.m_tailptr}, m_length{other_list.m_length} {
    // leave the moved list valid
    other_list.m_headptr = nullptr;
    other_list.m_tailptr = nullptr;
    other_list.m_length = 0;
}

template <typename T>
DLinkedList<T>::DLinkedList(std::initializer_list<T> list) : DLinkedList() {
    for (std::size_t i = 0; i < list.size(); i++) {
        insert_rear(list.begin()[i]);
    }

    m_length = static_cast<int>(list.size());
}

template <typename T>
DLinkedList<T>& DLinkedList<T>::operator=(const DLinkedList<T>& other_list) {
    // self assignment check
    if (this == &other_list) {
        return *this;
    }

    // delete current list
    while (!is_empty()) {
        delete_front();
    }

    // copy the list
    Node_d<T>* next_nodeptr = other_list.m_headptr;
    while (next_nodeptr) {
        insert_rear(next_nodeptr->m_value);
        next_nodeptr = next_nodeptr->m_nextptr;
    }
    m_length = other_list.m_length;

    return *this;
}

template <typename T>
DLinkedList<T>& DLinkedList<T>::operator=(DLinkedList<T>&& other_list) noexcept {
    // self assignment check
    if (this == &other_list) {
        return *this;
    }

    // delete current list
    while (!is_empty()) {
        delete_front();
    }

    // move data to new list
    m_headptr = other_list.m_headptr;
    m_tailptr = other_list.m_tailptr;
    m_length = other_list.m_length;

    // leave other list in valid state
    other_list.m_headptr = nullptr;
    other_list.m_tailptr = nullptr;
    other_list.m_length = 0;

    return *this;
}

template <typename T>
void DLinkedList<T>::insert_front(T value) {
    Node_d<T>* new_node = new Node_d<T>{value};

    // when list is empty
    if (m_headptr == nullptr) {
        m_headptr = new_node;
        m_tailptr = new_node;
    } else {
        // when list is not empty
        new_node->m_nextptr = m_headptr;
        m_headptr->m_prevptr = new_node;
        m_headptr = new_node;
    }

    ++m_length;
    return;
}

template <typename T>
void DLinkedList<T>::insert_rear(T value) {
    Node_d<T>* new_node = new Node_d<T>{value};

    // when list is empty
    if (m_tailptr == nullptr) {
        m_headptr = new_node;
        m_tailptr = new_node;
    } else {
        // when list is not empty
        m_tailptr->m_nextptr = new_node;
        new_node->m_prevptr = m_tailptr;
        m_tailptr = new_node;
    }

    ++m_length;
    return;
}

template <typename T>
void DLinkedList<T>::delete_front() {
    // throw exception if node is empty
    if (!m_headptr) {
        throw std::length_error("Error: Empty list cannot be deleted");
    }

    // if only one node
    if (m_headptr == m_tailptr) {
        delete m_headptr;
        m_headptr = nullptr;
        m_tailptr = nullptr;
        --m_length;
        return;
    }

    // if more than one node
    Node_d<T>* temp = nullptr;
    m_headptr->m_nextptr->m_prevptr = nullptr;
    temp = m_headptr;
    m_headptr = m_headptr->m_nextptr;
    delete temp;
    --m_length;

    return;
}

template <typename T>
void DLinkedList<T>::delete_rear() {
    // throw exception if node is empty
    if (!m_headptr) {
        throw std::length_error("Error: Empty list cannot be deleted");
    }

    // if only one node
    if (m_headptr == m_tailptr) {
        delete m_headptr;
        m_headptr = nullptr;
        m_tailptr = nullptr;
        --m_length;
        return;
    }

    // if more than one node
    Node_d<T>* temp = nullptr;
    m_tailptr->m_prevptr->m_nextptr = nullptr;
    temp = m_tailptr;
    m_tailptr = m_tailptr->m_prevptr;
    delete temp;
    --m_length;

    return;
}

template <typename T>
const Node_d<T>* DLinkedList<T>::search(T value) const {
    // throw exception if node is empty
    if (!m_headptr) {
        throw std::length_error("Error: Empty list cannot be searched");
    }

    // return pointer to node if node is found
    Node_d<T>* temp = m_headptr;
    while (temp != nullptr) {
        if (temp->m_value == value) {
            return temp;
        }
        temp = temp->m_nextptr;
    }

    // if node not found return nullptr
    return nullptr;
}

template <typename T>
bool DLinkedList<T>::is_empty() const {
    if (!m_headptr) {
        return true;
    }
    return false;
}

} // namespace datastructs

#endif
