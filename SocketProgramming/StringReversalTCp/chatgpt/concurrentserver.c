#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h> // for fork() and close()

#define PORT 8080
#define BUFFER_SIZE 1024

void reverseString(char *str) {
    int i = 0;
    int j = strlen(str) - 1;

    while (i < j) {
        char temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++;
        j--;
    }
}

int main() {
    int serverSocket, newSocket;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t addrSize = sizeof(clientAddr);
    char buffer[BUFFER_SIZE];

    // Create socket
    if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    // Prepare the server address structure
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket to the specified IP and port
    if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1) {
        perror("Error binding socket");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(serverSocket, 5) == -1) {
        perror("Error listening on socket");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", PORT);

    while (1) {
        // Accept incoming connection
        if ((newSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &addrSize)) == -1) {
            perror("Error accepting connection");
            exit(EXIT_FAILURE);
        }

        printf("Client connected: %s:%d\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));

        // Fork a new process to handle the client request
        pid_t pid = fork();

        if (pid == -1) {
            perror("Error forking process");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process

            // Close the listening socket in the child process
            close(serverSocket);

            // Receive strings from the client and reply with reversed strings
            while (1) {
                memset(buffer, 0, sizeof(buffer));

                // Receive string from client
                if (recv(newSocket, buffer, sizeof(buffer), 0) == -1) {
                    perror("Error receiving data");
                    exit(EXIT_FAILURE);
                }

                printf("Received: %s\n", buffer);

                // Reverse the string
                reverseString(buffer);

                // Reply with reversed string
                if (send(newSocket, buffer, strlen(buffer), 0) == -1) {
                    perror("Error sending data");
                    exit(EXIT_FAILURE);
                }

                printf("Replied with: %s\n", buffer);
            }

            // Close the client socket in the child process
            close(newSocket);

            exit(EXIT_SUCCESS);
        } else {
            // Parent process

            // Close the client socket in the parent process
            close(newSocket);
        }
    }

    // Close the server socket
    close(serverSocket);

    return 0;
}
