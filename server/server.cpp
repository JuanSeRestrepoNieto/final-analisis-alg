#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <vector>
#include <cstring>
#include "totp_aes_utils.h"

#define PORT 8080
#define BUFFER_SIZE 1024

int main()
{
  int server_fd, new_socket;
  struct sockaddr_in address;
  socklen_t addrlen = sizeof(address);
  // unsigned char buffer[BUFFER_SIZE] = {0};

  server_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (server_fd == 0)
  {
    perror("socket failed");
    exit(EXIT_FAILURE);
  }

  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(PORT);

  if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
  {
    perror("bind failed");
    exit(EXIT_FAILURE);
  }

  if (listen(server_fd, 3) < 0)
  {
    perror("listen");
    exit(EXIT_FAILURE);
  }

  std::cout << "Server listening on port " << PORT << std::endl;
  new_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen);
  if (new_socket < 0)
  {
    perror("accept");
    exit(EXIT_FAILURE);
  }

  std::vector<unsigned char> buffer(BUFFER_SIZE);
  ssize_t valread = read(new_socket, buffer.data(), buffer.size());
  if (valread < 0)
  {
    perror("read");
    exit(EXIT_FAILURE);
  }
  buffer.resize(valread);
  std::string decrypted = aes_decrypt(buffer);
  std::cout << "Mensaje recibido: " << decrypted << std::endl;

  close(new_socket);
  close(server_fd);

  return 0;
}
