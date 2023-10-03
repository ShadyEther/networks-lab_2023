#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <dirent.h> // Include this header for directory functions

#define MAX_MESSAGE_SIZE 1024

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <IP Address> <Port Number>\n", argv[0]);
        return 1;
    }

    const char *ipAddress = argv[1];
    const int portNumber = atoi(argv[2]);

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1)
    {
        perror("Socket creation failed");
        return 1;
    }

    struct sockaddr_in myAddr;
    myAddr.sin_family = AF_INET;
    myAddr.sin_port = htons(portNumber);
    inet_pton(AF_INET, ipAddress, &myAddr.sin_addr);

    if (bind(sockfd, (struct sockaddr *)&myAddr, sizeof(myAddr)) == -1)
    {
        perror("Binding failed");
        return 1;
    }
    printf("\nServer listening on: %s:%d\n",inet_ntoa(myAddr.sin_addr),ntohs(myAddr.sin_port));
    

    char receivedMessage[MAX_MESSAGE_SIZE];

    struct sockaddr_in senderAddr;
    socklen_t senderAddrLen = sizeof(senderAddr);

    recvfrom(sockfd, receivedMessage, MAX_MESSAGE_SIZE, 0,
             (struct sockaddr *)&senderAddr, &senderAddrLen);

    if (strcmp(receivedMessage, "list") == 0)
    {
        DIR *dir = opendir(".");
        if (dir == NULL)
        {
            perror("Error opening directory");
            return 1;
        }

        char result[MAX_MESSAGE_SIZE * 10] = "";
        struct dirent *entry;
        while ((entry = readdir(dir)) != NULL)
        {
            if (entry->d_type == DT_REG)
            {
                strcat(result, entry->d_name);
                strcat(result, "\n");
            }
        }
        closedir(dir);

        sendto(sockfd, result, strlen(result), 0,
               (struct sockaddr *)&senderAddr, senderAddrLen);
    }

    close(sockfd);
    return 0;
}