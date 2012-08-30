/**
 * 板子上的服务端
 * 负责接受从PC上的Java客户端发来的信息
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>

#define LED_ON   1
#define LED_OFF  0
#define LED1     1
#define LED2     2
#define LED3     3
#define LED4     4
#define STOP_LED 0

char char_led;    /* 接收到的客户端的LED编号 */
int  int_led;    /* 服务端的LED编号 */

static int led_flag  = LED_ON;    /* 停止标志位 */
static int led_flag1 = LED_ON;    /* LED1的标志位 */
static int led_flag2 = LED_ON;    /* LED2的标志位 */
static int led_flag3 = LED_ON;    /* LED3的标志位 */
static int led_flag4 = LED_ON;    /* LED4的标志位 */

/* 对LED进行操作 */
void action( int led_num );

int main(int argc, char *argv[])
{
	 struct sockaddr_in servaddr;

	 /* 建立一个Socket */
     int clisock = socket( AF_INET,    /* 使用IPV4 */
								  SOCK_STREAM,    /* 使用TCP协议进行Stream Communication */
								  0 );    /* 使用常用的协议进行通信 */

	 memset(&servaddr, 0, sizeof(servaddr));
	 servaddr.sin_family = AF_INET;
	 servaddr.sin_port = htons(48000);
	 servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");    /* 本地 */
	 
	 do
	 {
		  /* 接收从java客户端发来的LED灯的编号 */
		  scanf( "%c", &char_led );
		  getchar(  );

		  int_led = char_led - '0';

		  /* 根据java客户端LED灯的编号对LED进行操作 */
		  action( int_led );
	 } while (LED_ON == led_flag);

	 close( clisock );    /* 关闭Socket */
	 
	 return 0;
}

/* 对LED进行操作 */
void action( int led_num )
{
	 /* 停止位为0 */
	 if (STOP_LED == led_num)
		  led_flag = LED_OFF;
	 /* LED编号为1 */
	 else if (LED1 == led_num)
	 {
		  /* 启用控制函数 */
		  if (LED_OFF == led_flag1 % 2)
			   printf ("LED1 OFF...\n");
		  else
			   printf ("LED1 ON...\n");

		  led_flag1++;
	 }
	 /* LED编号为2 */
	 else if (LED2 == led_num)
	 {
		  if (LED_OFF == led_flag2 % 2)
			   printf ("LED2 OFF...\n");
		  else
			   printf ("LED2 ON...\n");

		  led_flag2++;
	 }
	 /* LED编号为3 */
	 else if (LED3 == led_num)
	 {
		  if (LED_OFF == led_flag3 % 2)
			   printf ("LED3 OFF...\n");
		  else
			   printf ("LED3 ON...\n");

		  led_flag3++;
	 }
	 /* LED编号为4 */
	 else if (LED4 == led_num)
	 {
		  if (LED_OFF == led_flag4 % 2)
			   printf ("LED4 OFF...\n");
		  else
			   printf ("LED4 ON...\n");

		  led_flag4++;
	 }
	 /* 错误LED编号 */
	 else
	 {
		  perror( "LED NUMBER ERROR...\n" );
		  
		  exit( 0 );
	 }
}
