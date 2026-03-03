#ifndef MYVECTOR_HPP
#define MYVECTOR_HPP

#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <memory>

namespace datastructs {
template <typename T>
class Myvector {
public:
    Myvector(int = 0, T = {});
    ~Myvector() {}
    Myvector(std::initializer_list<T>);
    Myvector(const Myvector&);
    Myvector& operator=(const Myvector&);
    Myvector(Myvector&&) noexcept;
    Myvector& operator=(Myvector&&) noexcept;

    // utility functions
    void push_back(T);
    void pop_back();
    T& operator[](int);
    const T& operator[](int) const;
    T& at(int);
    const T& at(int) const;
    int get_size() const { return m_size; }
    int get_capacity() const { return m_capacity; }
    bool empty();
    T* data();
    void resize(int, T = {}); // value initialised
    void reserve(int);

    // overload ostream operator to print
    friend std::ostream& operator<<(std::ostream& out, const Myvector& vector) {
        for (int i = 0; i < vector.m_size; i++) {
            out << vector.array[static_cast<std::size_t>(i)] << " ";
        }
        return out;
    }

    template <typename U>
    class VectorIterator {
    public:
        using value_type = std::remove_const_t<U>;
        using difference_type = std::ptrdiff_t;
        using pointer = U*;
        using reference = U&;
        using iterator_category = std::random_access_iterator_tag;

        explicit VectorIterator(U* current_ptr) : current{current_ptr} {}

        // dereference
        reference operator*() const { return *current; }
        pointer operator->() const { return current; }

        // subscript --> random access
        reference operator[](difference_type index) const { return current[index]; }

        // increment / decrement
        VectorIterator& operator++() {
            ++current;
            return *this;
        }
        VectorIterator operator++(int) {
            VectorIterator temp = *this;
            ++(*this);
            return temp;
        }
        VectorIterator& operator--() {
            --current;
            return *this;
        }
        VectorIterator operator--(int) {
            VectorIterator temp = *this;
            --(*this);
            return temp;
        }

        // Addition / Subtraction
        VectorIterator operator+(difference_type n) const { return VectorIterator(current + n); }
        VectorIterator operator-(difference_type n) const { return VectorIterator(current - n); }
        VectorIterator& operator+=(difference_type n) {
            current += n;
            return *this;
        }
        VectorIterator& operator-=(difference_type n) {
            current -= n;
            return *this;
        }

        // Distance between iterator
        difference_type operator-(const VectorIterator& other_iterator) const {
            return current - other_iterator.current;
        }

        // comparisons
        bool operator==(const VectorIterator& other_iterator) const { return current == other_iterator.current; }
        bool operator!=(const VectorIterator& other_iterator) const { return current != other_iterator.current; }
        bool operator>(const VectorIterator& other_iterator) const { return current > other_iterator.current; }
        bool operator<(const VectorIterator& other_iterator) const { return current < other_iterator.current; }
        bool operator>=(const VectorIterator& other_iterator) const { return current >= other_iterator.current; }
        bool operator<=(const VectorIterator& other_iterator) const { return current <= other_iterator.current; }

    private:
        pointer current;
    };

    // iterator type aliases
    using iterator = VectorIterator<T>;
    using const_iterator = VectorIterator<const T>;

    iterator begin() { return iterator(array.get()); }
    const_iterator begin() const { return const_iterator(array.get()); }

    iterator end() { return iterator(array.get() + m_size); }
    const_iterator end() const { return const_iterator(array.get() + m_size); }

