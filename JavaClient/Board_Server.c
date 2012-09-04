/**
 * 板子上的服务端
 * 负责接受从PC上的Java客户端发来的信息
 */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#define LED_ON    1
#define LED_OFF   0
#define LED1     "1"
#define LED2     "2"
#define LED3     "3"
#define LED4     "4"
#define STOP_LED "q"

long led_flag1 = LED_ON;    /* LED1的标志位 */
long led_flag2 = LED_ON;    /* LED2的标志位 */
long led_flag3 = LED_ON;    /* LED3的标志位 */
long led_flag4 = LED_ON;    /* LED4的标志位 */

int main(int argc, char *argv[])
{
    int sock, connected;
    int recieved;
    int sin_size;
    int true = 1;
    char recv_buf[1024];
    
    struct sockaddr_in server;
    
    if (-1 == (sock = socket(AF_INET, SOCK_STREAM, 0)))
    {
        perror("socket error.");
        exit(0);
    }

    if (-1 == setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &true, sizeof(int)))
    {
        perror("setsockopt error.");
        exit(1);
    }
    
    server.sin_family = AF_INET;
    server.sin_port = htons(1991);
    server.sin_addr.s_addr = INADDR_ANY;
    bzero(&(server.sin_zero),8);
    
    if (-1 == bind(sock, (struct sockaddr *)&server, sizeof(struct sockaddr)))
    {
        perror("bind error.");
        exit(1);
    }

    if (-1 == listen(sock, 10))
    {
        perror("listen error.");
        exit(1);
    }

    printf ("Waiting...\n");
    fflush(stdout);

    do
    {
        sin_size = sizeof(struct sockaddr_in);

        connected = accept(sock, (struct sockaddr *)&server, &sin_size);

        printf("\nConnected.\nFrom (%s , %d)\n\n", inet_ntoa(server.sin_addr), ntohs(server.sin_port));

        do
        {
            recieved = recv(connected, recv_buf, 1024, 0);
            recv_buf[recieved] = '\0';

            if (0 == strcmp(recv_buf, STOP_LED))
            {
                close(connected);
                exit(1);
            }
            else if (0 == strcmp(recv_buf, LED1))
            {
                if (LED_OFF == led_flag1 % 2)
                    printf ("call led1 function, led1 off.\n");
                else
                    printf ("call led1 function, led1 on.\n");
                
                led_flag1++;
            }
            else if (0 == strcmp(recv_buf, LED2))
            {
                if (LED_OFF == led_flag2 % 2)
                    printf ("call led2 function, led2 off.\n");
                else
                    printf ("call led2 function, led2 on.\n");
                
                led_flag2++;
            }
            else if (0 == strcmp(recv_buf, LED3))
            {
                if (LED_OFF == led_flag3 % 2)
                    printf ("call led3 function, led3 off.\n");
                else
                    printf ("call led3 function, led3 on.\n");
                
                led_flag3++;
            }
            else if (0 == strcmp(recv_buf, LED4))
            {
                if (LED_OFF == led_flag4 % 2)
                    printf ("call led4 function, led4 off.\n");
                else
                    printf ("call led4 function, led4 on.\n");
                
                led_flag4++;
            }
            else
            {
                printf ("order error.\n");
            }
            
            fflush(stdout);
        } while (1);

    } while (1);

    close(sock);
    
    return 0;
}
