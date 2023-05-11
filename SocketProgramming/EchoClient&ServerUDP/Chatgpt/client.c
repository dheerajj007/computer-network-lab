#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAX_BUFFER_SIZE 32

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <server IP address> <message>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *serverIP = argv[1];
    const char *message = argv[2];

    // Create socket
    int clientSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (clientSocket == -1) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12345);
    if (inet_pton(AF_INET, serverIP, &serverAddr.sin_addr) <= 0) {
        perror("Invalid server IP address");
        exit(EXIT_FAILURE);
    }

    // Send the message to the server
    ssize_t sentBytes = sendto(clientSocket, message, strlen(message), 0, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
    if (sentBytes == -1) {
        perror("Error sending message");
        exit(EXIT_FAILURE);
    }

    printf("Sent to server: %s\n", message);

    // Receive the response from the server
    char buffer[MAX_BUFFER_SIZE];
    memset(buffer, 0, sizeof(buffer));
    socklen_t serverAddrLen = sizeof(serverAddr);
    ssize_t receivedBytes = recvfrom(clientSocket, buffer, sizeof(buffer) - 1, 0, (struct sockaddr *)&serverAddr, &serverAddrLen);
    if (receivedBytes == -1) {
        perror("Error receiving response");
        exit(EXIT_FAILURE);
    }

    printf("Received from server: %s\n", buffer);

    // Close the socket
    close(clientSocket);

    return 0;
}
