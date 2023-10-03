#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define MAXLINE 1024

int main(int argc, char **argv)
{
    int sockfd;
    char buffer[MAXLINE];
    struct sockaddr_in servaddr;

    char *msg1 = "Welcome to socket programming!";
    char *msg2 = "Hi!";
    char *msg3 = "This is a test message2";

    // Creating socket file descriptor
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));

    // Filling server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(24);
    servaddr.sin_addr.s_addr = inet_addr("10.1.0.1");

    int n, len;

    sendto(sockfd, (const char *)msg1, strlen(msg1), 0, (const struct sockaddr *)&servaddr, sizeof(servaddr));
    sendto(sockfd, (const char *)msg2, strlen(msg2), 0, (const struct sockaddr *)&servaddr, sizeof(servaddr));
    sendto(sockfd, (const char *)msg3, strlen(msg3), 0, (const struct sockaddr *)&servaddr, sizeof(servaddr));

    close(sockfd);
    return 0;
}