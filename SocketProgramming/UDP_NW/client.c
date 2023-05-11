#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<arpa/inet.h>
#include<stdio.h>
#define MAXLINE 1024
int main(int argc,char* argv[])
{
    int sockfd;
    int n;
    socklen_t len;
    char sendline[MAXLINE],recvline[MAXLINE];
    struct sockaddr_in servaddr;
 
    if(argc != 4){
        printf("Format : Command Address Port Message\n");
        return 0;
    }
    strcpy(sendline,argv[3]);
    sockfd=socket(AF_INET,SOCK_DGRAM,0);
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family=AF_INET;
    servaddr.sin_addr.s_addr=inet_addr(argv[1]);
    servaddr.sin_port=htons(atoi(argv[2]));
    connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
    len=sizeof(servaddr);
    sendto(sockfd,argv[3],sizeof(argv[3]),0,(struct sockaddr*)&servaddr,len);
    // Extra
    n=recvfrom(sockfd,recvline,MAXLINE,0,NULL,NULL);
    recvline[n]=0;
    printf("\n Server's Echo : %s\n\n",recvline);
    return 0;
}