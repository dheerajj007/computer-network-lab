// CalcServerTCP.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char *argv[]) {
  // Check for the correct number of arguments
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <port_number>\n", argv[0]);
    exit(1);
  }

  // Create a TCP socket
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    perror("socket");
    exit(1);
  }

  // Bind the socket to a port
  struct sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(atoi(argv[1]));
  server_addr.sin_addr.s_addr = INADDR_ANY;
  if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
    perror("bind");
    exit(1);
  }

  // Listen for connections
  if (listen(sockfd, 5) < 0) {
    perror("listen");
    exit(1);
  }

  // Accept connections
  while (1) {
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    int client_fd = accept(sockfd, (struct sockaddr *)&client_addr, &client_addr_len);
    if (client_fd < 0) {
      perror("accept");
      continue;
    }

    // Print the IP address and port of the connected client
    char client_ip[INET_ADDRSTRLEN];
    if (inet_ntop(AF_INET, &client_addr.sin_addr, client_ip, sizeof(client_ip)) < 1) {
      fprintf(stderr, "Error converting IP address to string\n");
      continue;
    }
    printf("Connected to client %s:%d\n", client_ip, ntohs(client_addr.sin_port));

    // Receive data from the client
    char expression[100];
    int bytes_received = recv(client_fd, expression, sizeof(expression), 0);
    if (bytes_received < 0) {
      perror("recv");
      continue;
    }

    // Evaluate the arithmetic expression
    char answer[100];
    int result = eval(expression);
    sprintf(answer, "%d", result);

    // Send the result back to the client
    int bytes_sent = send(client_fd, answer, strlen(answer), 0);
    if (bytes_sent < 0) {
      perror("send");
      continue;
    }

    // Close the socket
    close(client_fd);
  }

  return 0;
}

// Evaluate an arithmetic expression
int eval(char *expression) {
  // Create a parser
  struct parser *parser = parser_new();

  // Parse the expression
  int result = parser_parse(parser, expression);

  // Free the parser
  parser_free(parser);

  // Return the result
  return result;
}
