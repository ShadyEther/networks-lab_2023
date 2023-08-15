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

    char message1[MAX_MESSAGE_SIZE];
    char message2[MAX_MESSAGE_SIZE];
    char concatenatedMessage[MAX_MESSAGE_SIZE * 2]; // Assuming both messages can be MAX_MESSAGE_SIZE

    while (1) {
        printf("Enter the first message: ");
        fgets(message1, MAX_MESSAGE_SIZE, stdin);
        // char ch[]
        // for(int i=0;)
        printf("Enter the second message: ");
        fgets(message2, MAX_MESSAGE_SIZE, stdin);

        sendto(sockfd, message1, strlen(message1), 0,
               (struct sockaddr *)&destAddr, sizeof(destAddr));
        sendto(sockfd, message2, strlen(message2), 0,
               (struct sockaddr *)&destAddr, sizeof(destAddr));

        if (strcmp(message1, "exit\n") == 0 || strcmp(message2, "exit\n") == 0) {
            break;
        }

        recvfrom(sockfd, concatenatedMessage, MAX_MESSAGE_SIZE * 2, 0, NULL, NULL);
        printf("Received concatenated message: %s", concatenatedMessage);
    }

    close(sockfd);
    return 0;
}
