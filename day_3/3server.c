#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

void sort(int array[],int size)
{
    for(int i=0;i<size-1;i++)
    {
        for(int j=i+1;j<size;j++)
        {
            if(array[j]<array[i])
            {
                int tmp=array[j];
                array[j]=array[i];
                array[i]=tmp;
            }
        }
    }

}

int main()
{
    int sockfd;
    if ((sockfd = socket(AF_INET, SOCK_DGRAM,0) )== -1)
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

    // servaddr.sin_family=AF_INET;
    // servaddr.sin_port=htons(port);
    // inet_pton(AF_INET,ip,&(servaddr.sin_addr));

    servaddr.sin_family=AF_INET;
    servaddr.sin_port=htons(port);
    inet_pton(servaddr.sin_family,ip,&servaddr.sin_addr);

    if(bind(sockfd,(struct sock_addr*)&servaddr,sizeof servaddr )==-1)
    {
        perror("bind failed");
        exit(1);
    }

    printf("Server listening on %s:%d\n",inet_ntoa(servaddr.sin_addr),ntohs(servaddr.sin_port));
    int array[500];
    int size;

    socklen_t theiraddrlen= sizeof theiraddr;
    while(1){
        printf("Waiting for client response\n");
        if(recvfrom(sockfd,&size,sizeof(size),0,(struct sock_addr*)&theiraddr,&theiraddrlen)==-1){
            perror("Receive Error");
            exit(1);
        }
        printf("Received size: %d\nWaiting for array...\n",size);

        if(recvfrom(sockfd,&array,sizeof(array),0,(struct sock_addr*)&theiraddr,&theiraddrlen)==-1){
            perror("Receive Error");
            exit(1);
        }

        printf("Received array is--\n");
        for(int i=0;i<size;i++)
        {
            printf("a[%d]:%d\n",i,array[i]);
        }

        sort(array,size);

        if(sendto(sockfd,array,sizeof(int)*size,0,(struct serv_addr*)&theiraddr,sizeof theiraddr)==-1)
        {
            perror("Send failed");
            exit(1);
        }


    }

}