#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <algorithm>
#include <concepts>
#include <cstddef>
#include <datastructs/utilities.hpp>
#include <iostream>
#include <memory>
#include <stdexcept>

namespace datastructs {

/**
 * @brief A templated queue data structure.
 * * This class implements queue data structure that uses first-in first-out mechanism.
 * @tparam T is restricted to arithmetic types (integral & floating-point).
 */

template <datastructs::arithmetic T>
class Queue {
public:
    Queue(std::size_t);
    ~Queue() {};
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
                temp_head = (temp_head + 1) % static_cast<int>(queue.m_capacity);
            }
            out << queue.m_queue[static_cast<std::size_t>(temp_head)];
        }
        return out;
    }

private:
    int m_head;
    int m_tail;
    std::size_t m_capacity;
    std::unique_ptr<T[]> m_queue;
};

/**
 * @brief Constructor to initialise queue object.
 * @param size is the size of queue.
 */
template <datastructs::arithmetic T>
Queue<T>::Queue(std::size_t capacity)
    : m_head{-1}, m_tail{-1}, m_capacity{capacity}, m_queue{std::make_unique<T[]>(m_capacity)} {}

/**
 * @brief Copy constructor.
 * Deep copying is done.
 * @param other_queue queue object to copy from.
 */
template <datastructs::arithmetic T>
Queue<T>::Queue(const Queue& other_queue)
    : m_head{other_queue.m_head},
      m_tail{other_queue.m_tail},
      m_capacity{other_queue.m_capacity},
      m_queue{std::make_unique<T[]>(m_capacity)} {
    std::copy_n(other_queue.m_queue.get(), m_capacity, m_queue.get());
}

/**
 * @brief Copy assignment.
 * Deep copying is done.
 * @param other_queue queue object to copy from.
 */
template <datastructs::arithmetic T>
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

/**
 * @brief Move constructor.
 * * Moves resources from onether queue object, leaves the moved object in valid state.
 * @param other_queue queue object to move resource from.
 */
template <datastructs::arithmetic T>
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

/**
 * @brief Move assignment.
 * * Moves resources from another queue object, leaves the moved object in valid state.
 * @param other_queue queue object to move resource from.
 */
template <datastructs::arithmetic T>
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

/**
 * @brief To add data to queue.
 * * Addition of data happens at the end of the queue.
 * @throws std::length_error, when trying to add data to queue that is full.
 */
template <datastructs::arithmetic T>
void Queue<T>::enqueue(T value) {
    if (IsEmpty()) {
        ++m_head;
        ++m_tail;
        m_queue[static_cast<std::size_t>(m_tail)] = value;
    } else if (m_head == (m_tail + 1) % static_cast<int>(m_capacity)) {
        throw std::length_error("Queue is full.");
    } else {
        m_tail = (m_tail + 1) % static_cast<int>(m_capacity);
        m_queue[static_cast<std::size_t>(m_tail)] = value;
    }
}

/**
 * @brief To remove data from queue.
 * * Removal of data happens at the front of the queue.
 * @return copy of data removed from front of queue.
 * @throws std::length_error, when trying to remove data from empty queue.
 */
template <datastructs::arithmetic T>
T Queue<T>::dequeue() {
    if (IsEmpty()) {
        throw std::length_error("Queue is empty.");
    } else if (m_head == m_tail) {
        T value = m_queue[static_cast<std::size_t>(m_head)];
        m_head = -1;
        m_tail = -1;
        return value;
    } else {
        T value = m_queue[static_cast<std::size_t>(m_head)];
        m_head = (m_head + 1) % static_cast<int>(m_capacity);
        return value;
    }
}

/**
 * @brief To peak data at the front of the queue.
 * @throws std::length_error, when trying to peak from empty queue.
 * @return a copy of data at the front of the queue.
 */
template <datastructs::arithmetic T>
T Queue<T>::front() const {
    if (IsEmpty()) {
        throw std::length_error("Queue is empty.");
    } else {
        return m_queue[static_cast<std::size_t>(m_head)];
    }
}

/**
 * @brief To check if the queue is empty.
 * @return boolean data, true if queue is empty, false if otherwise.
 */
template <datastructs::arithmetic T>
bool Queue<T>::IsEmpty() const {
    if (m_head == -1 && m_tail == -1) {
        return true;
    }
    return false;
}
} // namespace datastructs

#endif
