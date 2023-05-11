#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
int main(int argc, char *argv[]) {
    int serverFd, len, port;
    struct sockaddr_in server;
    char *server_ip = "127.0.0.1";  
    char *buffer;
    if (argc != 3 && argc != 4) {
        printf("Format : Command IP(optional) Port Message");
        return 0;
    }
    if(argc == 4){
        server_ip = argv[1];
        port = atoi(argv[2]);
        buffer = argv[3];
    }
    else{
        port = atoi(argv[1]);
        buffer = argv[2];
    }
    serverFd = socket(AF_INET, SOCK_STREAM, 0);
    if (serverFd < 0) {
        printf("Socket Not Created");
        return 0;
    }
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(server_ip);
    server.sin_port = htons(port);
    len = sizeof(server);
    if (connect(serverFd, (struct sockaddr *)&server, len) < 0) {
        printf("Cannot connect to server");
        return 0;
    }
    if (write(serverFd, buffer, strlen(buffer)) < 0) {
        printf("Unable to send message to server");
        return 0;
    }
    char recv[1024];
    memset(recv, 0, sizeof(recv));
    if (read(serverFd, recv, sizeof(recv)) < 0) {
        printf("Unable to recieve message from server");
        return 0;
    }
    printf("Server Response : %s\n", recv);
    close(serverFd);
    return 0;
}
 