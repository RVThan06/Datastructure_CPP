#ifndef STACK_HPP
#define STACK_HPP

#include <algorithm>
#include <concepts>
#include <cstddef>
#include <iostream>
#include <memory>

namespace datastructs {

/**
 * @brief A templated stack data structure.
 * * This class implements stack data structure with Last-in first-out mechanism.
 * @tparam T is the type of the data stored by the underlying datastructure.
 */

template <typename T>
class Stack {
public:
    Stack(std::size_t);
    ~Stack() {};
    Stack(const Stack&);
    Stack& operator=(const Stack&);
    Stack(Stack&&);
    Stack& operator=(Stack&&);

    // stack functions
    void push(T);
    T pop();
    T peak() const;
    bool isEmpty() const;
    int size() const;
    std::size_t capacity() const;

    /// @brief Ostream overload for printing of linked list
    friend std::ostream& operator<<(std::ostream& out, const Stack& stack) {
        for (int i = 0; i <= stack.m_top; i++) {
            out << stack.m_stack[static_cast<std::size_t>(i)] << ", ";
        }

        return out;
    }

private:
    std::size_t m_capacity{};
    int m_top = -1;
    std::unique_ptr<T[]> m_stack;
};

/**
 * @brief Constructs stack object for a given size.
 * @param size is the size of stack.
 */
template <typename T>
Stack<T>::Stack(std::size_t size) : m_capacity{size}, m_stack{std::make_unique<T[]>(m_capacity)} {}

/**
 * @brief Copy constructor.
 * Deep copying is done.
 * @param other_obj stack object to copy from.
 */
template <typename T>
Stack<T>::Stack(const Stack& other_obj)
    : m_capacity{other_obj.m_capacity}, m_top{other_obj.m_top}, m_stack{std::make_unique<T[]>(m_capacity)} {
    std::copy_n(other_obj.m_stack.get(), m_capacity, m_stack.get());
}

/**
 * @brief Copy assignment.
 * Deep copying is done.
 * @param other_obj stack object to copy from.
 */
template <typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& other_obj) {
    // self assignment check
    if (this == &other_obj) {
        return *this;
    }

    m_capacity = other_obj.m_capacity;
    m_top = other_obj.m_top;
    m_stack.reset(new T[m_capacity]); // replace allocated memory with new one, old one is deallocated
    std::copy_n(other_obj.m_stack.get(), m_capacity, m_stack.get());
    return *this;
}

/**
 * @brief Move constructor.
 * * Moves resources from onether stack object, leaves the moved object in valid state.
 * @param other_obj stack object to move resource from.
 */
template <typename T>
Stack<T>::Stack(Stack&& other_obj)
    : m_capacity{other_obj.m_capacity}, m_top{other_obj.m_top}, m_stack{std::move(other_obj.m_stack)} {
    // leave the moved object in valid state
    other_obj.m_capacity = 0;
    other_obj.m_top = -1;
}

/**
 * @brief Move assignment.
 * * Moves resources from another stack object, leaves the moved object in valid state.
 * @param other_obj stack object to move resource from.
 */
template <typename T>
Stack<T>& Stack<T>::operator=(Stack<T>&& other_obj) {
    m_capacity = other_obj.m_capacity;
    m_top = other_obj.m_top;
    m_stack = std::move(other_obj.m_stack);

    // leave the moved object in valid state
    other_obj.m_capacity = 0;
    other_obj.m_top = -1;

    return *this;
}

/**
 * @brief Push function, to push data onto top of stack.
 * @param val data to be pushed onto stack.
 * @throws std::out_of_range, if stack is full.
 */
template <typename T>
void Stack<T>::push(T val) {
    if (m_top < static_cast<int>(m_capacity) - 1) {
        ++m_top;
        m_stack[static_cast<std::size_t>(m_top)] = val;
        return;
    }

    throw std::out_of_range("Error: Stack is full");
}

/**
 * @brief Pop function, to remove data from top of stack.
 * @return data stored on stack that was removed.
 * @note Does not perform bound checking. Popping empty stack can cause UB.
 */
template <typename T>
T Stack<T>::pop() {
    --m_top;
    return m_stack[static_cast<std::size_t>((m_top) + 1)];
}

/**
 * @brief Peak function, to return data on top of stack without removing it.
 * @return data stored on top of stack.
 * @throws std::out_of_range, if stack is empty.
 */
template <typename T>
T Stack<T>::peak() const {
    if (isEmpty()) {
        throw std::out_of_range("Error: Stack is empty so cannot be peaked.");
    }
    return m_stack[static_cast<std::size_t>(m_top)];
}

/**
 * @brief To check if the stack is empty.
 * @return boolean data, true if stack is empty, false if otherwise
 */
template <typename T>
bool Stack<T>::isEmpty() const {
    if (m_top < 0) {
        return true;
    }
    return false;
}

/**
 * @brief To return the number of elements on stack.
 * @return number of elements.
 */
template <typename T>
int Stack<T>::size() const {
    return m_top + 1;
}

/**
 * @brief To return the total capacity of stack.
 * @return stack capacity --> m_capacity.
 */
template <typename T>
std::size_t Stack<T>::capacity() const {
    return m_capacity;
}

} // namespace datastructs

#endif
