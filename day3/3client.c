#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 12345
#define MAX_ARRAY_SIZE 100
#define BUFFER_SIZE (MAX_ARRAY_SIZE * sizeof(int))

int main() {
    int sockfd;
    struct sockaddr_in serverAddr;
    socklen_t addrLen = sizeof(serverAddr);
    int arrayToSend[MAX_ARRAY_SIZE];
    int arraySize;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);
    serverAddr.sin_port = htons(SERVER_PORT);

    printf("Enter the size of the integer array (max %d): ", MAX_ARRAY_SIZE);
    scanf("%d", &arraySize);
    if (arraySize <= 0 || arraySize > MAX_ARRAY_SIZE) {
        printf("Invalid array size.\n");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("Enter %d integers for the array:\n", arraySize);
    for (int i = 0; i < arraySize; i++) {
        scanf("%d", &arrayToSend[i]);
    }

    sendto(sockfd, &arraySize, sizeof(arraySize), 0, (struct sockaddr *)&serverAddr, addrLen);
    printf("Sent array size to server\n");

    sendto(sockfd, arrayToSend, BUFFER_SIZE, 0, (struct sockaddr *)&serverAddr, addrLen);
    printf("Sent array to server\n");

    recvfrom(sockfd, arrayToSend, BUFFER_SIZE, 0, NULL, NULL);
    printf("Received sorted array from server: ");
    for (int i = 0; i < arraySize; i++) {
        printf("%d ", arrayToSend[i]);
    }
    printf("\n");

    close(sockfd);
    return 0;
}