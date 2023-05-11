// CalcClientTCP.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char *argv[]) {
  // Check for the correct number of arguments
  if (argc != 3) {
    fprintf(stderr, "Usage: %s <server_hostname> <port_number>\n", argv[0]);
    exit(1);
  }

  // Resolve the server hostname to an IP address
  struct sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(atoi(argv[2]));
  if (inet_pton(AF_INET, argv[1], &server_addr.sin_addr) < 1) {
    fprintf(stderr, "Error resolving hostname: %s\n", argv[1]);
    exit(1);
  }

  // Create a TCP socket
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    perror("socket");
    exit(1);
  }

  // Connect to the server
  if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
    perror("connect");
    exit(1);
  }

  // Print the IP address and port of the server
  char server_ip[INET_ADDRSTRLEN];
  if (inet_ntop(AF_INET, &server_addr.sin_addr, server_ip, sizeof(server_ip)) < 1) {
    fprintf(stderr, "Error converting IP address to string\n");
    exit(1);
  }
  printf("Connected to server %s:%d\n", server_ip, ntohs(server_addr.sin_port));

  // Get the user's input
  char expression[100];
  printf("Enter an arithmetic expression: ");
  fgets(expression, sizeof(expression), stdin);

  // Send the expression to the server
  int bytes_sent = send(sockfd, expression, strlen(expression), 0);
  if (bytes_sent < 0) {
    perror("send");
    exit(1);
  }

  // Read the answer from the server
  char answer[100];
  int bytes_received = recv(sockfd, answer, sizeof(answer), 0);
  if (bytes_received < 0) {
    perror("recv");
    exit(1);
  }

  // Print the answer to the user
  printf("The answer is: %s\n", answer);

  // Close the socket
  close(sockfd);

  return 0;
}
