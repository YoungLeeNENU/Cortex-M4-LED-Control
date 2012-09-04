/**
 * PC上的客户端，负责向板子发送LED信息
*/
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#define STOP_LED "q"

int main(int argc, char *argv[])
{
    int sock;
    char send_buf[1024];
    
    struct hostent *host;
    struct sockaddr_in client;
    
        /* host = gethostbyname("192.168.0.10"); */
    host = gethostbyname("127.0.0.1");

    if (-1 == (sock = socket(AF_INET, SOCK_STREAM, 0)))
    {
        perror("socket error.");
        exit(1);
    }

    client.sin_family = AF_INET;
    client.sin_port = htons(1991);
    client.sin_addr = *((struct in_addr *)host->h_addr);
    bzero(&(client.sin_zero),8);

    if (-1 == connect(sock, (struct sockaddr *)&client, sizeof(struct sockaddr)))
    {
        perror("connect error.");
        exit(1);
    }

    do
    {
        gets(send_buf);

        if (0 != strcmp(send_buf, STOP_LED))
            send(sock, send_buf, strlen(send_buf), 0);
        else
        {
            send(sock, send_buf, strlen(send_buf), 0);
            close(sock);
            break;
        }
    } while (1);
    
    return 0;
}
