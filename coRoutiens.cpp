#include <iostream>
#include <coroutine>
#include <thread>

// Define a coroutine that simulates an asynchronous task.
struct MyCoroutine {
    struct promise_type {
        int result;

        MyCoroutine get_return_object() {
            return MyCoroutine{std::coroutine_handle<promise_type>::from_promise(*this)};
        }

        std::suspend_never initial_suspend() { return {}; }
        std::suspend_never final_suspend() noexcept { return {}; }

        void return_value(int value) {
            result = value;
        }

        void unhandled_exception() {
            std::terminate();
        }
    };

    std::coroutine_handle<promise_type> coroutine;

    int getResult() {
        return coroutine.promise().result;
    }

    bool await_ready() {
        return false; // Simulate an asynchronous operation.
    }

    void await_suspend(std::coroutine_handle<>) {
        std::thread([] {
            std::this_thread::sleep_for(std::chrono::seconds(2));
            coroutine.resume();
        }).detach();
    }

    int await_resume() {
        return getResult();
    }
};

MyCoroutine createAsyncTask() {
    co_await std::suspend_never{}; // Allow co_await inside the function
    co_yield 42; // Simulate asynchronous operation
    co_return 100; // Return a result
}

int main() {
    MyCoroutine coroutine = createAsyncTask();

    while (!coroutine.coroutine.done()) {
        // Do other work while waiting for the coroutine to complete.
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    std::cout << "Coroutine result: " << coroutine.getResult() << std::endl;
    return 0;
}
