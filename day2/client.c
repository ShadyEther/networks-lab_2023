/*
** A datagram "client" demo
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define SERVERPORT 3000 // the port users will be connecting to
int main()
{
    int sockfd;
    struct sockaddr_in their_addr; // connector's address information
    // struct hostent *he;
    int numbytes;//message length
    char arg[30];//message holder
    //socket created and error handled
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
        perror("socket");
        exit(1);
    }

    their_addr.sin_family =AF_INET;                             // host byte order
    their_addr.sin_port = htons(SERVERPORT); // short, network byte order
    const char *ipAddress = "localhost";
    inet_pton(AF_INET,ipAddress,&their_addr.sin_addr);//ip addrress converted to dot based
    // their_addr.sin_addr.s_addr = inet_addr("localhost");
    // memset(their_addr.sin_zero, '\0', sizeof their_addr.sin_zero);
    printf("Enter a message\n");
    gets(arg);
    if ((numbytes = sendto(sockfd, arg, strlen(arg), 0,
                           (struct sockaddr *)&their_addr, sizeof their_addr)) == -1)
    {
        perror("sendto");
        exit(1);
    }
    printf("sent %d bytes to %s\n", numbytes, inet_ntoa(their_addr.sin_addr));
    close(sockfd);
    return 0;
}