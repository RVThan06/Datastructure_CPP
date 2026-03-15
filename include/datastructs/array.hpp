#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <stdexcept>

namespace datastructs {

/**
 * @brief A template class for array data structure.
 * This a class is a static array implementation replicating std::array from
 * C++ standard template library.
 * @tparam T is the type of the data stored by the underlying datastructure.
 * @tparam N is the size of array.
 */
template <typename T, std::size_t N>
class MyArray {
    /// @brief compile time check for template parameters
    static_assert(N >= 0, "Array dimension must be larger than 0");

public:
    /**
     * @brief default constructor
     * Initialises an array of size N and default initialises each
     * array element with the deafult value of type T.
     */
    MyArray() {
        T val{};
        std::fill_n(array, m_size, val);
    }

    /**
     * @brief Copy constructor.
     * @param other_array, array object to copy from.
     */
    MyArray(const MyArray& other_array) { std::copy_n(other_array.array, m_size, array); }

    /**
     * @brief Move constructor.
     * * Performs element wise move semantic to move the the stored object pointer instead of moving
     *  the memroy of the array itself as array memory on stack cannot be moved.
     * @note Complexity: O(n) since n number of moves must be performed.
     * @param other_array array object to move resource from.
     */
    MyArray(MyArray&& other_array) noexcept {
        // element wise move semantics
        for (std::size_t i = 0; i < m_size; i++) {
            array[i] = std::move_if_noexcept(other_array.array[i]);
        }
    }

    /**
     * @brief List constructor.
     * * Initialises a an array using initilizer list by copying all the values in it.
     * @param lst, std::initializer list object.
     * @throws std::out_of_range, if initializer list is not equal to array
     */
    MyArray(std::initializer_list<T> lst) {
        if (lst.size() != N) {
            throw std::out_of_range("List size not equal to array.\n");
        }
        std::copy_n(lst.begin(), m_size, array);
    }

    /**
     * @brief Copy assignment.
     * @param other_array, array object to copy from.
     */
    MyArray& operator=(const MyArray& other_array) {
        if (&other_array == this) {
            return *this;
        }

        std::copy_n(other_array.array, m_size, array);

        return *this;
    }
    /**
     * @brief Move assignment.
     * * Performs element wise moving of underlying array element pointers.
     * @note Does not move the array memery since array is on stack.
     * @param other_array array object to move resource from.
     */
    MyArray& operator=(MyArray&& other_array) noexcept {
        if (&other_array == this) {
            return *this;
        }

        for (std::size_t i = 0; i < m_size; i++) {
            array[i] = std::move_if_noexcept(other_array.array[i]);
        }

        return *this;
    }

    /**
     * @brief Subscript operator overload to retrieve data stored
     * in a given index of the array.
     * @returns reference to the data stored.
     * @warning // no bound checking done, indexing out of bound causes undefined behaviour
     */
    T& operator[](std::size_t index) { return array[index]; }
    const T& operator[](std::size_t index) const { return array[index]; }

    /**
     * @brief at() fucntion to retrieve data stored at an index.
     * @returns reference to the data stored.
     * @throws std::out_of_range when index is out of array bounds.
     */
    T& at(std::size_t index) {
        if (index >= m_size) {
            throw std::out_of_range("Index is beyond range of array\n");
        }

        return array[index];
    }

    const T& at(std::size_t index) const {
        if (index >= m_size) {
            throw std::out_of_range("Index is beyond range of array\n");
        }

        return array[index];
    }

    /**
     * @brief returns a reference to the first element in array
     * @note returns constant reference for const objects
     */
    T& front() { return array[0]; }
    const T& front() const { return array[0]; }

    /**
     * @brief returns a reference to the last array element
     * @note returns a const reference for constant objects
     */
    T& back() { return array[m_size - 1]; }
    const T& back() const { return array[m_size - 1]; }

    /**
     * @brief function to return pointer to underlying array in memeory.
     * Allows for direct access to data array in memory.
     * @note returns a constant pointer for constant objects.
     */
    T* data() { return &array[0]; }
    const T* data() const { return &array[0]; }

    /**
     * @brief function to return array size
     * @return returns a number of type std::size_t
     */
    std::size_t size() const { return N; }

    /**
     * @brief To check if array is empty.
     * @return boolean data, true if list is empty, false if otherwise.
     */
    bool empty() const { return N == 0; }

    /**
     * @brief To fill array with a given value.
     * @param val, the value to be used to fill the array.
     */
    void fill(const T& val) { std::fill_n(array, m_size, val); }

    /**
     * @brief Fucntion to swap the content of one array with another.
     * @param other_array, a reference to the array to swap with.
     */
    void swap(MyArray& other_array) { std::swap_ranges(array, array + N, other_array.array); }

    /**
     * @brief equality operator overload to compare two array.
     * * this function performs element-wise comparison between two arrays.
     */
    friend bool operator==(const MyArray& array1, const MyArray& array2) {
        bool equal = std::equal(std::begin(array1.array), std::end(array1.array), std::begin(array2.array));
        return equal;
    }

    /// @brief Ostream overload for printing of array
    friend std::ostream& operator<<(std::ostream& out, const MyArray& arr) {
        for (std::size_t i = 0; i < arr.m_size; i++) {
            out << arr.array[i] << " ";
        }
        out << "\n";

        return out;
    }

