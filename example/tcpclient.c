/* Server和Client交替发送和接收数据 */
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    int sock, bytes_recieved;    /* socket的文件描述福和收到文件的byte数 */
    char send_data[1024], recv_data[1024];    /* 收发数据缓冲区 */
    struct hostent *host;
    struct sockaddr_in server_addr;    /* sockaddr_in结构 */

    host = gethostbyname("127.0.0.1");    /* 本地IP */

        /* 初始化socket */
    if (-1 == (sock = socket(AF_INET, SOCK_STREAM, 0)))
    {
        perror("Socket");
        exit(1);
    }

        /* IP通信 */
    server_addr.sin_family = AF_INET;
        /* 服务器端口号1991 */
    server_addr.sin_port = htons(1991);
        /* 服务器IP地址 */
    server_addr.sin_addr = *((struct in_addr *)host->h_addr);
        /* 把sin_zero的8位置0 */
    bzero(&(server_addr.sin_zero),8); 
    
    if (connect(sock, (struct sockaddr *)&server_addr,
                sizeof(struct sockaddr)) == -1) 
    {
        perror("Connect");
        exit(1);
    }

    while(1)
    {
            /* 收数据 */
        bytes_recieved = recv(sock,recv_data,1024,0);
        recv_data[bytes_recieved] = '\0';
 
        if (strcmp(recv_data , "q") == 0 || strcmp(recv_data , "Q") == 0)
        {
            close(sock);
            break;
        }
        else
            printf("\nRecieved data = %s " , recv_data);
           
        printf("\nSEND (q or Q to quit) : ");
        gets(send_data);

            /* 发数据 */
        if (strcmp(send_data , "q") != 0 && strcmp(send_data , "Q") != 0)
            send(sock,send_data,strlen(send_data), 0);
        else
        {
            send(sock,send_data,strlen(send_data), 0);   
            close(sock);
            break;
        }
    }
    
    return 0;
}
