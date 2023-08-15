#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>


int main()
{
    int sockfd;
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
        perror("Socket error");
        exit(1);
    }
    char ip[100];
    int port;
    printf("Enter ip: ");
    scanf(" %[^\n]c%*c",ip);
    printf("enter port: ");
    scanf("%d",&port);
    struct sockaddr_in servaddr,theiraddr;

    servaddr.sin_family=AF_INET;
    servaddr.sin_port=htons(port);
    inet_pton(AF_INET,ip,&servaddr.sin_addr);


    printf("Client connected to %s:%d\n",inet_ntoa(servaddr.sin_addr),ntohs(servaddr.sin_port));
    int array[500];
    int len;
    socklen_t theiraddrlen= sizeof theiraddr;
    int recvfd=0;
    while(1){
        printf("\nEnter size of array: ");
        scanf("%d",&len);

        if(sendto(sockfd,&len,sizeof(len),0,(struct sock_addr*)&servaddr,sizeof servaddr )==-1)
        {
            perror("Send failed");
            exit(1);
        }
        printf("Enter array elements: ");
        for(int i=0;i<len;i++)
        {
            scanf("%d",&array[i]);
        }

        if(sendto(sockfd,array,sizeof(int)*len,0,(struct sock_addr*)&servaddr,sizeof servaddr)==-1)
        {
            perror("Send failed");
            exit(1);
        }

        if(recvfd=recvfrom(sockfd,&array,sizeof(int)*len,0,NULL,NULL)==-1){
            perror("Receive Error");
            exit(1);
        }

        printf("Received sorted array is--\n");
        for(size_t i=0;i<len;i++)
        {
            printf("%d ",i,array[i]);
        }
        

    }

}