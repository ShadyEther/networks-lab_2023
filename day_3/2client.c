#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>

int main()
{
    int sockfd;
    if((sockfd=socket(AF_INET,SOCK_DGRAM,0))==-1){
        perror("Socket creation error\n");
        exit(1);
    }

    char ip[100];
    int port;
    printf("Enter ip to host: ");
    scanf(" %[^\n]c%*c",ip);
    printf("enter port: ");
    scanf("%d",&port);
    struct sockaddr_in servaddr,theiraddr;

    servaddr.sin_family=AF_INET;
    servaddr.sin_port=htons(port);
    inet_pton(servaddr.sin_family,ip,&servaddr.sin_addr);



    printf("Server listening on %s:%d\n",inet_ntoa(servaddr.sin_addr),ntohs(servaddr.sin_port));

    int msg;
    socklen_t destaddrlen=sizeof theiraddr;
    while(1){
        printf("Enter number: ");
        scanf("%d",&msg);

        if(sendto(sockfd,&msg,sizeof(msg),0,(struct sock_addr*)&servaddr,sizeof(servaddr))==-1)
        {
            perror("Send failed");
            exit(1);
        }
        printf("Message sent\n");

        if(recvfrom(sockfd,&msg,sizeof(msg),0,NULL,NULL)==-1)
        {
            perror("receive error");
            exit(1);
        }
        printf("Received Sum of digits: %d\n",msg);

        
    }
}