#include "bsp_delay.h"
#include "bsp_led.h"
#include "bsp_uart.h"

void uart_test(void)
{
    unsigned char a=0;
	unsigned char state = OFF;

    uart_init();

    while(1)				
	{	
		puts("请输入1个字符:");
		a=getc();
		putc(a);	//回显功能
		puts("\r\n");

		//显示输入的字符
		puts("您输入的字符为:");
		putc(a);
		puts("\r\n\r\n");
		
		state = !state;
		led_switch(LED0,state);
	}
}