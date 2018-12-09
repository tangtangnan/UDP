#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

#define PORT 1234

#define MAXDATASIZE 100

int main(int argc, char *argv[])
{
    int sockfd, num;
    char buf[MAXDATASIZE];
    struct hostent *he;
    struct sockaddr_in server, peer;
    if(argc != 3)
    {
        printf("Usage: %s <IP address> <message>\n", argv[0]);
        exit(1);
    }

    if((sockfd=socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
        printf("socket() error\n");
        exit(1);
    }
    bzero(&server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);

    server.sin_addr.s_addr = inet_addr(argv[1]);
    //server.sin_addr.s_addr = inet_addr(argv[1]);
    if(connect(sockfd, (struct sockaddr *)&server, sizeof(server)) == -1)
    {
        printf("connect() error.\n");
        exit(1);
    }
    
    send(sockfd, argv[2], strlen(argv[2]), 0);

    while(1)
    {
        if((num = recv(sockfd, buf, MAXDATASIZE, 0)) == -1)
        {
            printf("recv() error.\n");
            exit(1);
        }
        
        buf[num] = '\0';
        printf("Server Message: %s.\n", buf);
        break;
    }
    close(sockfd);
}