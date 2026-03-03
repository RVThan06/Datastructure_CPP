#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <stdexcept>

namespace datastructs {
template <typename T, std::size_t N>
class MyArray {
public:
    MyArray() {
        T val{};
        std::fill_n(array, m_size, val);
    }

    MyArray(const MyArray& other_array) {
        if (other_array.m_size != N) {
            throw std::out_of_range("Array size mismatch\n");
        }

        std::copy_n(other_array.array, m_size, array);
    }

    MyArray(const MyArray&& other_array) noexcept {
        if (other_array.m_size != N) {
            throw std::out_of_range("Array size mismatch\n");
        }

        // element wise move semantics
        for (std::size_t i = 0; i < m_size; i++) {
            array[i] = std::move_if_noexcept(other_array.array[i]);
        }
    }

    MyArray(std::initializer_list<T> lst) {
        if (lst.size() > N) {
            throw std::out_of_range("List is larger thatn array size\n");
        }
        std::copy_n(lst.begin(), m_size, array);
    }

    MyArray& operator=(const MyArray& other_array) {
        if (&other_array == this) {
            return *this;
        }

        if (other_array.m_size != N) {
            throw std::out_of_range("Array size mismatch\n");
        }

        std::copy_n(other_array.array, m_size, array);

        return *this;
    }

    MyArray& operator=(const MyArray&& other_array) noexcept {
        if (&other_array == this) {
            return *this;
        }

        if (other_array.m_size != N) {
            throw std::out_of_range("Array size mismatch\n");
        }

        for (std::size_t i = 0; i < m_size; i++) {
            array[i] = std::move_if_noexcept(other_array.array[i]);
        }

        return *this;
    }

    T& operator[](std::size_t index) { return array[index]; }

    const T& operator[](std::size_t index) const { return array[index]; }

    T& at(std::size_t index) {
        if (index < 0 || index >= m_size) {
            throw std::out_of_range("Index is beyond range of array\n");
        }

        return array[index];
    }

    const T& at(std::size_t index) const {
        if (index < 0 || index >= m_size) {
            throw std::out_of_range("Index is beyond range of array\n");
        }

        return array[index];
    }

    // front reference
    T& front() { return array[0]; }
    const T& front() const { return array[0]; }

    // back reference
    T& back() { return array[m_size - 1]; }
    const T& back() const { return array[m_size - 1]; }

    // internal data pointer
    T* data() { return &array[0]; }
    const T* data() const { return &array[0]; }

    std::size_t size() const { return N; }
    bool empty() const { return N == 0; }
    void fill(const T& val) { std::fill_n(array, m_size, val); }
    void swap(MyArray& other_array) { std::swap_ranges(array, array + N, other_array.array); }

    friend bool operator==(const MyArray& array1, const MyArray& array2) {
        bool equal = std::equal(std::begin(array1.array), std::end(array1.array), std::begin(array2.array));
        return equal;
    }

    friend std::ostream& operator<<(std::ostream& out, const MyArray& arr) {
        for (std::size_t i = 0; i < arr.m_size; i++) {
            out << arr.array[i] << " ";
        }
        out << "\n";

        return out;
    }

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

// template specialisation for N=0
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
