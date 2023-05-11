#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<netdb.h>
#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#define MAXLINE 1024
int main(int argc,char *argv[])
{
    int sockfd;
    int n;
    socklen_t len;
    char msg[1024];
    struct sockaddr_in servaddr,cliaddr;
    if(argc != 2){
        printf("Format : Command Port\n");
        return 0;
    }
    sockfd=socket(AF_INET,SOCK_DGRAM,0);
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family=AF_INET;
    servaddr.sin_addr.s_addr=INADDR_ANY;
    servaddr.sin_port=htons(atoi(argv[1]));
    printf("\n\n Binded");
    bind(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
    printf("\n\n Listening...");
    for(;;)
    {
        printf("\n ");
        len=sizeof(cliaddr);
        n=recvfrom(sockfd,msg,MAXLINE,0,(struct sockaddr*)&cliaddr,&len);
        // Extra
        printf("\n Client's Message : %s\n Message Length : %d\n",msg, strlen(msg));
        sendto(sockfd,msg,n,0,(struct sockaddr*)&cliaddr,len);
    }
    return 0;
}