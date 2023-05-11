#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h> // for close()

#define MAX_BUFFER_SIZE 32

int main() {
    // Create socket
    int serverSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (serverSocket == -1) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in serverAddr, clientAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12345);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket to the specified IP and port
    if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1) {
        perror("Error binding socket");
        exit(EXIT_FAILURE);
    }

    printf("Server started... waiting for connection...\n");

    char buffer[MAX_BUFFER_SIZE];
    memset(buffer, 0, sizeof(buffer));
    socklen_t clientAddrLen = sizeof(clientAddr);

    // Receive the message from the client
    ssize_t receivedBytes = recvfrom(serverSocket, buffer, sizeof(buffer) - 1, 0, (struct sockaddr *)&clientAddr, &clientAddrLen);
    if (receivedBytes == -1) {
        perror("Error receiving message");
        exit(EXIT_FAILURE);
    }

    printf("Received from client: %s\n", buffer);

    // Send the message back to the client
    ssize_t sentBytes = sendto(serverSocket, buffer, receivedBytes, 0, (struct sockaddr *)&clientAddr, clientAddrLen);
    if (sentBytes == -1) {
        perror("Error sending message");
        exit(EXIT_FAILURE);
    }

    // Close the socket
    close(serverSocket);

    return 0;
}
