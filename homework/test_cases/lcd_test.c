#include "bsp_delay.h"
#include "bsp_led.h"
#include "bsp_uart.h"
#include "stdio.h"
#include "bsp_lcd.h"
#include "bsp_lcdapi.h"

/* 背景颜色索引 */
unsigned int backcolor[10] = {
	LCD_BLUE, 		LCD_GREEN, 		LCD_RED, 	LCD_CYAN, 	LCD_YELLOW, 
	LCD_LIGHTBLUE, 	LCD_DARKBLUE, 	LCD_WHITE, 	LCD_BLACK, 	LCD_ORANGE

}; 

void lcd_test(void)
{
    unsigned char index = 0;
	unsigned char state = OFF;

	lcd_init();					/* 初始化LCD 			*/

	tftlcd_dev.forecolor = LCD_RED;	  
	while(1)				
	{	
		lcd_clear(backcolor[index]);
		delayms(1); 	  
		lcd_show_string(10, 40, 260, 32, 32,(char*)"ALPHA IMX6U"); 	
		lcd_show_string(10, 80, 240, 24, 24,(char*)"RGBLCD TEST");
		lcd_show_string(10, 110, 240, 16, 16,(char*)"ATOM@ALIENTEK");      					 
		lcd_show_string(10, 130, 240, 12, 12,(char*)"2019/8/14");	      					 
	    index++;
		if(index == 10)
			index = 0;      
		state = !state;
		led_switch(LED0,state);
		delayms(1000);

#if 0
		index++;
		if(index == 10)
			index = 0;
		lcd_fill(0, 300, 1023, 599, backcolor[index]);
		lcd_show_string(800,10,240,32,32,(char*)"INDEX=");  /*显示字符串				  */
		lcd_shownum(896,10, index, 2, 32); 					/* 显示数字，叠加显示	*/
		
		state = !state;
		led_switch(LED0,state);
		delayms(1000);	/* 延时一秒	*/
#endif
	}
}