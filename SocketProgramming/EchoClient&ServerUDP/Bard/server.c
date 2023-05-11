// EchoServer.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main() {
  // Create a UDP socket
  int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (sockfd < 0) {
    perror("socket");
    exit(1);
  }

  // Bind the socket to a port
  struct sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(5000);
  server_addr.sin_addr.s_addr = INADDR_ANY;
  if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
    perror("bind");
    exit(1);
  }

  // Receive a message
  char message[100];
  int bytes_received = recvfrom(sockfd, message, sizeof(message), 0, NULL, NULL);
  if (bytes_received < 0) {
    perror("recvfrom");
    exit(1);
  }

  // Echo the message back to the client
  int bytes_sent = sendto(sockfd, message, bytes_received, 0, (struct sockaddr *)&server_addr, sizeof(server_addr));
  if (bytes_sent < 0) {
    perror("sendto");
    exit(1);
  }

  // Close the socket
  close(sockfd);

  return 0;
}
