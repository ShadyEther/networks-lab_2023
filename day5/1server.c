
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<fcntl.h>
#include<string.h>
main()
{
int sockfd,fd1, length,i,x,y,sum;
char buf[100],p[3]; /* We will use this buffer for communication */
struct sockaddr_in sa,ta1;

sockfd=socket(AF_INET,SOCK_STREAM,0);

 sa.sin_family=AF_INET;
 sa.sin_addr.s_addr=INADDR_ANY;
 sa.sin_port=60018;

 i=bind(sockfd,(struct sockaddr *)&sa,sizeof(sa));
 printf("test %d%d\n",sockfd,i);

listen(sockfd,5);

 length=sizeof(sa);
 fd1=accept(sockfd, (struct sockaddr *) &ta1,&length);
/* We initialize the buffer, copy the message to it,
and send the message to the client. */

while(1){
if(fd1==-1){
    perror("Error!");
}
else{
    printf("One client connected");
}
//receive from client
for(i=0; i < 100; i++) buf[i] = '\0';
			ssize_t size=recv(fd1, buf, 100, 0);
			


//  for(i=0; i < 100; i++) buf[i] = '\0';
			// strcpy(buf,"Message from server");
            // printf("\nClient connected to: %s:%d\n",inet_ntoa(sa.sin_addr),ntohs(sa.sin_port));
            printf("\nMessage received from client %s:%d: %s\nNumber of bits: %d\n",inet_ntoa(ta1.sin_addr),ntohs(ta1.sin_port),buf,size);
			send(fd1, buf, 100, 0);
            printf("Message echoed backto client\n",buf);

}
close(fd1);
}
