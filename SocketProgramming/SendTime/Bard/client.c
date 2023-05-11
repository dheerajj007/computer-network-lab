#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char *argv[]) {
  // Check the number of arguments
  if (argc != 3) {
    fprintf(stderr, "Usage: %s <server_ip> <port>\n", argv[0]);
    exit(1);
  }

  // Create a socket
  int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (sockfd < 0) {
    perror("socket");
    exit(1);
  }

  // Set the destination address
  struct sockaddr_in addr;
  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(atoi(argv[2]));
  inet_pton(AF_INET, argv[1], &addr.sin_addr);

  // Send a request for the time of day
  char buffer[1024];
  strcpy(buffer, "GET TIME");
  sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&addr, sizeof(addr));

  // Receive the time from the server
  int n = recvfrom(sockfd, buffer, sizeof(buffer), 0, NULL, NULL);
  if (n < 0) {
    perror("recvfrom");
    exit(1);
  }

  // Print the time
  printf("The time is: %s\n", buffer);

  // Close the socket
  close(sockfd);

  return 0;
}
