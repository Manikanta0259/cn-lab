//How to IMPLEMENT  Nmap scan.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

int scan_port(const char *ip, int port) {
    int sock;
    struct sockaddr_in addr;
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) return 0;

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    inet_pton(AF_INET, ip, &addr.sin_addr);

    // Set timeout for connect (optional)
    struct timeval timeout;
    timeout.tv_sec = 1; // 1 second timeout
    timeout.tv_usec = 0;
    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof timeout);
    setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, (const char*)&timeout, sizeof timeout);

    int result = connect(sock, (struct sockaddr *)&addr, sizeof(addr));
    close(sock);

    return (result == 0); // 0 means successful connection (port open)
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <IP address>", argv[0]);
        return 1;
    }

    const char *ip = argv[1];
    printf("Scanning %s for open ports...", ip);

    for (int port = 20; port <= 1024; port++) {
        if (scan_port(ip, port)) {
            printf("Port %d is open", port);
        }
    }

    return 0;
}