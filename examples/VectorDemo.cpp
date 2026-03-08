#include <datastructs/vector.hpp>
#include <iostream>

// non-member function
// create function template to use class template in it
// primary function template
// to demo how class template can be a return type
template <typename T>
datastructs::Myvector<T> create_vector() {
    datastructs::Myvector<T> vector1;
    return vector1;
}

// non-member function
// specialised function template --> not implicitly inline
// function template to create a class using class template, only for int
template <>
inline datastructs::Myvector<int> create_vector() {
    datastructs::Myvector<int> vector1;
    for (int i = 5; i < 10; i++) {
        vector1.push_back(i);
    }
    // returning automatic l-value compiler will elide it
    return vector1;
}

int main() {
    /****************************************************************************************************
     * VECTOR DEMO                                                                                     **
     * **************************************************************************************************
     */

    // --- Vector Initialisation --------------------------------------------------------------------------

    datastructs::Myvector<int> vector1;
    std::cout << "Vector 1 m_capacity: " << vector1.get_capacity() << "\n";
    std::cout << "Vector 1 m_size: " << vector1.get_size() << "\n\n";
    for (int i = 0; i < 5; i++) {
        vector1.push_back(i);
    }
    std::cout << "Vector 1 (adding elements) .........\n\n";
    std::cout << "Vector 1 m_capacity: " << vector1.get_capacity() << "\n";
    std::cout << "Vector 1 m_size: " << vector1.get_size() << "\n";
    std::cout << "Vector 1: " << vector1 << std::endl;
    std::cout << "\n\n";

    // --- Copy semantics -------------------------------------------------------------------------------

    // 1. Copy assignment
    datastructs::Myvector<int> vector2;
    vector2 = vector1;
    std::cout << "(Copy assignment) Vector 1 --> Vector 2\n";
    std::cout << "Vector 2: " << vector2 << std::endl;
    std::cout << "\n\n";

    // 2. Copy constructor
    std::cout << "(Copy constructor) Vector 1 --> vector 3\n";
    datastructs::Myvector<int> vector3(vector2);
    std::cout << "Vector 3: " << vector3 << std::endl;
    std::cout << "\n\n";

    // ---  Move semantics ------------------------------------------------------------------------------

    // 1. Move constructor
    datastructs::Myvector<int> vector4(std::move_if_noexcept(vector3));
    std::cout << "(Move constructor) Vector 3 --> Vector 4\n";
    std::cout << "Vector 4: " << vector4 << std::endl;
    std::cout << "\n\n";

    // calling create vector function directly in the constructor will not invoke move constructor
    // since compiler will optimise and use elision to directly create the object instead of returning a temporary
    // object
    datastructs::Myvector<int> vector5(create_vector<int>());
    std::cout << "Vector 5 --> created by eliding copy\n";
    std::cout << "Vector 5: " << vector5 << std::endl;
    std::cout << "\n\n";

    // 2. Move assignment
    datastructs::Myvector<int> vector6;
    vector6 = std::move_if_noexcept(vector5);
    std::cout << "(Move assignment) vector 5 --> Vector 6\n";
    std::cout << "Vector 6: " << vector6 << std::endl;
    std::cout << "Vector 5: (Empty) " << vector5 << "\n";
    std::cout << "Vector 5 m_size: " << vector5.get_size() << "\n";
    std::cout << "\n\n";

    // --- Vector Operations ------------------------------------------------------------------------------

    // 1.Resizing of vector
    std::cout << "Vector 6 m_capacity (initial): " << vector6.get_capacity() << "\n";
    std::cout << "Vector 6 m_size (initial): " << vector6.get_size() << "\n\n";
    vector6.resize(10, 20);
    std::cout << "Vector 6 (Resizing) .........\n\n";
    std::cout << "Vector 6 m_capacity (new): " << vector6.get_capacity() << "\n";
    std::cout << "Vector 6 m_size (new): " << vector6.get_size() << "\n";
    std::cout << "Vector 6: (trailing 20s): " << vector6 << "\n\n\n";

    // 2. Reserving capacity
    vector6.reserve(25);
    std::cout << "Vector 6 (Reserving capacity) .........\n";
    std::cout << "Vector 6 m_capacity (new): " << vector6.get_capacity() << "\n";
    std::cout << "Vector 6 m_size (new): " << vector6.get_size() << "\n";
    std::cout << "Vector 6: " << vector6 << "\n";
    std::cout << "\n\n";

    // --- List constructor ------------------------------------------------------------------------------
    std::cout << "(List constructor) --> Vector 8\n";
    datastructs::Myvector<int> vector8{1, 2, 3, 4, 5};
    std::cout << "Vector 1 m_capacity: " << vector8.get_capacity() << "\n";
    std::cout << "Vector 1 m_size: " << vector8.get_size() << "\n";
    std::cout << "Vector 8: " << vector8 << "\n";
    std::cout << "\n\n";

    // list assignment --> move constructor invoked
    std::cout << "List assigning to vector 8, will convert list to a temp obj and use move assigment. \n";
    vector8 = {5, 6, 7, 8, 9};
    std::cout << "Printing vector 8: " << vector8 << "\n\n\n";

    // --- Custom Iterators Usage -----------------------------------------------------------------------

    // 1. For-each loop
    std::cout << "(Custom iterator) --> Vector 1 for-each loop\n";
    for (auto val : vector1) {
        std::cout << val << " -> ";
    }
    std::cout << "\n\n\n";

    const datastructs::Myvector vector1_1 = vector1;
    for (const auto& val : vector1_1) {
        std::cout << val << " -> ";
    }
    std::cout << "\n\n\n";

    // --- Vector + STL algorithms (via custom iterators) ------------------------------------------

    datastructs::Myvector sample_1{1, 2, 3, 4, 5};
    datastructs::Myvector sample_2{0, 0, 0, 0, 0};
    datastructs::Myvector sample_3{0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    datastructs::Myvector even_numbers{2, 4, 6};

    // 1. std::copy
    std::copy(sample_1.begin(), sample_1.end(), sample_2.begin());
    std::cout << "Sample 1: " << sample_1 << "\n";
    std::cout << "Sample 2: " << sample_2 << "\n\n";

    // 2. std::copy_if
    auto is_even = [](int x) { return x % 2 == 0; };
    std::copy_if(even_numbers.begin(), even_numbers.end(), sample_2.begin(), is_even);
    std::cout << "Sample 2: " << sample_2 << "\n\n";

    // 3. std::fill
    std::fill(sample_1.begin(), sample_1.end(), -10);
    std::cout << "Sample 1: " << sample_1 << "\n\n";

    // std::for_each
    auto multiply_2 = [](int& x) { x = x * 2; };
    std::for_each(sample_2.begin(), sample_2.end(), multiply_2);
    std::cout << "Sample 2: " << sample_2 << "\n\n";

    // 4. std::find
    auto it_2 = std::find(sample_2.begin(), sample_2.end(), 12);
    if (it_2 != sample_2.end()) {
        std::cout << "Value: " << *it_2 << " found in Sample 2\n\n";
    } else {
        std::cout << "Value not found\n";
    }

    // 5. std::copy_backward
    std::copy_backward(sample_2.begin(), sample_2.end(), sample_3.end());
    std::cout << "Sample 3: " << sample_3 << "\n\n";

    // --- Contiguous Iterator demo ---------------------------------------------------------------------

    auto it_1 = sample_2.begin();
    std::cout << "Sample 2, 1st item: " << *it_1 << "\n";

    it_1 = it_1 + 1;
    std::cout << "Sample 2, 2nd item: " << *it_1 << "\n";

    it_1++;
    std::cout << "Sample 2, 3rd item: " << *it_1 << "\n";

    it_1 = sample_2.begin();
    it_1 += 3;
    std::cout << "Sample 2, 4th item: " << *it_1 << "\n";

    auto it_3 = sample_2.end();
    std::cout << "Sample 2, last item: " << *(it_3 - 1) << "\n";

    it_3--;
    it_3--;
    std::cout << "Sample 2, second last item: " << *it_3 << "\n";

    it_3 = sample_2.end();
    std::cout << "Sample 2, 1st item: " << it_3[-5] << "\n";

    it_3 = sample_2.begin();
    std::cout << "Sample 2, 3rd item: " << it_3[2] << "\n";

    return 0;
}
