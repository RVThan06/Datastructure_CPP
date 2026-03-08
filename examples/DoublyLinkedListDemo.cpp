#include <algorithm>
#include <array>
#include <datastructs/doubly_linked_list.hpp>
#include <iostream>

int main() {
    /****************************************************************************************************
     * DOUBLY LINKED LIST DEMO                                                                         **
     * **************************************************************************************************
     */

    // --- List Initialisation --------------------------------------------------------------------------

    // 1. Create a list using insert_front()
    std::array primes{2, 3, 5, 7, 11};
    datastructs::DLinkedList<int> prime_numbers;

    for (const auto& val : primes) {
        prime_numbers.insert_front(val);
    }
    std::cout << "Prime numbers: " << prime_numbers << " lenght: " << prime_numbers.length() << "\n\n";

    // 2. Create a list using insert_rear()
    std::array evens{2, 4, 6, 8, 10, 12};
    datastructs::DLinkedList<int> even_numbers;

    for (const auto& val : evens) {
        even_numbers.insert_rear(val);
    }
    std::cout << "Even numbers: " << even_numbers << " lenght: " << even_numbers.length() << "\n\n";

    // --- Copy semantics -------------------------------------------------------------------------------

    // 1. Copy constructor
    datastructs::DLinkedList<int> even_numbers_2(even_numbers);
    std::cout << "Even numbers_2 copy constructed: " << even_numbers_2 << "\n\n";

    // 2. Copy assignment
    std::array evens_2{20, 40, 60, 80, 100};
    datastructs::DLinkedList<int> even_numbers_3;

    for (const auto& val : evens_2) {
        even_numbers_3.insert_rear(val);
    }
    even_numbers_2 = even_numbers_3;
    std::cout << "Even numbers_3 copy assigned: " << even_numbers_2 << "\n\n";

    // ---  Move semantics ------------------------------------------------------------------------------

    // 1. Move constructor
    datastructs::DLinkedList<int> prime_numbers_2 = std::move_if_noexcept(prime_numbers);
    std::cout << "Prime numbers_2 is move constructed: " << prime_numbers_2 << "\n";
    std::cout << "Prime numbers: " << prime_numbers << "\n\n"; // empty list

    // 2. Move assignement
    prime_numbers = std::move_if_noexcept(prime_numbers_2);
    std::cout << "Prime numbers is move assigned again: " << prime_numbers << "\n";
    std::cout << "Prime numbers_2: " << prime_numbers_2 << "\n\n"; // empty list

    // --- List constructor using initialiser list ---
    std::cout << "Odd numbers is list initialised: ";
    datastructs::DLinkedList<int> odd_numbers{1, 3, 5, 7, 9};
    std::cout << odd_numbers << "\n\n";

    // --- List Operations ------------------------------------------------------------------------------

    // 1. search for a given node
    if (!odd_numbers.is_empty()) {
        auto result = odd_numbers.search(3);
        if (result) {
            std::cout << "Node " << result.value() << " found \n";
        }
    }

    // 2. delete node using delete_front()
    odd_numbers.delete_front();
    std::cout << "Odd numbers after front deletion: " << odd_numbers << "\n";
    std::cout << "Odd numbers length is: " << odd_numbers.length() << "\n\n";

    // 3. delete entire list
    int odd_length = odd_numbers.length();
    for (int i = 0; i < odd_length; i++) {
        odd_numbers.delete_rear();
    }
    std::cout << "Odd numbers after back deletion: " << odd_numbers << "\n";
    std::cout << "Odd numbers length is: " << odd_numbers.length() << "\n\n";

    // --- Custom Iterators Usage -----------------------------------------------------------------------

    // 1. For-each loop
    for (const auto& val : even_numbers) {
        std::cout << val << "-->";
    }
    std::cout << "\n\n";

    // 2. Reverse iteration
    for (auto pos = even_numbers.rbegin(); pos != even_numbers.rend(); --pos) {
        std::cout << *pos << "-->";
    }
    std::cout << "\n\n";

    // --- Doubly Linked List + STL algorithms (via custom iterators) ------------------------------------------

    std::array positions{1, 2, 3, 4, 5};
    std::array zeros{0, 0, 0, 0, 0};
    datastructs::DLinkedList<int> sample_1;
    datastructs::DLinkedList<int> sample_2;

    for (const auto& val : positions) {
        sample_1.insert_rear(val);
    }

    for (const auto& val : zeros) {
        sample_2.insert_rear(val);
    }

    // 1. std::copy
    std::copy(sample_1.begin(), sample_1.end(), sample_2.begin());
    std::cout << "Sample 1: " << sample_1 << "\n";
    std::cout << "Sample 2: " << sample_2 << "\n\n";

    // 2. std::copy_if
    auto is_even = [](int x) { return x % 2 == 0; };
    std::copy_if(even_numbers_2.begin(), even_numbers_2.end(), sample_2.begin(), is_even);
    std::cout << "Sample 2: " << sample_2 << "\n\n";

    // 3. std::fill
    std::fill(sample_1.begin(), sample_1.end(), -10);
    std::cout << "Sample 1: " << sample_1 << "\n\n";

    // 4. std::for_each
    auto multiply_2 = [](int& x) { x = x * 2; };
    std::for_each(sample_2.begin(), sample_2.end(), multiply_2);
    std::cout << "Sample 2: " << sample_2 << "\n\n";

    // 5. std::find
    auto it_2 = std::find(sample_2.begin(), sample_2.end(), 160);
    if (it_2 != sample_2.end()) {
        std::cout << "Value: " << *it_2 << " found in Sample 2\n\n";
    } else {
        std::cout << "Value not found\n";
    }

    return 0;
}
