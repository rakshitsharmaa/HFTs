#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>

class RateLimiter {
public:
    RateLimiter(int ratePerSecond) : ratePerSecond_(ratePerSecond) {
        lastTime_ = std::chrono::steady_clock::now();
    }

    void RateLimit() {
        std::unique_lock<std::mutex> lock(mutex_);
        auto currentTime = std::chrono::steady_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastTime_).count();

        if (elapsedTime < 1000) {
            int sleepTime = (1000 / ratePerSecond_) - elapsedTime;
            std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
        }

        lastTime_ = std::chrono::steady_clock::now();
    }

private:
    int ratePerSecond_;
    std::chrono::time_point<std::chrono::steady_clock> lastTime_;
    std::mutex mutex_;
};

int main() {
    RateLimiter limiter(5); // Limit to 5 requests per second

    for (int i = 0; i < 10; ++i) {
        limiter.RateLimit();
        std::cout << "Request " << i + 1 << " has been processed." << std::endl;
    }

    return 0;
}
