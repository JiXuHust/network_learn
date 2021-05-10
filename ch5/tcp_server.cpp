#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "read/read.h"

void read_data(int sockfd)
{
    char buf[1024];
    size_t n;

    int time = 0;
    for (;;)
    {
        std::cout << "block in read" << std::endl;
        if ((n = readn(sockfd, buf, 1024)) == 0)
            return;
        time++;
        std::cout << "read 1K data " << time << " times" << std::endl;
        usleep(10000);
    }
}

int main(int argc, char **argv)
{
    int listenfd, connfd;
    socklen_t client_len;
    struct sockaddr_in cliaddr, servaddr;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(12345);

    bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    listen(listenfd, 1024);

    for (;;)
    {
        client_len = sizeof(cliaddr);
        connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &client_len);
        read_data(connfd);
        close(connfd);
    }
}
