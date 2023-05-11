// Server program
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main() {
  // Create a socket
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    perror("socket");
    exit(1);
  }

  // Bind the socket to a port
  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(9001); // use some unused port number
  addr.sin_addr.s_addr = INADDR_ANY;
  if (bind(sockfd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
    perror("bind");
    exit(1);
  }

  // Listen for connections
  listen(sockfd, 5);

  // Accept connections
  while (1) {
    int clientfd = accept(sockfd, NULL, NULL);
    if (clientfd < 0) {
      perror("accept");
      exit(1);
    }

    // Fork a child process to handle the connection
    pid_t pid = fork();
    if (pid < 0) {
      perror("fork");
      exit(1);
    } else if (pid == 0) {
      // This is the child process. Close the listening socket and handle the connection.
      close(sockfd);

      // Receive a string from the client
      char str[100];
      recv(clientfd, str, sizeof(str), 0);

      // Reverse the string
      char reversed_str[100];
      int i, j;
      for (i = 0, j = strlen(str) - 1; i < j; i++, j--) {
        reversed_str[i] = str[j];
        reversed_str[j] = str[i];
      }
      reversed_str[strlen(str)] = '\0';

      // Send the reversed string back to the client
      send(clientfd, reversed_str, strlen(reversed_str), 0);

      // Close the client connection
      close(clientfd);

      // Exit the child process
      exit(0);
    } else {
      // This is the parent process. Continue listening for connections.
      close(clientfd);
    }
  }

  return 0;
}
    