#include "bsp_delay.h"
#include "bsp_led.h"
#include "bsp_uart.h"
#include "bsp_lcd.h"
#include "bsp_lcdapi.h"
#include "bsp_rtc.h"
#include "bsp_ap3216c.h"
#include "stdio.h"

void ap3216c_test(void)
{
    unsigned short ir, als, ps;
    unsigned char state = OFF;

    while(ap3216c_init())		/* 检测不到AP3216C */
	{
		lcd_show_string(30, 130, 200, 16, 16, (char*)"AP3216C Check Failed!");
		delayms(500);
		lcd_show_string(30, 130, 200, 16, 16, (char*)"Please Check!        ");
		delayms(500);
	}

    lcd_show_string(30, 130, 200, 16, 16, (char*)"AP3216C Ready!");  
    lcd_show_string(30, 160, 200, 16, 16, (char*)" IR:");	 
	lcd_show_string(30, 180, 200, 16, 16, (char*)" PS:");	
	lcd_show_string(30, 200, 200, 16, 16, (char*)"ALS:");	
	tftlcd_dev.forecolor = LCD_BLUE;

    while(1)					
	{
		ap3216c_readdata(&ir, &ps, &als);		/* 读取数据		  	*/
		lcd_shownum(30 + 32, 160, ir, 5, 16);	/* 显示IR数据 		*/
        lcd_shownum(30 + 32, 180, ps, 5, 16);	/* 显示PS数据 		*/
        lcd_shownum(30 + 32, 200, als, 5, 16);	/* 显示ALS数据 	*/ 
		delayms(120);
		state = !state;
		led_switch(LED0,state);
	}
}