#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <atomic>

class LoadBalancer {
public:
    LoadBalancer() : currentIndex(0) {}

    void AddServer(const std::string& serverName) {
        std::lock_guard<std::mutex> lock(serverMutex);
        servers.push_back(serverName);
    }

    std::string GetNextServer() {
        std::lock_guard<std::mutex> lock(serverMutex);
        if (servers.empty()) {
            return "No servers available";
        }

        int index = currentIndex++;
        index %= servers.size();
        return servers[index];
    }

private:
    std::vector<std::string> servers;
    std::mutex serverMutex;
    std::atomic<int> currentIndex;
};

int main() {
    LoadBalancer loadBalancer;

    // Add servers to the load balancer
    loadBalancer.AddServer("Server1");
    loadBalancer.AddServer("Server2");
    loadBalancer.AddServer("Server3");

    // Simulate client requests
    for (int i = 0; i < 10; ++i) {
        std::string server = loadBalancer.GetNextServer();
        std::cout << "Request " << i + 1 << " routed to " << server << std::endl;
    }

    return 0;
}
