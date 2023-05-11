#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SERVER_IP "SERVER_IP_ADDRESS"
#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int clientSocket;
    struct sockaddr_in serverAddr;
    char buffer[BUFFER_SIZE];

    // Create socket
    if ((clientSocket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    // Prepare the server address structure
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);

    // Connect to the server
    if (connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1) {
        perror("Error connecting to the server");
        exit(EXIT_FAILURE);
    }

    printf("Connected to the server\n");

    // Send strings to the server and receive reversed strings
    while (1) {
        printf("Enter a string (or 'q' to quit): ");
        fgets(buffer, sizeof(buffer), stdin);

        // Remove newline character from the input
        buffer[strcspn(buffer, "\n")] = '\0';

        // Check if the user wants to quit
        if (strcmp(buffer, "q") == 0) {
            break;
        }

        // Send string to the server
        if (send(clientSocket, buffer, strlen(buffer), 0) == -1) {
            perror("Error sending data");
            exit(EXIT_FAILURE);
        }

        printf("Sent: %s\n", buffer);

        // Receive reversed string from the server
        memset(buffer, 0, sizeof(buffer));
        if (recv(clientSocket, buffer, sizeof(buffer), 0) == -1) {
            perror("Error receiving data");
            exit(EXIT_FAILURE);
        }

        printf("Reversed: %s\n", buffer);
    }

    // Close the socket
    close(clientSocket);

    return 0;
}
