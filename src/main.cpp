#include <array>
#include <datastructs/array.hpp>
#include <datastructs/binary_search_tree.hpp>
#include <datastructs/doubly_linked_list.hpp>
#include <datastructs/heap.hpp>
#include <datastructs/queue.hpp>
#include <datastructs/singly_linked_list.hpp>
#include <datastructs/stack.hpp>
#include <datastructs/vector.hpp>
#include <iostream>

template <typename T, std::size_t N>
void intialise_tree(datastructs::BinarySearchTree<T>& tree, std::array<T, N>& nodes) {
    for (const auto& val : nodes) {
        tree.insert_node(val);
    }
}

int main() {
    // 1. Intialsing stack
    std::cout << "Initisalising stack 1" << "\n";
    int size = 5;
    datastructs::Stack<float> stack1(static_cast<std::size_t>(size));
    std::cout << "Size of stack 1: " << stack1.size() << "\n";

    // 1. Initialise a queue object and try to enqueue beyond it's limit
    datastructs::Queue<int> queue1(5);
    for (int i = 0; i < 7; i++) {
        try {
            queue1.enqueue(i);
        } catch (const std::exception& e) {
            std::cerr << e.what() << '\n';
        }
    }
    std::cout << "Print queue 1: " << queue1 << "\n\n";

    // 1. Testing linked list functions
    std::array primes{2, 3, 5, 7, 11};
    datastructs::LinkedList<int> prime_numbers;

    for (const auto& val : primes) {
        prime_numbers.insert_front(val);
    }
    std::cout << "Prime numbers: " << prime_numbers << "\n";

    // 1. Testing doubly linked list functions
    std::array evens{2, 4, 6, 8, 10, 12};
    datastructs::DLinkedList<int> even_numbers;

    for (const auto& val : evens) {
        even_numbers.insert_rear(val);
    }
    std::cout << "Even numbers: " << even_numbers << " lenght: " << even_numbers.length() << "\n\n";

    // 1. instantiate heap 1
    datastructs::MaxHeap<int> heap_1;
    heap_1.insert_node(10);
    heap_1.insert_node(20);
    heap_1.insert_node(15);
    heap_1.insert_node(30);
    heap_1.insert_node(40);
    heap_1.insert_node(30);

    std::cout << "Heap 1: " << heap_1 << "\n";
    std::cout << "Heap 1 size: " << heap_1.size() << "\n";
    std::cout << "Heap 1 empty: " << std::boolalpha << heap_1.is_empty() << "\n\n";

    // 1. Initialise tree object

    std::array nodes{5, 10, 20, 8, 12, 17, 25};
    datastructs::BinarySearchTree<int> tree_1;
    intialise_tree<int, 7>(tree_1, nodes);
    std::cout << tree_1 << "\n\n";

    // Initialising vector
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

    // 1. Array
    datastructs::MyArray<int, 4> prime{2, 3, 5, 7};
    std::cout << prime;
    const datastructs::MyArray prime_2 = prime;
    std::cout << prime_2;
    std::cout << "Index 0: " << prime_2.front() << "\n";
    std::cout << "Index 1: " << prime_2.at(1) << "\n";
    std::cout << "Last element: " << prime_2.back() << "\n\n";

    return 0;
}
