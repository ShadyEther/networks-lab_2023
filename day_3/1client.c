#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>
int main()
{
    //socket creation
    int sockfd=socket(AF_INET,SOCK_DGRAM,0);
    if(sockfd==-1){
        perror("Socket creation error\n");
        exit(1);
    }
    //address creation
    char ip[100];
    int port;
    printf("Enter ip to host: ");
    scanf(" %[^\n]c%*c",ip);
    printf("enter port: ");
    scanf("%d",&port);
    struct sockaddr_in serverAddr,theirAddr;

    serverAddr.sin_family=AF_INET;
    serverAddr.sin_port=htons(port);
    inet_pton(serverAddr.sin_family,ip,&serverAddr.sin_addr);

    printf("Client connected to %s:%d\n", inet_ntoa(serverAddr.sin_addr),ntohs(serverAddr.sin_port));
    
    int msglen=500;
    char message1[msglen],message2[msglen];
    int fd;
    socklen_t theirAddrlen=sizeof theirAddr;
    while(1){
        printf("Enter first message: ");
        scanf(" %[^\n]c%*c",message1);

        if((fd=sendto(sockfd,message1,msglen - 1,0, (struct sock_addr*)&serverAddr, sizeof(serverAddr)))==-1)
        {
            perror("send error\n");
            exit(1);
        }
        printf("First message sent..\nenter second message: ");
        scanf(" %[^\n]c%*c",message2);

        if((fd=sendto(sockfd,message2,msglen - 1,0, (struct sock_addr*)&serverAddr, sizeof(serverAddr)))==-1)
        {
            perror("send error\n");
            exit(1);
        }
        printf("Second message sent\n");

        if((fd=recvfrom(sockfd,message1,(msglen*2)-1,0,(struct sock_addr*)&theirAddr, &theirAddrlen))==-1)
        {
            perror("Receive Error\n");
            exit(1);
        }

        printf("Received concatenated message: %s\n", message1);
        
    }
    close(sockfd);
    // receive
    // send

    //backend

    // logic
}