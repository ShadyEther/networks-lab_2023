#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MAX_MESSAGE_SIZE 1024

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <IP Address> <Port Number>\n", argv[0]);
        return 1;
    }

    const char *ipAddress = argv[1];
    const int portNumber = atoi(argv[2]);

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1) {
        perror("Socket creation failed");
        return 1;
    }



    struct sockaddr_in destAddr;
    destAddr.sin_family = AF_INET;
    destAddr.sin_port = htons(portNumber);
    inet_pton(AF_INET, ipAddress, &destAddr.sin_addr);

    printf("\nClient connected to: %s:%d\n",inet_ntoa(destAddr.sin_addr),ntohs(destAddr.sin_port));
    char message[MAX_MESSAGE_SIZE];

    printf("Enter the message: ");
    fgets(message, MAX_MESSAGE_SIZE, stdin);
    message[strlen(message) - 1] = '\0'; 

    sendto(sockfd, message, strlen(message), 0,
           (struct sockaddr *)&destAddr, sizeof(destAddr));

    char result[MAX_MESSAGE_SIZE * 10];
    socklen_t serverAddrLen = sizeof(destAddr);
    ssize_t bytesReceived = recvfrom(sockfd, result, sizeof(result), 0,
                                     (struct sockaddr *)&destAddr, &serverAddrLen);
    if (bytesReceived == -1) {
        perror("Error receiving data");
        close(sockfd);
        return 1;
    }

    result[bytesReceived] = '\0';

    printf("List of files received from the server:\n%s\n", result);

    close(sockfd);
    return 0;
}