# DataStructs

> 🚧 **Work in Progress:** The core header files for the data structures are implemented and functional. Comprehensive unit testing (via GoogleTest) and usage examples are currently under active development.

## Overview

DataStructs is a modern, header-only C++20 data structures library. The primary goal of this project is to provide clean, efficient, and standard-compliant implementations of fundamental data structures.

Built with modern C++ paradigms in mind, the library leverages C++20 features (such as concepts and compile-time evaluations where appropriate) and is strictly validated against rigorous compiler warnings to ensure memory safety and robust performance.

## Features

* **Header-Only Architecture:** No separate compilation step is required. Simply link the library via CMake and `#include` the necessary headers.
* **Modern C++20:** Takes advantage of the latest language standards for cleaner syntax and safer type constraints.
* **Strict Quality Controls:** Configured to compile cleanly under stringent compiler flags (e.g., `-Wall`, `-Wextra`, `-Wpedantic`, `-Wconversion` for GCC/Clang, and `/W4` for MSVC).
* **Standardized Layout:** Follows the Pitchfork project layout for professional and predictable directory organization.

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

## Quick Start (Integration)

Since DataStructs is a CMake `INTERFACE` library, integrating it into your project is straightforward.

1. Clone or copy the `DataStructs` repository into your project (e.g., into an `external/` or `third_party/` directory).
2. In your top-level `CMakeLists.txt`, add the subdirectory and link it to your target:

```cmake
# Add the library to your build
add_subdirectory(external/DataStructs)

# Link it to your executable or library
target_link_libraries(YourTargetName PRIVATE datastructs)
