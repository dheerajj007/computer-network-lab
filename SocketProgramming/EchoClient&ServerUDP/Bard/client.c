// EchoClient.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char *argv[]) {
  // Check for the correct number of arguments
  if (argc != 3) {
    fprintf(stderr, "Usage: %s <server_ip> <message>\n", argv[0]);
    exit(1);
  }

  // Create a UDP socket
  int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (sockfd < 0) {
    perror("socket");
    exit(1);
  }

  // Set the destination address
  struct sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(5000);
  inet_pton(AF_INET, argv[1], &server_addr.sin_addr);

  // Send the message
  int bytes_sent = sendto(sockfd, argv[2], strlen(argv[2]), 0, (struct sockaddr *)&server_addr, sizeof(server_addr));
  if (bytes_sent < 0) {
    perror("sendto");
    exit(1);
  }

  // Receive the response
  char response[100];
  int bytes_received = recvfrom(sockfd, response, sizeof(response), 0, NULL, NULL);
  if (bytes_received < 0) {
    perror("recvfrom");
    exit(1);
  }

  // Print the response
  printf("Received from server: %s\n", response);

  // Close the socket
  close(sockfd);

  return 0;
}
