#include <iostream>
#include <thread>

int sharedValue = 0;

void IncrementSharedValue() {
    for (int i = 0; i < 100000; ++i) {
        sharedValue++;
    }
}

int main() {
    std::thread thread1(IncrementSharedValue);
    std::thread thread2(IncrementSharedValue);

    thread1.join();
    thread2.join();

    std::cout << "Final sharedValue: " << sharedValue << std::endl;

    return 0;
}
