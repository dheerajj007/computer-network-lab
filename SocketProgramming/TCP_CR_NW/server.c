#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#define MAX_BUFFER 1024
#define PORT 6996
 
 
int main(){
    int serv_sock, client_socket;
    char buffer[MAX_BUFFER] = {0};
    struct sockaddr_in serv_addr, cli_addr;
    serv_sock = socket(AF_INET, SOCK_STREAM, 0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr = INADDR_ANY; 
    bind(serv_sock, (struct sockaddr *)&serv_addr,sizeof(serv_addr));
    listen(serv_sock ,5);
    while(1){
        int client_add_len = sizeof(cli_addr);
        client_socket = accept(serv_sock, (struct sockaddr*)&cli_addr,(socklen_t*)&client_add_len);
        int pid = fork();
        if(pid == 0){
            close(serv_sock);
            read(client_socket, buffer, MAX_BUFFER);
            printf("Client Message : %s\n", buffer);
            
            // Extra
 
            // sleep(5);
            printf("Updated Message : %s\n", buffer);
            send(client_socket, buffer, strlen(buffer),0);
            close(client_socket);
            exit(0);
        }else{
            close(client_socket);
        }
    }
    close(serv_sock);
}