#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>

int main(int siz,char* argv[])
{
    int sockfd;
    if((sockfd=socket(AF_INET,SOCK_DGRAM,0))==-1){
        perror("socket creation error!--\n");
        exit(1);
    }

    const char *ip=argv[1];
    const int port=atoi(argv[2]);
    struct sockaddr_in servaddr,theiraddr;
    servaddr.sin_family=AF_INET;
    servaddr.sin_port=htons(port);
    inet_pton(AF_INET,ip,&(servaddr.sin_addr));

    if(bind(sockfd,(struct socket_addr*)&servaddr,sizeof(servaddr))==-1)
    {
        perror("bind error\n");
        exit(1);
    }
    
    printf("Server listening on %s:%d\n",inet_ntoa(servaddr.sin_addr),ntohs(servaddr.sin_port));
    int msglen=500;
    char msg[msglen];

    socklen_t theiraddrlen=sizeof theiraddr;
    while (1){
        printf("Waiting to receive message from client...\n");
        if(recvfrom(sockfd,msg,msglen-1,0,(struct sock_addr*)&theiraddr,&theiraddrlen)==-1){
            perror("receive failed!\n");
            exit(1);
        }
        printf("Received message from client: %s\n", msg);
        if(strcmp(msg,"exit")==0)
        {
            printf("its time to exit..\n");
            exit(1);
        }
    }
}