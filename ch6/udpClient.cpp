#include <error.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <cstring>
#include <string>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>

#define MAXLINE 4096
#define SERV_PORT 5201

using namespace std;

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        error(1, 0, "usage: udpclient <IPaddress>");
    }

    int socket_fd;
    socket_fd = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in server_addr;
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERV_PORT);
    inet_pton(AF_INET, argv[1], &server_addr.sin_addr);

    socklen_t server_len = sizeof(server_addr);

    struct sockaddr *reply_addr;
    reply_addr = (struct sockaddr *)malloc(server_len);
    socklen_t len;

    string send_string;
    char send_line[MAXLINE], recv_line[MAXLINE + 1];

    while (cin >> send_string)
    {
        strcpy(send_line, send_string.c_str());
        cout << "now sending " << send_string << endl;
        size_t rt = sendto(socket_fd, send_line, strlen(send_line), 0, (struct sockaddr *)&server_addr, server_len);
        if (rt < 0)
        {
            error(1, errno, "send failed ");
        }
        cout << "send bytes: " << rt << endl;

        len = 0;
        int n = recvfrom(socket_fd, recv_line, MAXLINE, 0, reply_addr, &len);
        if (n < 0)
            error(1, errno, "recvfrom failed");
        recv_line[n] = 0;
        fputs(recv_line, stdout);
        fputs("\n", stdout);
    }

    exit(0);
}