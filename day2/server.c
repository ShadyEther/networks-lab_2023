/*
** A datagram sockets "server" demo
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
#define MYPORT 3000 // the port users will be connecting to
#define MAXBUFLEN 200
int main()
{
    int sockfd;
    struct sockaddr_in my_addr;    // my address information
    struct sockaddr_in their_addr; // connector's address information
    socklen_t addr_len;//socklen_t is the data type to store ip address length
    int numbytes;//how many bytes is the message ?
    char buf[MAXBUFLEN];//the message buffer or the message itself is stored here
    

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)//used to create a socket and check for errors..if error exit else continue
    {
        perror("socket");
        exit(1);
    }
    my_addr.sin_family = AF_INET;         // host byte order
    my_addr.sin_port = htons(MYPORT);     // short, network byte order
    // inet_pton(AF_INET, "127.0.0.1", &my_addr.sin_addr);

    const char *ipAddress = "localhost";
    inet_pton(AF_INET,ipAddress,&my_addr.sin_addr);//ip addrress converted to dot based

    // my_addr.sin_addr.s_addr = INADDR_ANY; // automatically fill with my IP i.e 127.0.0.1
    // memset(my_addr.sin_zero, '\0', sizeof my_addr.sin_zero);
    //bind is for assigning the server messages to a particular process on the pc..or bind them to a certain port number 
    if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof my_addr) == -1)
    {
        perror("bind");
        exit(1);
    }
    
    addr_len = sizeof their_addr;
    if ((numbytes = recvfrom(sockfd, buf, MAXBUFLEN - 1, 0,(struct sockaddr *)&their_addr, &addr_len)) == -1)
    {
        perror("recvfrom");
        exit(1);
    }
    printf("got packet from %s\n", inet_ntoa(their_addr.sin_addr));
    printf("packet is %d bytes long\n", numbytes);
    buf[numbytes] = '\0';
    printf("packet contains \"%s\"\n", buf);
    close(sockfd);
    return 0;
}