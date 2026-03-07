#include <cstddef>
#include <datastructs/stack.hpp>
#include <iostream>

int main() {
    /*******************************************************************************************
     * STACK DEMO                                                                             **
     * *****************************************************************************************
     */

    // --- Intialsing stack ---

    std::cout << "Initisalising stack 1" << "\n";
    std::size_t size = 5;
    datastructs::Stack<int> stack1(size);
    std::cout << "Size of stack 1: " << stack1.size() << "\n";

    // --- Stack operations ---

    // 1. push()
    std::cout << "Adding elements to stack \n";
    for (std::size_t i = 0; i < stack1.capacity(); ++i) {
        try {
            stack1.push(static_cast<int>(i));
        } catch (const std::exception& e) {
            std::cerr << e.what() << '\n';
        }
    }
    std::cout << "stack 1 after pushing data: " << stack1 << "\n\n";

    // 2. peak()
    if (!stack1.isEmpty()) // check if empty before peaking
    {
        std::cout << "Top of stack 1 is: " << stack1.peak() << "\n";
    }

    // 3. pop()
    std::cout << "Pop top item: " << stack1.pop() << "\n";
    std::cout << "Stack 1 after popping top item : " << stack1 << "\n";

    // 4. aize()
    std::cout << "Size of stack 1: " << stack1.size() << "\n\n";

    // --- Maxing out stack ---

    std::cout << "Max out stack 1 with adding too much items: " << "\n";
    for (int i = 5; i < 10; i++) {
        try {
            stack1.push(i);
        } catch (const std::exception& e) {
            std::cerr << e.what() << '\n';
        }
    }
    std::cout << "stack 1 after pushing data: " << stack1 << "\n\n\n";

    // --- Copy construction ---

    std::cout << "Initialising stack 2 using stack 1 (Copy constructor)\n";
    datastructs::Stack<int> stack2 = stack1;
    std::cout << "Printing stack 2: " << stack2 << "\n";
    std::cout << "Pop all items in stack 2\n";
    while (!stack2.isEmpty()) // check if empty before popping since no  bound check
    {
        std::cout << stack2.pop() << " ";
    }
    std::cout << "\n";
    std::cout << "Size of stack 2 after popping: " << stack2.size() << "\n\n\n";

    // --- Copy assignment ---

    std::cout << "Initialising empty stack 3 using stack 1 (Copy assignment)\n";
    datastructs::Stack<int> stack3(3);
    stack3 = stack1;
    std::cout << "Printing stack 3: " << stack3 << "\n\n\n";

    // --- Move construction ---

    std::cout << "Initialising stack 4 by moving stack 1 to stack 4 (Move constructor)\n";
    datastructs::Stack<int> stack4 = std::move(stack1);
    std::cout << stack4 << "\n";
    std::cout << "Size of stack 1 after moving: " << stack1.size() << "\n";
    std::cout << "Printing stack 4: " << stack4 << "\n";
    std::cout << "Printing stack 1: " << stack1 << "\n\n\n";

    // --- Move Assignment ---

    std::cout << "Initialising stack 5 by moving stack 3 (Move assignment)\n";
    datastructs::Stack<int> stack5(1);
    stack5 = std::move(stack3);
    std::cout << "Printing stack 5: " << stack5 << "\n";
    std::cout << "Printing stack 3: " << stack3 << "\n";

    return 0;
}