    const_iterator cbegin() const { return const_iterator(array.get()); }
    const_iterator cend() const { return const_iterator(array.get() + m_size); }

private:
    int m_capacity;
    int m_size;
    std::unique_ptr<T[]> array;

protected:
    void reallocation(int = -1);
};

// default constructor
template <typename T>
Myvector<T>::Myvector(int size, T val) : m_capacity{(size + 4)}, m_size{size}, array{new T[(size + 4)]} {
    for (int i = 0; i < m_size; i++) {
        array[static_cast<std::size_t>(i)] = val;
    }
}

// list constructor
template <typename T>
Myvector<T>::Myvector(std::initializer_list<T> list)
    : m_capacity{(static_cast<int>(list.size()) + 4)}, m_size{0}, array{new T[(static_cast<int>(list.size()) + 4)]} {
    // copy values into vector from initialiser list
    for (std::size_t i = 0; i < list.size(); i++) {
        push_back(list.begin()[i]); // begin returns 1st pointer to initialiser list
    }
}

// copy constructor
template <typename T>
Myvector<T>::Myvector(const Myvector<T>& other_vector)
    : m_capacity{other_vector.m_capacity}, m_size{other_vector.m_size}, array{new T[m_capacity]} {
    std::copy_n(other_vector.array.get(), m_size, array.get());
}

// copy assignment operator -- deep copy
template <typename T>
Myvector<T>& Myvector<T>::operator=(const Myvector<T>& other_vector) {
    // self assignment check
    if (this == &other_vector) {
        return *this;
    }

    // deallocate current memory
    array.reset(nullptr);

    // allocate new memory based on new m_size and m_capacity
    m_capacity = other_vector.m_capacity;
    m_size = other_vector.m_size;
    array.reset(new T[m_capacity]);

    // copy all elements from other vector to this vector
    std::copy_n(other_vector.array.get(), m_size, array.get());

    return *this;
}

// move constructor
template <typename T>
Myvector<T>::Myvector(Myvector<T>&& other_vector) noexcept
    : m_capacity{other_vector.m_capacity},
      m_size{other_vector.m_size},
      array{std::move_if_noexcept(other_vector.array)} {
    // after moving object is left in valid state
    other_vector.m_capacity = 0;
    other_vector.m_size = 0;
}

template <typename T>
Myvector<T>& Myvector<T>::operator=(Myvector<T>&& other_vector) noexcept {
    // self assignment check
    if (this == &other_vector) {
        return *this;
    }

    // deallocate existing memory
    array.reset(nullptr);

    // move the memory of other object to this object
    array = std::move_if_noexcept(other_vector.array);
    m_size = other_vector.m_size;
    m_capacity = other_vector.m_capacity;

    // leave the moved object in valid
    other_vector.m_capacity = 0;
    other_vector.m_size = 0;

    return *this;
}

// internal function that will double m_capacity when vector is full by default
// or increase to the desired capacity
template <typename T>
void Myvector<T>::reallocation(int new_capacity) {
    // 1. Acquire new memory
    if (new_capacity == -1) {
        m_capacity = m_capacity * 2;
    } else {
        m_capacity = new_capacity * 2;
    }

    // allocate new memory
    std::unique_ptr<T[]> new_array(new T[m_capacity]);

    // 2. copy over from old memory to new memory
    std::copy_n(array.get(), m_size, new_array.get());

    // 3. deallocate old memory + acquire new memory
    array = std::move_if_noexcept(new_array);
    return;
}

template <typename T>
void Myvector<T>::push_back(T value) {
    if (m_size == m_capacity) {
        reallocation();
    }

    array[static_cast<std::size_t>(m_size)] = value;
    m_size++;
    return;
}

template <typename T>
void Myvector<T>::pop_back() {
    // if not empty
    if (m_size > 0) {
        // reduce m_size so the other elements are not accessible
        --m_size;
    }
    return;
}

// overload sucript operator [] --> always return a reference to element
template <typename T>
T& Myvector<T>::operator[](int index) {
    // no bound checking done, ibdexing out of bound causes undefined behaviour
    return array[static_cast<std::size_t>(index)];
}

// overload const subscript operator [] --> always return a reference to element
template <typename T>
const T& Myvector<T>::operator[](int index) const {
    // no bound checking done, ibdexing out of bound causes undefined behaviour
    return array[static_cast<std::size_t>(index)];
}

// at() to index and perform bound check
template <typename T>
T& Myvector<T>::at(int index) {
    if (index >= m_size) {
        throw std::out_of_range("Index out of bounds");
    }
    return array[static_cast<std::size_t>(index)];
}

// at() to index and perform bound check
template <typename T>
const T& Myvector<T>::at(int index) const {
    if (index >= m_size) {
        throw std::out_of_range("Index out of bounds");
    }
    return array[static_cast<std::size_t>(index)];
}

// check if vector is empty
template <typename T>
bool Myvector<T>::empty() {
    if (m_size == 0) {
        return true;
    }
    return false;
}

// data() --> to get underlying pointer to dynamically allocated array
template <typename T>
T* Myvector<T>::data() {
    return array.get();
}

template <typename T>
void Myvector<T>::resize(int size, T val) // value initialise T val
{
    if (size < m_size) {
        // move the top of stack lower so shrink the vector, capacity doesn't change
        m_size = size;
    }

    else if (size > m_size) {
        // reallocating to ensure future push back has space
        if (size >= m_capacity) {
            reallocation(size);
        }

        for (int i = m_size; i < size; i++) {
            array[static_cast<std::size_t>(i)] = val;
        }
        // update m_size after expanding the array
        m_size = size;
    }
    return;
}

template <typename T>
void Myvector<T>::reserve(int new_capacity) {
    if (new_capacity > m_capacity) {
        reallocation(new_capacity);
    }
    return;
}

} // namespace datastructs

#endif
