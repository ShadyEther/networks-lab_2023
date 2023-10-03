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



    //binding
    int bindfd=bind(sockfd,(struct sock_addr*)&serverAddr,sizeof(serverAddr));
    if(bindfd==-1){
        perror("Binding failed.\n");
        exit(1);
    }

    printf("Server Listening on %s:%d\n", inet_ntoa(serverAddr.sin_addr),ntohs(serverAddr.sin_port));
    
    int msglen=500;
    char message1[msglen],message2[msglen];
    int fd;
    socklen_t theirAddrlen=sizeof theirAddr;
    while(1){
        printf("\nWaiting for client message 1\n");
        if((fd=recvfrom(sockfd,message1,msglen-1,0,(struct sock_addr*)&theirAddr, &theirAddrlen))==-1)
        {
            perror("Receive Error\n");
            exit(1);
        }
        printf("Received first message: %s\n",message1);
        printf("\nWaiting for client message 2\n");
        if ((fd=recvfrom(sockfd ,message2,msglen - 1, 0,(struct sock_addr *)&theirAddr, &theirAddrlen))==-1)
        {
            perror("Received failed\n");
            exit(1);
        }
        printf("received second message : %s \n",message2 );

        strcat(message1,message2);

        if((fd=sendto(sockfd,message1,msglen - 1,0, (struct sock_addr*)&theirAddr, sizeof theirAddr))==-1)
        {
            perror("send error\n");
            exit(1);
        }
        printf("Message sent after concatenating");



    }
    close(sockfd);
    // receive
    // send

    //backend

    // logic
}