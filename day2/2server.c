#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <arpa/inet.h>

int main()
{
    int sockfd=socket(AF_INET,SOCK_DGRAM,0);//socket created
    if (sockfd==-1){
        perror("\nSocket creation failed :(");
        exit(1);
    }

    char ipAddr[100];
    int port;
    printf("\nEnter the ip address to host:");
    scanf(" %[^\n]c%*c",ipAddr);
    printf("\nEnter the port to host:");
    scanf(" %d",&port);

    struct sockaddr_in hostAddr;
    hostAddr.sin_family=AF_INET;
    hostAddr.sin_port=htons(port);
    inet_pton(hostAddr.sin_family,ipAddr,&hostAddr.sin_addr);

    int bindfd=bind(sockfd,(struct sock_addr*)&hostAddr,sizeof(hostAddr));
    if(bindfd==-1){
        perror("\nBinding Error! :(");
        exit(1);
    }


    printf("\nServer listening on: %s:%d\n",inet_ntoa(hostAddr.sin_addr),ntohs(hostAddr.sin_port));
    
    int maxlen=500;
    
    char message[maxlen];
    
    struct sockaddr_in theirAddr;
    
    socklen_t theirAddrLen=sizeof theirAddr;
    
    

    
    while(1){
        printf(" \nWaiting to receive message from client\n");
        int receivefd=recvfrom(sockfd, message, maxlen - 1, 0,(struct sockaddr *)&theirAddr, &theirAddrLen);
        if(receivefd==-1){
            printf("\nError receiving!");
            exit(1);
        }
        message[receivefd-1]='\0';
        printf("\nReceived Message---\n%s\n",message);

        printf("\nEnter something to send: ");
        scanf(" %[^\n]c%*c",message);

        int sendfd=sendto(sockfd,message, maxlen-1, 0,(struct sockaddr *)&theirAddr, theirAddrLen);
        if(sendfd==-1){
            printf("\nError Sending");
            exit(1);
        }
        printf("\nMessage sent: %s",message);
        
    }

        close(sockfd);


    




    


}