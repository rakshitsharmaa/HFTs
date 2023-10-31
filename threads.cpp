#include <iostream>
#include <thread>

void task1() {
    for (int i = 0; i < 5; ++i) {
        std::cout << "Task 1: " << i << std::endl;
    }
}

void task2() {
    for (int i = 0; i < 5; ++i) {
        std::cout << "Task 2: " << i << std::endl;
    }
}

int main() {
    // Create two threads
    std::thread t1(task1);
    std::thread t2(task2);

    // Wait for the threads to finish
    t1.join();
    t2.join();

    std::cout << "Both threads have completed." << std::endl;

    return 0;
}
