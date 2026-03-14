#include <algorithm>
#include <datastructs/array.hpp>
#include <initializer_list>
#include <iostream>

int main() {
    /****************************************************************************************************
     * Array DEMO                                                                                      **
     * **************************************************************************************************
     */

    // --- Array Initialisation --------------------------------------------------------------------------

    datastructs::MyArray<int, 4> prime{2, 3, 5, 7};
    std::cout << prime;

    // --- Copy semantics -------------------------------------------------------------------------------

    // 1. Copy construction
    const datastructs::MyArray prime_2 = prime;
    std::cout << prime_2;
    std::cout << "Index 0: " << prime_2.front() << "\n";
    std::cout << "Index 1: " << prime_2.at(1) << "\n";
    std::cout << "Last element: " << prime_2.back() << "\n\n";

    // 2. List construction
    datastructs::MyArray<int, 4> prime_3{11, 13, 17, 19};
    std::cout << prime_3;

    // 3. Copy assignment
    prime_3 = prime;
    std::cout << prime_3;

    // ---  Move semantics ------------------------------------------------------------------------------

    datastructs::MyArray<int, 3> numbers{1, 2, 3};
    std::cout << numbers;

    // 1. Move construction
    datastructs::MyArray numbers_2(std::move_if_noexcept(numbers));
    std::cout << numbers_2;

    // 2. Move assignment
    numbers_2 = std::move_if_noexcept(numbers);
    std::cout << numbers_2;

    // --- Array Operations ------------------------------------------------------------------------------

    // 1. data() --> access underlying array
    std::cout << "Pointer arithmetic using underlying array\n";
    const int* ptr = prime_2.data();
    std::cout << "Index 0: " << *ptr << "\n";
    ptr += 1;
    std::cout << "Index 1: " << *ptr << "\n\n";

    // 2. size() - returns capacity of array
    std::cout << "Size of numbers_2: " << numbers_2.size() << "\n";

    // 3. empty() - ro check if its empty
    std::cout << std::boolalpha << numbers_2.empty() << "\n";

    // 4. fill() - to fill entire array with value 1
    numbers_2.fill(1);
    std::cout << numbers_2 << "\n";

    // 5. swap() - to enable swapping of two arrays
    numbers_2.swap(numbers);
    std::cout << numbers_2 << "\n";
    std::cout << numbers << "\n";
    std::cout << (numbers == numbers_2) << "\n";

    // --- Custom Iterators Usage -----------------------------------------------------------------------

    // 1. for-each loop
    for (const auto& val : prime_2) {
        std::cout << val << "\n";
    }
    std::cout << "\n";

    // 2. iterator usage
    auto itr = prime_2.begin();      // iterator itself is not constant --> only underlying pointer is
    std::cout << *(itr + 2) << "\n"; // 5
    std::cout << prime_2[2] << "\n"; // 5

    // --- Array + STL algorithms (via custom iterators) ------------------------------------------------

    // 1. std::copy_n
    datastructs::MyArray<int, 4> sample_1;
    std::copy_n(prime_2.begin(), 4, sample_1.begin());
    std::cout << sample_1;

    // 2. std::for_each
    auto multiply_2 = [](int& x) { x = x * 2; };
    std::for_each(sample_1.begin(), sample_1.end(), multiply_2);
    std::cout << "Sample 2: " << sample_1;

    // --- Empty array instantiation (Calls specialsied template) ---------------------------------------

    datastructs::MyArray<int, 0> empty_array;
    std::cout << "Size: " << empty_array.size() << "\n";

    for (auto& val : empty_array) {
        std::cout << val << "\n";
    }

    return 0;
}
