#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main() {
  // Create a socket
  int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (sockfd < 0) {
    perror("socket");
    exit(1);
  }

  // Bind the socket to a port
  struct sockaddr_in addr;
  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(12345);
  addr.sin_addr.s_addr = INADDR_ANY;
  if (bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
    perror("bind");
    exit(1);
  }

  // Receive a request from the client
  char buffer[1024];
  int n = recvfrom(sockfd, buffer, sizeof(buffer), 0, NULL, NULL);
  if (n < 0) {
    perror("recvfrom");
    exit(1);
  }

  // Check if the request is for the time of day
  if (strncmp(buffer, "GET TIME", 7) != 0) {
    fprintf(stderr, "Invalid request\n");
    exit(1);
  }

  // Get the current time
  time_t now = time(NULL);
  struct tm *tm = localtime(&now);

  // Send the time to the client
  char time_str[32];
  strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", tm);
  sendto(sockfd, time_str, strlen(time_str), 0, NULL, NULL);

  // Close the socket
  close(sockfd);

  return 0;
}
