#ifndef STACK_HPP
#define STACK_HPP

#include <algorithm>
#include <concepts>
#include <iostream>
#include <memory>

namespace datastructs {
// stack class template
template <typename T>
class Stack {
public:
    Stack(int);
    ~Stack();
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

    // tp print stack elements
    friend std::ostream& operator<<(std::ostream& out, const Stack& stack) {
        for (int i = 0; i <= stack.m_top; i++) {
            out << stack.m_stack[static_cast<std::size_t>(i)] << ", ";
        }

        return out;
    }

private:
    int m_capacity{};
    int m_top = -1;
    std::unique_ptr<T[]> m_stack;
};

template <typename T>
Stack<T>::Stack(int size) : m_capacity{size}, m_stack{new T[m_capacity]} {}

// destructor
template <typename T>
Stack<T>::~Stack() {}

// copy constructor --> deep copy
template <typename T>
Stack<T>::Stack(const Stack& other_obj)
    : m_capacity{other_obj.m_capacity}, m_top{other_obj.m_top}, m_stack{new T[m_capacity]} {
    std::copy_n(other_obj.m_stack.get(), m_capacity, m_stack.get());
}

// copy assignment --> deep copy
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

// move constructor
template <typename T>
Stack<T>::Stack(Stack&& other_obj)
    : m_capacity{other_obj.m_capacity}, m_top{other_obj.m_top}, m_stack{std::move(other_obj.m_stack)} {
    // leave the moved object in valid state
    other_obj.m_capacity = 0;
    other_obj.m_top = -1;
}

// move assignment
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

template <typename T>
void Stack<T>::push(T val) {
    if (m_top < m_capacity - 1) {
        ++m_top;
        m_stack[static_cast<std::size_t>(m_top)] = val;
        return;
    }

    throw std::out_of_range("Error: Stack is full");
}

// no bound checking done, will cause undefined behaviour if pop out of bound
template <typename T>
T Stack<T>::pop() {
    --m_top;
    return m_stack[static_cast<std::size_t>((m_top) + 1)];
}

// returns the top element by value without removing it
template <typename T>
T Stack<T>::peak() const {
    if (isEmpty()) {
        throw std::out_of_range("Error: Stack is empty so cannot be peaked.");
    }
    return m_stack[static_cast<std::size_t>(m_top)];
}

template <typename T>
bool Stack<T>::isEmpty() const {
    if (m_top < 0) {
        return true;
    }
    return false;
}

// return current number of elements on stack
template <typename T>
int Stack<T>::size() const {
    return m_top + 1;
}

} // namespace datastructs

#endif
