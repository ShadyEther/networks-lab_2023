#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h> 
#include <arpa/inet.h>

int main(int siz, char *argv[])
{
    if (siz != 3)
    {
        perror("Usage: ./<filename>.c <IPaddress> <portnumber>");
        exit(1);
    }
    int sockfd;
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
        perror("socket creation error!--\n");
        exit(1);
    }

    const char *ip = argv[1];
    const int port = atoi(argv[2]);
    struct sockaddr_in servaddr, theiraddr;
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);
    inet_pton(AF_INET, ip, &(servaddr.sin_addr));

    if (bind(sockfd, (struct socket_addr *)&servaddr, sizeof(servaddr)) == -1)
    {
        perror("bind error\n");
        exit(1);
    }

    printf("Server listening on %s:%d\n", inet_ntoa(servaddr.sin_addr), ntohs(servaddr.sin_port));
    int msglen = 500;
    char msg[msglen];

    socklen_t theiraddrlen = sizeof theiraddr;
    char *direc[1000];
    while (1)
    {
        int i;
        printf("Waiting to receive message from client...\n");
        if (recvfrom(sockfd, msg, msglen - 1, 0, (struct sock_addr *)&theiraddr, &theiraddrlen) == -1)
        {
            perror("receive failed!\n");
            exit(1);
        }
        printf("Received message from client: %s\n", msg);
        if (strcmp(msg, "list") == 0)
        {
            DIR *d;
            struct dirent *dir;
            d = opendir(".");
            i = 0;
            if (d)
            {
                while ((dir = readdir(d)) != NULL)
                {
                    direc[i] = dir->d_name;
                    printf("Sent: %s\n", direc[i]);
                    i++;
                }

                closedir(d);
            }
        }

        if (sendto(sockfd, i, sizeof(i), 0, (struct sock_addr *)&theiraddr, sizeof theiraddr) == -1)
        {
            perror("send failed!\n");
            exit(1);
        }
        for(int j=0;j<i;j++){
            if (sendto(sockfd, direc[j],sizeof(direc[j]), 0, (struct sock_addr *)&theiraddr, sizeof(theiraddr)) == -1)
        {
            perror("send failed!\n");
            exit(1);
        }
        printf("Sent: %s\n", direc[j]);
        }
        // if (sendto(sockfd, direc,, 0, (struct sock_addr *)&theiraddr, sizeof(theiraddr)) == -1)
        // {
        //     perror("send failed!\n");
        //     exit(1);
        // }
    }
}