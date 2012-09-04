/* Server和Client交替发送和接收数据 */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int sock, connected, bytes_recieved , true = 1;  
    char send_data [1024] , recv_data[1024];       

    struct sockaddr_in server_addr,client_addr;
    int sin_size;

    if (-1 == (sock = socket(AF_INET, SOCK_STREAM, 0)))
    {
        perror("Socket");
        exit(1);
    }
    
        /* 设置套接口选项 */
    if (-1 == setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &true, sizeof(int)))
    {/* SOL_SOCKET层，socket可重用 */
        perror("Setsockopt");
        exit(1);
    }
        
    server_addr.sin_family = AF_INET;         
    server_addr.sin_port = htons(1991);
    server_addr.sin_addr.s_addr = INADDR_ANY; 
    bzero(&(server_addr.sin_zero),8); 

        /* 将套接字和机器上一定的端口关联起来 */
    if (-1 == bind(sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)))
    {
        perror("Unable to bind");
        exit(1);
    }

    if (-1 == listen(sock, 5))    /* 进入队列中允许的连接数目为5 */
    {
        perror("Listen");
        exit(1);
    }
		
    printf("\nTCPServer Waiting for client on port 1991");
        /* 刷新标准输出缓冲区，把输出缓冲区里的东西打印到标准输出设备上 */
    fflush(stdout);
    
    while(1)
    {  
        sin_size = sizeof(struct sockaddr_in);

        connected = accept(sock, (struct sockaddr *)&client_addr, &sin_size);

        printf("\n I got a connection from (%s , %d)",
               inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));

        while (1)
        {
            printf("\n SEND (q or Q to quit) : ");
            gets(send_data);
              
            if (0 == strcmp(send_data , "q") || 0 == strcmp(send_data , "Q"))
            {
                send(connected, send_data,strlen(send_data), 0); 
                close(connected);
                break;
            }
            else
                send(connected, send_data,strlen(send_data), 0);  

            bytes_recieved = recv(connected,recv_data,1024,0);

            recv_data[bytes_recieved] = '\0';

            if (0 == strcmp(recv_data , "q") || 0 == strcmp(recv_data , "Q"))
            {
                close(connected);
                break;
            }
            else 
                printf("\n RECIEVED DATA = %s " , recv_data);
            fflush(stdout);
        }
    }       

    close(sock);
    
    return 0;
}
