#include <datastructs/heap.hpp>
#include <iostream>

int main() {
    /****************************************************************************************************
     * HEAP DEMO                                                                         **
     * **************************************************************************************************
     */

    // --- Heap Initialisation --------------------------------------------------------------------------

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

    // --- Copy semantics -------------------------------------------------------------------------------

    // 1. Copy construction
    datastructs::MaxHeap<int> heap_2 = heap_1;
    std::cout << "Copy constructing heap 2 using heap 1\n";
    std::cout << "Heap 2: " << heap_2 << "\n";
    std::cout << "Heap 2 size: " << heap_2.size() << "\n";
    std::cout << "Heap 2 empty: " << std::boolalpha << heap_2.is_empty() << "\n\n";

    // ---  Move semantics ------------------------------------------------------------------------------

    // 1. Move construction
    datastructs::MaxHeap<int> heap_3 = std::move_if_noexcept(heap_2);
    std::cout << "Move constructing heap 3 using heap 2\n";
    std::cout << "Heap 3: " << heap_3 << "\n";
    std::cout << "Heap 3 size: " << heap_3.size() << "\n";
    std::cout << "Heap 3 empty: " << std::boolalpha << heap_3.is_empty() << "\n";
    std::cout << "Heap 2 empty: " << std::boolalpha << heap_2.is_empty() << "\n\n";

    // --- Heap Operations ------------------------------------------------------------------------------

    // 1. delete_node()
    std::cout << "Deleting heap 1 nodes --> returns nodes sorted in descending order\n";
    std::cout << heap_1.delete_node() << " -> ";
    std::cout << heap_1.delete_node() << " -> ";
    std::cout << heap_1.delete_node() << " -> ";
    std::cout << heap_1.delete_node() << " -> ";
    std::cout << heap_1.delete_node() << " -> ";
    std::cout << heap_1.delete_node() << " -> ";
    // std::cout << heap_1.delete_node() << " -> "; this line will raise empty heap exception
    std::cout << "\n";

    return 0;
}
