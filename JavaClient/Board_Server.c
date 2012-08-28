/**
 * 板子上的服务端
 * 负责接受从PC上的Java客户端发来的信息
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char char_led;    /* 接收到的客户端的LED编号 */
int  int_led;    /* 服务端的LED编号 */

static int led_flag1 = 0;    /* LED1的标志位 */
static int led_flag2 = 0;    /* LED2的标志位 */
static int led_flag3 = 0;    /* LED3的标志位 */
static int led_flag4 = 0;    /* LED4的标志位 */

/* 对LED进行操作 */
void action( int led_num );

int main(int argc, char *argv[])
{
	 do
	 {
		  /* 接收从java客户端发来的LED灯的编号 */
		  scanf( "%c", &char_led );
		  getchar(  );

		  int_led = char_led - '0';

		  /* 根据java客户端LED灯的编号对LED进行操作 */
		  action( int_led );
	 } while (1);
	 
	 return 0;
}

/* 对LED进行操作 */
void action( int led_num )
{
	 /* LED编号为1 */
	 if (1 == led_num)
	 {
		  led_flag1++;
		  
		  if (0 == led_flag1 % 2)
			   printf ("LED1 OFF...\n");
		  else
			   printf ("LED1 ON...\n");
	 }
	 /* LED编号为2 */
	 else if (2 == led_num)
	 {
		  led_flag2++;
		  
		  if (0 == led_flag2 % 2)
			   printf ("LED2 OFF...\n");
		  else
			   printf ("LED2 ON...\n");
	 }
	 /* LED编号为3 */
	 else if (3 == led_num)
	 {
		  led_flag3++;
		  
		  if (0 == led_flag3 % 2)
			   printf ("LED3 OFF...\n");
		  else
			   printf ("LED3 ON...\n");
	 }
	 /* LED编号为4 */
	 else if (4 == led_num)
	 {
		  led_flag4++;
		  
		  if (0 == led_flag4 % 2)
			   printf ("LED4 OFF...\n");
		  else
			   printf ("LED4 ON...\n");
	 }
	 /* 错误LED编号 */
	 else
	 {
		  perror( "LED NUMBER ERROR...\n" );
		  
		  exit( 0 );
	 }
}
