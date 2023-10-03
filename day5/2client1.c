
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <string.h>
main()
{
  int i, sockfd, a, b, p = 6, q = 7, r;
  char buf[100];
  struct sockaddr_in sa;

  sockfd = socket(AF_INET, SOCK_STREAM, 0);

  sa.sin_family = AF_INET;
  sa.sin_addr.s_addr = inet_addr("127.0.0.1"); // Loop back IP address
  sa.sin_port = 60018;

  /* With the information specified in serv_addr, the connect()
  system call establishes a connection with the server process.*/
  i = connect(sockfd, (struct sockaddr *)&sa, sizeof(sa));
  printf("\nClient connected to: %s:%d\n", inet_ntoa(sa.sin_addr), ntohs(sa.sin_port));

  while (1)
  {
    for (i = 0; i < 100; i++)
      buf[i] = '\0';
    printf("Enter message: ");
    scanf("%s", buf);
    send(sockfd, buf, 100, 0);

    for (i = 0; i < 100; i++)
      buf[i] = '\0';
    recv(sockfd, buf, 100, 0);
    printf("Message received: %s\n", buf);
  }

  close(sockfd);
}
