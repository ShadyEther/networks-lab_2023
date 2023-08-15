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

    // const char *ipAddress = argv[1];
    const char *ipAddress = "localhost";
    // const int portNumber = atoi(argv[2]);
    const int portNumber = 3000;

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1) {
        perror("Socket creation failed");
        return 1;
    }

    struct sockaddr_in myAddr;
    myAddr.sin_family = AF_INET;
    myAddr.sin_port = htons(portNumber);
    inet_pton(AF_INET, ipAddress, &myAddr.sin_addr);

    if (bind(sockfd, (struct sockaddr *)&myAddr, sizeof(myAddr)) == -1) {
        perror("Binding failed");
        return 1;
    }

    char receivedMessage1[MAX_MESSAGE_SIZE];
    char receivedMessage2[MAX_MESSAGE_SIZE];
    char concatenatedMessage[MAX_MESSAGE_SIZE * 2]; // To accommodate concatenated messages

    struct sockaddr_in senderAddr;
    socklen_t senderAddrLen = sizeof(senderAddr);

    while (1) {
        recvfrom(sockfd, receivedMessage1, MAX_MESSAGE_SIZE, 0,
                 (struct sockaddr *)&senderAddr, &senderAddrLen);
        receivedMessage1[MAX_MESSAGE_SIZE - 1] = '\0';
        printf("%s",receivedMessage1);

        recvfrom(sockfd, receivedMessage2, MAX_MESSAGE_SIZE, 0,
                 (struct sockaddr *)&senderAddr, &senderAddrLen);
        receivedMessage2[MAX_MESSAGE_SIZE - 1] = '\0';
        printf("%s",receivedMessage2);

        if (strcmp(receivedMessage1, "exit") == 0 || strcmp(receivedMessage2, "exit") == 0) {
            break;
        }

        strcpy(concatenatedMessage, receivedMessage1);
        strcat(concatenatedMessage, receivedMessage2);
        printf("%s",concatenatedMessage);
        sendto(sockfd, concatenatedMessage, strlen(concatenatedMessage), 0,
               (struct sockaddr *)&senderAddr, senderAddrLen);
    }

    close(sockfd);
    return 0;
}
