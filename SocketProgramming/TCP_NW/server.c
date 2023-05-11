#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
 
int main(int argc, char const *argv[]) {
    int serverFd, clientFd, len, port;
    struct sockaddr_in server, client;
    char buffer[20];
    if (argc != 2) {
        printf("Format : Command Port");
        return 0;
    }
    port = atoi(argv[1]);
    serverFd = socket(AF_INET, SOCK_STREAM, 0);
    if (serverFd < 0) {
        printf("Socket Creation Error");
        return 0;
    }
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(port);
    len = sizeof(server);
    if (bind(serverFd, (struct sockaddr *)&server, len) < 0) {
        printf("Socket Not Binded");
        return 0;
    }
    if (listen(serverFd, 10) < 0) {
        printf("Socket Not Listening");
        return 0;
    }
    for (;;) {
        len = sizeof(client);
        printf("Listening... \n\n");
        if ((clientFd = accept(serverFd, (struct sockaddr *)&client, &len)) < 0) {
            printf("Message Recieving Error");
            continue;
        }
        char *client_ip = inet_ntoa(client.sin_addr);
        printf("Accepted new connection from a client %s: %d\n", client_ip, ntohs(client.sin_port));
        memset(buffer, 0, sizeof(buffer));
        int size = read(clientFd, buffer, sizeof(buffer));
        if ( size < 0 ) {
            printf("Reading Error.");
            break;
        }
        printf("Client Message : %s\n", buffer);
        // Extra
        printf("Updated Message : %s\n", buffer);
        if (write(clientFd, buffer, size) < 0) {
            perror("Writing Error.");
            break;
        }
        close(clientFd);
    }
    close(serverFd);
    return 0;
}