#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <algorithm>
#include <iostream>
#include <memory>
#include <stdexcept>

namespace datastructs {
template <typename T>
class Queue {
private:
    int m_head;
    int m_tail;
    int m_capacity;
    std::unique_ptr<T[]> m_queue;

public:
    Queue(int);
    ~Queue();
    Queue(const Queue&);
    Queue& operator=(const Queue&);
    Queue(Queue&&) noexcept;
    Queue& operator=(Queue&&) noexcept;

    // queue operations
    void enqueue(T);
    T dequeue();
    T front() const;
    bool IsEmpty() const;

    // ostream overload
    friend std::ostream& operator<<(std::ostream& out, const Queue& queue) {
        if (!queue.IsEmpty()) {
            int temp_head = queue.m_head;
            while (temp_head != queue.m_tail) {
                out << queue.m_queue[static_cast<std::size_t>(temp_head)] << ", ";
                temp_head = (temp_head + 1) % queue.m_capacity;
            }
            out << queue.m_queue[static_cast<std::size_t>(temp_head)];
        }
        return out;
    }
};

// default constructor
template <typename T>
Queue<T>::Queue(int capacity) : m_head{-1}, m_tail{-1}, m_capacity{capacity}, m_queue{new T[m_capacity]} {}

// destructor
template <typename T>
Queue<T>::~Queue() {}

// copy constructor
template <typename T>
Queue<T>::Queue(const Queue& other_queue)
    : m_head{other_queue.m_head},
      m_tail{other_queue.m_tail},
      m_capacity{other_queue.m_capacity},
      m_queue{new T[m_capacity]} {
    std::copy_n(other_queue.m_queue.get(), m_capacity, m_queue.get());
}

// copy assignment
template <typename T>
Queue<T>& Queue<T>::operator=(const Queue& other_queue) {
    // self assignment check
    if (this == &other_queue) {
        return *this;
    }

    // reassign data members
    m_head = other_queue.m_head;
    m_tail = other_queue.m_tail;
    m_capacity = other_queue.m_capacity;

    // deallocate current memory and allocate new memory
    m_queue.reset(new T[m_capacity]);
    std::copy_n(other_queue.m_queue.get(), m_capacity, m_queue.get());

    // return this for chained assignment
    return *this;
}

// move constructor
template <typename T>
Queue<T>::Queue(Queue&& other_queue) noexcept
    : m_head{other_queue.m_head},
      m_tail{other_queue.m_tail},
      m_capacity{other_queue.m_capacity},
      m_queue{std::move(other_queue.m_queue)} {
    // leave moved object in valid state
    other_queue.m_capacity = 0;
    other_queue.m_head = -1;
    other_queue.m_tail = -1;
}

// move assignment
template <typename T>
Queue<T>& Queue<T>::operator=(Queue&& other_queue) noexcept {
    // self assignment check
    if (this == &other_queue) {
        return *this;
    }

    // reassign data members
    m_head = other_queue.m_head;
    m_tail = other_queue.m_tail;
    m_capacity = other_queue.m_capacity;

    // move the resource
    m_queue = std::move(other_queue.m_queue);

    // set moved object to valid state
    other_queue.m_head = -1;
    other_queue.m_tail = -1;
    other_queue.m_capacity = 0;

    return *this;
}

template <typename T>
void Queue<T>::enqueue(T value) {
    if (IsEmpty()) {
        ++m_head;
        ++m_tail;
        m_queue[static_cast<std::size_t>(m_tail)] = value;
    } else if (m_head == (m_tail + 1) % m_capacity) {
        throw std::length_error("Queue is full");
    } else {
        m_tail = (m_tail + 1) % m_capacity;
        m_queue[static_cast<std::size_t>(m_tail)] = value;
    }
}

template <typename T>
T Queue<T>::dequeue() {
    if (IsEmpty()) {
        throw std::length_error("Queue is full");
    } else if (m_head == m_tail) {
        T value = m_queue[static_cast<std::size_t>(m_head)];
        m_head = -1;
        m_tail = -1;
        return value;
    } else {
        T value = m_queue[static_cast<std::size_t>(m_head)];
        m_head = (m_head + 1) % m_capacity;
        return value;
    }
}

template <typename T>
T Queue<T>::front() const {
    if (IsEmpty()) {
        throw std::length_error("Queue is full");
    } else {
        return m_queue[static_cast<std::size_t>(m_head)];
    }
}

template <typename T>
bool Queue<T>::IsEmpty() const {
    if (m_head == -1 && m_tail == -1) {
        return true;
    }
    return false;
}
} // namespace datastructs

#endif
