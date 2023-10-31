#include <iostream>
#include <atomic>
#include <thread>

std::atomic<int> sharedCounter(0);

void IncrementCounter() {
    for (int i = 0; i < 10000; ++i) {
        sharedCounter.fetch_add(1, std::memory_order_relaxed);
    }
}

int main() {
    std::thread thread1(IncrementCounter);
    std::thread thread2(IncrementCounter);

    thread1.join();
    thread2.join();

    std::cout << "Final sharedCounter value: " << sharedCounter.load(std::memory_order_relaxed) << std::endl;

    return 0;
}
