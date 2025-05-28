#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h> 
#include <vector>
#include "aes_utils.h"

#define PORT 8080

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    std::string message = "Final análisis Algoritmos!";

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("socket creation error");
        return -1;
    }

    // Resolve "server" usando getaddrinfo
    struct addrinfo hints{}, *res;
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    if (getaddrinfo("server", nullptr, &hints, &res) != 0) {
        perror("getaddrinfo failed");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr = ((struct sockaddr_in*)res->ai_addr)->sin_addr;
    freeaddrinfo(res);

    // Mostrar IP a la que se conectará
    char ip_str[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(serv_addr.sin_addr), ip_str, INET_ADDRSTRLEN);
    std::cout << "Conectando a: " << ip_str << ":" << ntohs(serv_addr.sin_port) << std::endl;

    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection Failed");
        return -1;
    }

    std::vector<unsigned char> encrypted = aes_encrypt(message);
    send(sock, encrypted.data(), encrypted.size(), 0);

    std::cout << "Mensaje cifrado enviado al servidor." << std::endl;

    close(sock);
    return 0;
}
