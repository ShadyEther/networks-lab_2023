#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>

int main(int siz,char* argv[])
{
    if(siz!=3){
        perror("Usage: ./<filename>.c <IPaddress> <portnumber>");
        exit(1);
    }
    int sockfd;
    if((sockfd=socket(AF_INET,SOCK_DGRAM,0))==-1){
        perror("socket creation error!--\n");
        exit(1);
    }

    char *ip=argv[1];
    int port=atoi(argv[2]);
    struct sockaddr_in servaddr,theiraddr;
    servaddr.sin_family=AF_INET;
    servaddr.sin_port=htons(port);
    inet_pton(AF_INET,ip,&(servaddr.sin_addr));

    
    printf("Client connected to %s:%d\n",inet_ntoa(servaddr.sin_addr),ntohs(servaddr.sin_port));
    int msglen=1000;
    char msg[msglen];
    while (1){
        printf("Enter msg to send: ");
        scanf(" %[^\n]c%*c",msg);
        if(sendto(sockfd,msg,msglen-1,0,(struct sock_addr*)&servaddr,sizeof(servaddr))==-1){
            perror("send failed!\n");
            exit(1);
        }
        int num;
        if (recvfrom(sockfd, &num,sizeof(num), 0,NULL, NULL) == -1)
        {
            perror("receive failed!\n");
            exit(1);
        }
        printf("num= %d",num);
        for(int i=0;i<num;i++)
        {
            if (recvfrom(sockfd, msg,msglen-1, 0,NULL,NULL) == -1)
        {
            perror("receive failed!\n");
            exit(1);
        }
        printf("Received: %s\n",msg);
        }
        // if (recvfrom(sockfd, &num,sizeof(num), 0, (struct sock_addr *)&theiraddr, &theiraddrlen) == -1)
        // {
        //     perror("receive failed!\n");
        //     exit(1);
        // }
        // for(int i=0;i<)
        // if(strcmp(msg,"exit")==0)
        // {
        //     printf("its time to exit..\n");
        //     exit(1);
        // }
    }
}