# DataStructs

> 🚧 **Work in Progress:** The core header files and usage examples are fully implemented. Comprehensive unit testing (via GoogleTest) is currently under active development.

## Overview

DataStructs is a modern, header-only C++20 data structures library. The primary goal of this project is to provide clean, efficient, and standard-compliant implementations of fundamental data structures.

Built with modern C++ paradigms in mind, the library leverages C++20 features and is strictly validated against rigorous compiler warnings to ensure memory safety and robust performance.

## Features

### Architecture & Tooling
* **Header-Only Design:** No separate compilation step is required. Simply link the library via CMake and `#include` the necessary headers.
* **Strict Quality Controls:** Configured to compile cleanly under stringent compiler warnings (e.g., `-Wall`, `-Wextra`, `-Wpedantic`, `-Wconversion` for GCC/Clang, and `/W4` for MSVC) to guarantee memory safety.
* **Standardized Layout:** Adheres to the Pitchfork project layout for predictable, professional directory organization.

### Modern C++ Implementations
* **Robust Resource Management (RAII):** Utilizes `std::unique_ptr` under the hood for dynamic memory allocations, ensuring automatic, leak-free cleanup and strong exception safety.
* **Optimized Copy & Move Semantics:** Fully implements the Rule of Five. Containers support deep copying for data integrity and highly efficient move constructors/assignment operators for zero-allocation data transfers.
* **STL-Compatible Iterators:** Containers feature custom iterators, allowing them to plug seamlessly into range-based `for` loops and standard library algorithms (e.g., `std::find`, `std::sort` from `<algorithm>`).
* **Ergonomic Initialization:** Includes `std::initializer_list` constructors for the Vector, Array, and Linked List, enabling clean, brace-enclosed instantiation (e.g., `datastructs::Myvector<int> vec = {1, 2, 3, 4};`).

## Implemented Data Structures

The library currently provides the following containers within the `datastructs::` namespace:

* **Array** (`<datastructs/array.hpp>`)
* **Vector** (`<datastructs/vector.hpp>`)
* **Stack** (`<datastructs/stack.hpp>`)
* **Queue** (`<datastructs/queue.hpp>`)
* **Heap** (`<datastructs/heap.hpp>`)
* **Binary Search Tree (BST)** (`<datastructs/binary_search_tree.hpp>`)
* **Singly linked list** (`<datastructs/singly_linked_list.hpp>`)
* **Doubly linked list** (`<datastructs/doubly_linked_list.hpp>`)

### 💻 Quick Start (Implementation)

```
#include <iostream>
#include <array>
#include <datastructs/vector.hpp>
#include <datastructs/linkedlist.hpp>

int main() {
    // --- Vector Example ---
    std::cout << "--- Myvector Quick Start ---\n";
    datastructs::Myvector<float> vector1;

    for (int i = 0; i < 5; i++) {
        vector1.push_back(i + 0.5f);
    }

    std::cout << "Vector Capacity: " << vector1.get_capacity() << "\n";
    std::cout << "Vector Size: " << vector1.get_size() << "\n\n";

    // --- Singly Linked List Example ---
    std::cout << "--- Singly Linked List Quick Start ---\n";
    std::array primes{2, 3, 5, 7, 11};
    datastructs::LinkedList<int> prime_numbers;

    // insert_front pushes elements to the head, reversing the order
    for (const auto& val : primes) {
        prime_numbers.insert_front(val);
    }

    std::cout << "Prime numbers (LIFO order): " << prime_numbers << "\n";

    return 0;
}
```

### Quick Start (STL algorithm via custom Iterator)
```
#include <iostream>
#include <array>
#include <datastructs/linkedlist.hpp>

int main() {

    datastructs::LinkedList<int> sample_1 {1, 2, 3, 4, 5};
    datastructs::LinkedList<int> sample_2 {0, 0, 0, 0, 0};

    // 1. std::copy
    std::copy(sample_1.begin(), sample_1.end(), sample_2.begin());
    std::cout << "Sample 1: " << sample_1 << "\n";
    std::cout << "Sample 2: " << sample_2 << "\n\n";

    // 2. std::copy_if
    auto is_even = [](int x) { return x % 2 == 0; };
    std::copy_if(even_numbers_2.begin(), even_numbers_2.end(), sample_2.begin(), is_even);
    std::cout << "Sample 2: " << sample_2 << "\n\n";
    return 0;
}
```

## Integration

Since DataStructs is a CMake `INTERFACE` library, integrating it into your project is straightforward.

1. Clone or copy the `DataStructs` repository into your project (e.g., into an `external/` or `third_party/` directory).
2. In your top-level `CMakeLists.txt`, add the subdirectory and link it to your target:

```cmake
# Add the library to your build
add_subdirectory(external/DataStructs)

# Link it to your executable or library
target_link_libraries(YourTargetName PRIVATE datastructs)

