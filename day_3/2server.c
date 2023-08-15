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

    if(bind(sockfd,(struct sock_addr*)&servaddr,sizeof(servaddr))==-1)
    {
        perror("bind error\n");
        exit(1);
    }

    printf("Server listening on %s:%d\n",inet_ntoa(servaddr.sin_addr),ntohs(servaddr.sin_port));

    int msg;
    socklen_t destaddrlen=sizeof theiraddr;
    while(1){
        printf("Waiting for client message\n");
        if(recvfrom(sockfd,&msg,sizeof(msg),0,(struct sock_addr*)&theiraddr,&destaddrlen)==-1)
        {
            perror("receive error");
            exit(1);
        }
        printf("Received number: %d\n",msg);

        int sum=0;
        while(msg){
            sum+=msg%10;
            msg/=10;
        }

        if(sendto(sockfd,&sum,sizeof(sum),0,(struct sock_addr*)&theiraddr,sizeof theiraddr)==-1)
        {
            perror("Send failed");
            exit(1);
        }
        printf("Sum of digits sent: %d\n", sum);
        
    }
}