#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#define SERVER_PORT 12345
#define BUFFER_SIZE 1024

int calculateDigitSum(int num) {
    int sum = 0;
    while (num > 0) {
        sum += num % 10;
        num /= 10;
    }
    return sum;
}

int main() {
    int sockfd;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t addrLen = sizeof(clientAddr);
    char buffer[BUFFER_SIZE];

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
        int clientNum, digitSum;
        recvfrom(sockfd, &clientNum, sizeof(clientNum), 0, (struct sockaddr *)&clientAddr, &addrLen);
        printf("Received number from client: %d\n", clientNum);

        digitSum = calculateDigitSum(clientNum);

        sendto(sockfd, &digitSum, sizeof(digitSum), 0, (struct sockaddr *)&clientAddr, addrLen);
        printf("Sent digit sum back to client: %d\n", digitSum);
    }

    close(sockfd);
    return 0;
}
