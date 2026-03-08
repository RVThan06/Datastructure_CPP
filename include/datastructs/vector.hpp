#ifndef MYVECTOR_HPP
#define MYVECTOR_HPP

#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <memory>

namespace datastructs {

/**
 * @brief A template class for vector data structure.
 * This a class of dynamic array that is a replication of std::vector
 * from C++ standard template library.
 * Hwoever, it is not a complete implementation, but i has the major functions to mimic
 * the behaviour of STL vector.
 * @tparam T is the type of the data stored by the underlying datastructure.
 */
template <typename T>
class Myvector {
public:
    /// @brief Constructors and assignment overloads
    Myvector(std::size_t = 0, T = {});
    ~Myvector() {}
    Myvector(std::initializer_list<T>);
    Myvector(const Myvector&);
    Myvector& operator=(const Myvector&);
    Myvector(Myvector&&) noexcept;
    Myvector& operator=(Myvector&&) noexcept;

    // vector functions
    void push_back(T);
    void pop_back();
    T& operator[](std::size_t);
    const T& operator[](std::size_t) const;
    T& at(std::size_t);
    const T& at(std::size_t) const;
    std::size_t get_size() const { return m_size; }
    std::size_t get_capacity() const { return m_capacity; }
    bool empty();
    T* data();
    void resize(std::size_t, T = {}); // value initialised
    void reserve(std::size_t);

    /// @brief Ostream overload for printing of vector
    friend std::ostream& operator<<(std::ostream& out, const Myvector& vector) {
        for (std::size_t i = 0; i < vector.m_size; ++i) {
            out << vector.array[static_cast<std::size_t>(i)] << " ";
        }
        return out;
    }

    /**
     * @brief iterator class for vector
     * This is a contiguous iterator.
     */
    template <typename U>
    class VectorIterator {
    public:
        using value_type = std::remove_const_t<U>;
        using difference_type = std::ptrdiff_t;
        using pointer = U*;
        using reference = U&;
        using iterator_category = std::contiguous_iterator_tag;

        explicit VectorIterator(U* current_ptr) : current{current_ptr} {}

        // Dereference
        reference operator*() const { return *current; }
        pointer operator->() const { return current; }

        // Subscript --> random access
        reference operator[](difference_type index) const { return current[index]; }

        // Increment / Decrement
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

        // Comparisons
        bool operator==(const VectorIterator& other_iterator) const { return current == other_iterator.current; }
        bool operator!=(const VectorIterator& other_iterator) const { return current != other_iterator.current; }
        bool operator>(const VectorIterator& other_iterator) const { return current > other_iterator.current; }
        bool operator<(const VectorIterator& other_iterator) const { return current < other_iterator.current; }
        bool operator>=(const VectorIterator& other_iterator) const { return current >= other_iterator.current; }
        bool operator<=(const VectorIterator& other_iterator) const { return current <= other_iterator.current; }

    private:
        pointer current;
    };

    /// @brief Iterator type aliases
    using iterator = VectorIterator<T>;
    using const_iterator = VectorIterator<const T>;

    iterator begin() { return iterator(array.get()); }
    const_iterator begin() const { return const_iterator(array.get()); }

    iterator end() { return iterator(array.get() + m_size); }
    const_iterator end() const { return const_iterator(array.get() + m_size); }

