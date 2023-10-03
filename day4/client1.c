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
    printf("\nEnter the ip address of hosted server:");
    scanf(" %[^\n]c%*c",ipAddr);
    printf("\nEnter the port of hosted server:");
    scanf(" %d",&port);

    struct sockaddr_in hostAddr;
    hostAddr.sin_family=AF_INET;
    hostAddr.sin_port=htons(port);
    inet_pton(hostAddr.sin_family,ipAddr,&hostAddr.sin_addr);


    printf("\nClient connected to: %s:%d\n",inet_ntoa(hostAddr.sin_addr),ntohs(hostAddr.sin_port));
    int maxlen=500;
    char message[maxlen];
    struct sockaddr_in theirAddr;
    socklen_t theirAddrLen=sizeof theirAddr;
    while(1){

        printf("\nEnter something to send: ");
        scanf(" %[^\n]c%*c",message);

        int sendfd=sendto(sockfd,message, maxlen-1, 0,(struct sockaddr *)&hostAddr, sizeof(hostAddr));
        if(sendfd==-1){
            printf("\nError Sending");
        }
        printf("\nMessage sent: %s",message);

        printf(" \nWaiting to receive a message...\n");
        int num=0;

        int receivefd=recvfrom(sockfd, num,sizeof(num), 0,(struct sockaddr *)&theirAddr, &theirAddrLen);
        if(receivefd==-1){
            printf("\nError receiving!");
            exit(1);
        }

        for(int i=0;i<num;i++)
        {
            int receivefd=recvfrom(sockfd,message ,maxlen-1, 0,(struct sockaddr *)&theirAddr, &theirAddrLen);
        if(receivefd==-1){
            printf("\nError receiving!");
            exit(1);
        }
        message[receivefd]='\0';
        printf("\nReceived Message---: %s\n",message);
        }

        message[receivefd]='\0';
        printf("\nReceived Message---: %s\n",message);

        


    }
    close(sockfd);




    


}