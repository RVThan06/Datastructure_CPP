#include <datastructs/queue.hpp>
#include <iostream>
#include <stdexcept>

int main() {
    /*******************************************************************************************
     * QUEUE DEMO                                                                             **
     * *****************************************************************************************
     */

    // --- Initialising queue ---

    datastructs::Queue<int> queue1(5);
    for (int i = 0; i < 7; i++) {
        try {
            queue1.enqueue(i);
        } catch (const std::exception& e) {
            std::cerr << e.what() << '\n';
        }
    }
    std::cout << "Print queue 1: " << queue1 << "\n\n";

    // --- Queue operations ---

    // 1. dequeue()
    std::cout << "Remove first  3 elements \n";
    std::cout << "Dequeue :" << queue1.dequeue() << "\n";
    std::cout << "Dequeue :" << queue1.dequeue() << "\n";
    std::cout << "Dequeue :" << queue1.dequeue() << "\n\n";

    // 2. enqueue()
    std::cout << "Add 2 elements \n";
    std::cout << "Enqueue : 6 \n";
    queue1.enqueue(6);
    std::cout << "Enqueue : 7 \n";
    queue1.enqueue(7);
    std::cout << "Queue 1 after adding new elements: " << queue1 << "\n";
    std::cout << "Front of queue 1 is : " << queue1.front() << "\n\n";

    // --- Copy semantics ---

    std::cout << "Instantiating queue 2 by copying queue 1. (Copy constructor)\n";
    datastructs::Queue<int> queue2 = queue1;
    std::cout << "Print queue 2: " << queue2 << "\n\n";

    // --- Move constructions ---

    std::cout << "Instantiating queue 3 by moving queue 1. (Move constructor)\n";
    datastructs::Queue<int> queue3 = std::move_if_noexcept(queue1);
    std::cout << "Print queue 3: " << queue3 << "\n";
    std::cout << "Print queue 1 (empty but valid): " << queue1 << "\n\n";

    // --- Move assignment ---
    std::cout << "Instantiating queue 4 by moving queue 3. (Move assignment)\n";
    datastructs::Queue<int> queue4(2);
    queue4 = std::move_if_noexcept(queue3);
    std::cout << "Print queue 4: " << queue4 << "\n";
    std::cout << "Print queue 3 (empty but valid): " << queue3 << "\n\n";

    // queue3.front(); // will cause program to crash because peaking an empty queue is invalid

    return 0;
}
