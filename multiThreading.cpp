#include <iostream>
#include <thread>

// This function will be executed by a separate thread
void threadFunction() {
    for (int i = 0; i < 5; ++i) {
        std::cout << "Thread: " << i << std::endl;
    }
}

int main() {
    // Create a thread and pass the function to execute
    std::thread t1(threadFunction);

    // Main thread's work
    for (int i = 0; i < 5; ++i) {
        std::cout << "Main: " << i << std::endl;
    }

    // Wait for the thread to finish
    t1.join();

    return 0;
}
