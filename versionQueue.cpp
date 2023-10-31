#include <iostream>
#include <queue>
#include <vector>

template <typename T>
class VersionedQueue {
public:
    VersionedQueue() {
        versions.push_back(std::queue<T>());
    }

    void Enqueue(const T& value) {
        versions.back().push(value);
    }

    bool Dequeue() {
        if (versions.back().empty()) {
            return false;
        }
        versions.back().pop();
        return true;
    }

    void CreateVersion() {
        versions.push_back(versions.back());
    }

    void RevertToVersion(size_t version) {
        if (version < versions.size()) {
            versions.resize(version + 1);
        }
    }

    void PrintCurrentVersion() {
        std::queue<T> currentVersion = versions.back();
        while (!currentVersion.empty()) {
            std::cout << currentVersion.front() << " ";
            currentVersion.pop();
        }
        std::cout << std::endl;
    }

private:
    std::vector<std::queue<T>> versions;
};

int main() {
    VersionedQueue<int> vq;

    vq.Enqueue(1);
    vq.Enqueue(2);
    vq.Enqueue(3);

    vq.CreateVersion();

    vq.Enqueue(4);

    vq.PrintCurrentVersion(); // Output: 1 2 3 4

    vq.RevertToVersion(0);

    vq.PrintCurrentVersion(); // Output: 1 2 3

    return 0;
}
