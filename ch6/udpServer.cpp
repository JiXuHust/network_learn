#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <cstring>
#include <string>
#include <iostream>
#include <signal.h>
#define MAXLINE 4096

using namespace std;
static int count = 0;

static void receivefrom_int(int sig)
{
    cout << "received " << count << " datagrams" << endl;
    exit(0);
}

int main(int argc, char **argv)
{
    int socket_fd;

    socket_fd = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in servaddr;
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(5201);

    bind(socket_fd, (struct sockaddr *)&servaddr, sizeof(servaddr));

    char message[MAXLINE];

    signal(SIGINT, receivefrom_int);

    struct sockaddr_in cliaddr;
    socklen_t len = sizeof(cliaddr);

    for (;;)
    {
        int n = recvfrom(socket_fd, message, MAXLINE, 0, (struct sockaddr *)&cliaddr, &len);
        message[n] = '\0';
        std::cout << "received " << n << " bytes: " << message << std::endl;

        string sendString(message);
        sendString.insert(0, "Hi,");
        char *send_line = new char[sendString.length() + 1];
        strcpy(send_line, sendString.c_str());
        cout << "sending " << send_line << endl;
        sendto(socket_fd, send_line, strlen(send_line), 0, (struct sockaddr *)&cliaddr, len);

        count++;
    }
}
