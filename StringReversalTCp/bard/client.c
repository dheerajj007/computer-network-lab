// Client program
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

  // Connect to the server
  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(9001); // use the same port as the server
  addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // use the local host IP address
  if (connect(sockfd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
    perror("connect");
    exit(1);
  }

  // Send a string to the server
  char str[100];
  scanf("%s", str);
  send(sockfd, str, strlen(str), 0);

  // Receive the reversed string from the server
  char reversed_str[100];
  recv(sockfd, reversed_str, sizeof(reversed_str), 0);

  // Print the reversed string
  printf("Reversed string: %s\n", reversed_str);

  // Close the socket
  close(sockfd);

  return 0;
}