    const_iterator cbegin() const { return const_iterator(array.get()); }
    const_iterator cend() const { return const_iterator(array.get() + m_size); }

private:
    std::size_t m_capacity;
    std::size_t m_size;
    std::unique_ptr<T[]> array;

protected:
    void reallocation(int = -1);
};

/**
 * @brief Default constructor.
 * By default initialises an empty vector.
 * @param size, the size of vector, the number of elements in it. Default = 0
 * @param val, the value to use to initisalise vector elements if size > 0,if not provided then all elements will
 * be default initialised.
 */
template <typename T>
Myvector<T>::Myvector(std::size_t size, T val)
    : m_capacity{(size + 4)}, m_size{size}, array{std::make_unique<T[]>(size + 4)} {
    for (std::size_t i = 0; i < m_size; ++i) {
        array[static_cast<std::size_t>(i)] = val;
    }
}

/**
 * @brief List constructor.
 * * Initialises a vector using initilizer list by copying all the values in it.
 * @param list, std::initializer list object.
 */
template <typename T>
Myvector<T>::Myvector(std::initializer_list<T> list)
    : m_capacity{list.size() + 4}, m_size{0}, array{std::make_unique<T[]>(list.size() + 4)} {
    // copy values into vector from initialiser list
    for (std::size_t i = 0; i < list.size(); i++) {
        push_back(list.begin()[i]); // begin returns 1st pointer to initialiser list
    }
}

/**
 * @brief Copy constructor.
 * Deep copying is done.
 * @param other_vector, vector object to copy from.
 */
template <typename T>
Myvector<T>::Myvector(const Myvector<T>& other_vector)
    : m_capacity{other_vector.m_capacity}, m_size{other_vector.m_size}, array{std::make_unique<T[]>(m_capacity)} {
    std::copy_n(other_vector.array.get(), m_size, array.get());
}

/**
 * @brief Copy assignment.
 * Deep copying is done.
 * @param other_vector vector object to copy from.
 */
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

/**
 * @brief Move constructor.
 * * Moves resources from another vector object, leaves the moved object in valid state.
 * @param other_vector vector object to move resource from.
 */
template <typename T>
Myvector<T>::Myvector(Myvector<T>&& other_vector) noexcept
    : m_capacity{other_vector.m_capacity},
      m_size{other_vector.m_size},
      array{std::move_if_noexcept(other_vector.array)} {
    // after moving object is left in valid state
    other_vector.m_capacity = 0;
    other_vector.m_size = 0;
}

/**
 * @brief Move assignment.
 * * Moves resources from another vector object, leaves the moved object in valid state.
 * @param other_vector vector object to move resource from.
 */
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

/**
 * @brief Reallaocation function used internally for vector to grow dynamically.
 * Involves allocating new memory that is larger and copying all data from old memory.
 * The old memory is then deallocated and vector now points to this newly allocated memory.
 * @param new_capacity, the new capacity of vector.
 */
template <typename T>
void Myvector<T>::reallocation(int new_capacity) {
    // 1. Acquire new memory
    std::size_t factor = 2;
    if (new_capacity == -1) {
        m_capacity = m_capacity * factor;
    } else {
        m_capacity = static_cast<std::size_t>(new_capacity) * factor;
    }

    // allocate new memory
    std::unique_ptr<T[]> new_array(new T[m_capacity]);

    // 2. copy over from old memory to new memory
    std::copy_n(array.get(), m_size, new_array.get());

    // 3. deallocate old memory + acquire new memory
    array = std::move_if_noexcept(new_array);
    return;
}

/**
 * @brief Push_back function to add new element to the end of vector.
 * Increases the size of vector.
 * Checks if vector is approching its capacity to trigger reallication.
 */
template <typename T>
void Myvector<T>::push_back(T value) {
    if (m_size == m_capacity) {
        reallocation();
    }

    array[static_cast<std::size_t>(m_size)] = value;
    m_size++;
    return;
}

/**
 * @brief pop_back function, used to remove the last element in vector.
 * Reduces the size of vector.
 */
template <typename T>
void Myvector<T>::pop_back() {
    // if not empty
    if (m_size > 0) {
        // reduce m_size so the other elements are not accessible
        --m_size;
    }
    return;
}

/**
 * @brief Subscript operator overload to retrieve data stored
 * in a given index of the vector.
 * @returns reference to the data stored.
 * @warning // no bound checking done, indexing out of bound causes undefined behaviour
 */
template <typename T>
T& Myvector<T>::operator[](std::size_t index) {
    return array[index];
}

/**
 * @brief Indexing operator for const vectors, similar implementation to non-const version.
 * @returns a const reference to the data stored.
 */
template <typename T>
const T& Myvector<T>::operator[](std::size_t index) const {
    return array[index];
}

/**
 * @brief at() fucntion to retrieve data stored at an index.
 * @returns reference to the data stored.
 * @throws std::out_of_range when index is out of vector bounds.
 */
template <typename T>
T& Myvector<T>::at(std::size_t index) {
    if (index >= m_size) {
        throw std::out_of_range("Index out of bounds");
    }
    return array[index];
}

/**
 * @brief similar to non-const at() function.
 * @returns const reference to the data stored.
 * @throws std::out_of_range when index is out of vector bounds.
 */
template <typename T>
const T& Myvector<T>::at(std::size_t index) const {
    if (index >= m_size) {
        throw std::out_of_range("Index out of bounds");
    }
    return array[index];
}

/**
 * @brief To check if vector is empty.
 * @return boolean data, true if list is empty, false if otherwise.
 */
template <typename T>
bool Myvector<T>::empty() {
    if (m_size == 0) {
        return true;
    }
    return false;
}

/**
 * @brief function to return pointer to underlying array in memeory.
 * Allows for direct access to data array in memory.
 */
template <typename T>
T* Myvector<T>::data() {
    return array.get();
}

/**
 * @brief Fucntion to allow user to resize a vector.
 * Changes the size of the vector and trigger reallocation is new size
 * exceeds current capacity.
 * @param size -> new size of the vector
 * @param val, val to use to initialise new items added to vector if size is increased.
 * The new item are default initialised if no val is provided.
 */
template <typename T>
void Myvector<T>::resize(std::size_t size, T val) // value initialise T val
{
    if (size < m_size) {
        // move the top of stack lower so shrink the vector, capacity doesn't change
        m_size = size;
    }

    else if (size > m_size) {
        // reallocating to ensure future push back has space
        if (size >= m_capacity) {
            reallocation(static_cast<int>(size));
        }

        for (std::size_t i = m_size; i < size; ++i) {
            array[i] = val;
        }
        // update m_size after expanding the array
        m_size = size;
    }
    return;
}

/**
 * @brief to increase capacity of vector without affecting its size.
 * Will trigger reallocation, thus is computationally more costly.
 */
template <typename T>
void Myvector<T>::reserve(std::size_t new_capacity) {
    if (new_capacity > m_capacity) {
        reallocation(static_cast<int>(new_capacity));
    }
    return;
}

} // namespace datastructs

#endif
