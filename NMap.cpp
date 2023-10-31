#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

// Function to scan a single port
bool scanPort(const std::string& target, int port) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        return false;
    }

    sockaddr_in sockaddr{};
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_port = htons(port);
    sockaddr.sin_addr.s_addr = inet_addr(target.c_str());

    int result = connect(sock, reinterpret_cast<struct sockaddr*>(&sockaddr), sizeof(sockaddr));
    close(sock);

    return result == 0;
}

int main() {
    std::string target = "127.0.0.1";
    int startPort = 1;
    int endPort = 1024;

    std::cout << "Scanning ports on " << target << std::endl;

    for (int port = startPort; port <= endPort; ++port) {
        if (scanPort(target, port)) {
            std::cout << "Port " << port << " is open" << std::endl;
        }
    }

    return 0;
}
