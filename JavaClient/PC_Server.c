#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char char_led;
int int_led;

static int flag1 = 0;
static int flag2 = 0;
static int flag3 = 0;
static int flag4 = 0;

void action( int led_num );

int main(int argc, char *argv[])
{
	 do
	 {
		  scanf( "%c", &char_led );
		  getchar(  );

		  int_led = char_led - '0';

		  action( int_led );
	 } while (1);
	 
	 return 0;
}

void action( int led_num )
{
	 if (1 == led_num)
	 {
		  flag1++;
		  if (0 == flag1 % 2)
			   printf ("LED1 OFF...\n");
		  else
			   printf ("LED1 ON...\n");
	 }
	 else if (2 == led_num)
	 {
		  flag2++;
		  if (0 == flag2 % 2)
			   printf ("LED2 OFF...\n");
		  else
			   printf ("LED2 ON...\n");
	 }
	 else if (3 == led_num)
	 {
		  flag3++;
		  if (0 == flag3 % 2)
			   printf ("LED3 OFF...\n");
		  else
			   printf ("LED3 ON...\n");
	 }
	 else if (4 == led_num)
	 {
		  flag4++;
		  if (0 == flag4 % 2)
			   printf ("LED4 OFF...\n");
		  else
			   printf ("LED4 ON...\n");
	 }
	 else
	 {
		  perror( "LED NUMBER ERROR...\n" );
		  exit( 0 );
	 }
}