    /**
     * @brief iterator class for array
     * This is a contiguous iterator.
     */
    template <typename U>
    class ArrayIterator {
    public:
        using value_type = std::remove_const_t<U>; // remove const since value type is always non-const, just T
        using difference_type = std::ptrdiff_t;
        using pointer = U*;
        using reference = U&;
        using iterator_category = std::contiguous_iterator_tag;

        explicit ArrayIterator(U* current_ptr) : current{current_ptr} {}

        // dereference
        reference operator*() const { return *current; }
        pointer operator->() const { return current; } // returns pointer to element

        // subscript --> random access
        reference operator[](difference_type index) { return current[index]; }

        // increment / decrement
        ArrayIterator& operator++() {
            ++current;
            return *this;
        }
        ArrayIterator operator++(int) {
            ArrayIterator temp = *this;
            ++(*this);
            return temp;
        }
        ArrayIterator& operator--() {
            --current;
            return *this;
        }
        ArrayIterator operator--(int) {
            ArrayIterator temp = *this;
            --(*this);
            return temp;
        }

        // Addition / Subtraction
        ArrayIterator operator+(difference_type n) const { return ArrayIterator(current + n); }
        ArrayIterator operator-(difference_type n) const { return ArrayIterator(current - n); }

        // Distance between iterator
        difference_type operator-(const ArrayIterator& other_iterator) const {
            return current - other_iterator.current;
        }

        // compound assignment
        ArrayIterator& operator+=(difference_type n) {
            current += n;
            return *this;
        }
        ArrayIterator& operator-=(difference_type n) {
            current -= n;
            return *this;
        }

        // comparisons
        bool operator==(const ArrayIterator& other_iterator) const { return current == other_iterator.current; }
        bool operator!=(const ArrayIterator& other_iterator) const { return current != other_iterator.current; }
        bool operator>(const ArrayIterator& other_iterator) const { return current > other_iterator.current; }
        bool operator<(const ArrayIterator& other_iterator) const { return current < other_iterator.current; }
        bool operator>=(const ArrayIterator& other_iterator) const { return current >= other_iterator.current; }
        bool operator<=(const ArrayIterator& other_iterator) const { return current <= other_iterator.current; }

    private:
        pointer current;
    };

    /// @brief Iterator type aliases
    using iterator = ArrayIterator<T>;
    using const_iterator = ArrayIterator<const T>;

    iterator begin() { return iterator(array); }
    const_iterator begin() const { return const_iterator(array); }

    iterator end() { return iterator(array + m_size); }
    const_iterator end() const { return const_iterator(array + m_size); }

    const_iterator cbegin() const { return const_iterator(array); }
    const_iterator cend() const { return const_iterator(array + m_size); }

private:
    std::size_t m_size{N};
    T array[N];
};

/**
 * @brief template specialisation for N = 0
 * * This allows for the creation of array with size 0 safely,
 * Allows for safe iteration of empty array.
 */
template <typename T>
class MyArray<T, 0> {
    template <typename U>
    class ArrayIterator {
    public:
        using value_type = std::remove_const_t<U>; // remove const since value type is always non-const, just T
        using difference_type = std::ptrdiff_t;
        using pointer = U*;
        using reference = U&;
        using iterator_category = std::random_access_iterator_tag;

        explicit ArrayIterator(U* current_ptr) : current{current_ptr} {}

        // dereference
        reference operator*() const { return *current; }
        pointer operator->() const { return current; }

        // subscript --> random access
        reference operator[](difference_type index) { return current[index]; }

        // increment / decrement
        ArrayIterator& operator++() {
            ++current;
            return *this;
        }
        ArrayIterator operator++(int) {
            ArrayIterator temp = *this;
            ++(*this);
            return temp;
        }
        ArrayIterator& operator--() {
            --current;
            return *this;
        }
        ArrayIterator operator--(int) {
            ArrayIterator temp = *this;
            --(*this);
            return temp;
        }

        // Addition / Subtraction
        ArrayIterator operator+(difference_type n) const { return ArrayIterator(current + n); }
        ArrayIterator operator-(difference_type n) const { return ArrayIterator(current - n); }

        // Distance between iterator
        difference_type operator-(const ArrayIterator& other_iterator) const {
            return current - other_iterator.current;
        }

        // compound assignment
        ArrayIterator& operator+=(difference_type n) {
            current += n;
            return *this;
        }
        ArrayIterator& operator-=(difference_type n) {
            current -= n;
            return *this;
        }

        // comparisons
        bool operator==(const ArrayIterator& other_iterator) const { return current == other_iterator.current; }
        bool operator!=(const ArrayIterator& other_iterator) const { return current != other_iterator.current; }
        bool operator>(const ArrayIterator& other_iterator) const { return current > other_iterator.current; }
        bool operator<(const ArrayIterator& other_iterator) const { return current < other_iterator.current; }
        bool operator>=(const ArrayIterator& other_iterator) const { return current >= other_iterator.current; }
        bool operator<=(const ArrayIterator& other_iterator) const { return current <= other_iterator.current; }

    private:
        pointer current;
    };

    using iterator = ArrayIterator<T>;
    using const_iterator = ArrayIterator<const T>;

public:
    iterator begin() { return iterator(nullptr); }
    const_iterator begin() const { return const_iterator(nullptr); }

    iterator end() { return iterator(nullptr); }
    const_iterator end() const { return const_iterator(nullptr); }

    const_iterator cbegin() const { return const_iterator(nullptr); }
    const_iterator cend() const { return const_iterator(nullptr); }

    bool empty() const { return true; }
    std::size_t size() const { return 0; }
};
} // namespace datastructs

#endif
