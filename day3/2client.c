#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 12345
#define BUFFER_SIZE 1024

int main() {
    int sockfd;
    struct sockaddr_in serverAddr;
    socklen_t addrLen = sizeof(serverAddr);
    int numToSend, digitSum;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);
    serverAddr.sin_port = htons(SERVER_PORT);

    printf("Enter an integer: ");
    scanf("%d", &numToSend);

    sendto(sockfd, &numToSend, sizeof(numToSend), 0, (struct sockaddr *)&serverAddr, addrLen);
    printf("Sent number to server: %d\n", numToSend);

    recvfrom(sockfd, &digitSum, sizeof(digitSum), 0, NULL, NULL);
    printf("Received digit sum from server: %d\n", digitSum);

    close(sockfd);
    return 0;
}
