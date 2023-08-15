#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#define SERVER_PORT 12345
#define MAX_ARRAY_SIZE 100
#define BUFFER_SIZE (MAX_ARRAY_SIZE * sizeof(int))

void sortArray(int *array, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

int main() {
    int sockfd;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t addrLen = sizeof(clientAddr);
    int receivedArray[MAX_ARRAY_SIZE];
    int receivedSize;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(SERVER_PORT);

    if (bind(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Binding failed");
        exit(EXIT_FAILURE);
    }

    printf("Server is listening...\n");

    while (1) {
        recvfrom(sockfd, &receivedSize, sizeof(receivedSize), 0, (struct sockaddr *)&clientAddr, &addrLen);
        printf("Received array size from client: %d\n", receivedSize);

        recvfrom(sockfd, receivedArray, BUFFER_SIZE, 0, (struct sockaddr *)&clientAddr, &addrLen);
        printf("Received array from client: ");
        for (int i = 0; i < receivedSize; i++) {
            printf("%d ", receivedArray[i]);
        }
        printf("\n");

        sortArray(receivedArray, receivedSize);

        sendto(sockfd, receivedArray, BUFFER_SIZE, 0, (struct sockaddr *)&clientAddr, addrLen);
        printf("Sorted array sent back to client\n");
    }

    close(sockfd);
    return 0;
}