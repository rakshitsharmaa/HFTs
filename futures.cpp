#include <iostream>
#include <future>

int CalculateSum(int a, int b) {
    std::this_thread::sleep_for(std::chrono::seconds(2)); // Simulating a time-consuming task
    return a + b;
}

int main() {
    // Launch a task asynchronously using std::async
    std::future<int> result = std::async(CalculateSum, 3, 4);

    // Do some other work here while the task is running...

    // Wait for the result and retrieve it
    int sum = result.get();

    std::cout << "Sum is: " << sum << std::endl;

    return 0;
}
