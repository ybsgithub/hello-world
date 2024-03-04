#include "bsp_clk.h"
#include "bsp_delay.h"
#include "bsp_led.h"
#include "beep.h"
#include "bsp_key.h"
#include "bsp_init.h"
#include "bsp_uart.h"
#include "bsp_lcd.h"
#include "bsp_lcdapi.h"
#include "bsp_rtc.h"
#include "bsp_backlight.h"
#include "stdio.h"
#include "bsp_gpio.h"

unsigned char duty = 0;

void gpio_rqhandler(void)
{
	/*
	 *采用延时消抖，中断服务函数中禁止使用延时函数！因为中断服务需要
	 *快进快出！！这里为了演示所以采用了延时函数进行消抖，后面我们会讲解
	 *定时器中断消抖法！！！
 	 */

	delay(10);
	if(gpio_pinread(GPIO1, 18) == 0)	/* 按键按下了  */
	{
		duty += 10;				/* 占空比加10% */
		if(duty > 100)			/* 如果占空比超过100%，重新从10%开始 */
			duty = 10;
	}
	
	gpio_clearintflags(GPIO1, 18); /* 清除中断标志位 */
}

void pwm_reflash_init(void)
{
    gpio_pin_config_t key_config;

    /* 1、设置IO复用 */
	IOMUXC_SetPinMux(IOMUXC_UART1_CTS_B_GPIO1_IO18,0);			/* 复用为GPIO1_IO18 */
	IOMUXC_SetPinConfig(IOMUXC_UART1_CTS_B_GPIO1_IO18,0xF080);

    /* 2、初始化GPIO为中断模式 */
	key_config.direction = kGPIO_DigitalInput;
	key_config.interruptMode = kGPIO_IntFallingEdge;
	key_config.outputLogic = 1;
	gpio_init(GPIO1, 18, &key_config);

    GIC_EnableIRQ(GPIO1_Combined_16_31_IRQn);				/* 使能GIC中对应的中断 */
	system_register_irqhandler(GPIO1_Combined_16_31_IRQn, (system_irq_handler_t)gpio_rqhandler, NULL);	/* 注册中断服务函数 */
	gpio_enableint(GPIO1, 18);
}

void backlight_test(void)
{
	unsigned char i = 0;
	unsigned char state = OFF;

    backlight_init();			/* 初始化背光PWM			 		*/ 

    tftlcd_dev.forecolor = LCD_RED;
	lcd_show_string(50, 10, 400, 24, 24, (char*)"ZERO-IMX6U BACKLIGHT PWM TEST");  
	lcd_show_string(50, 40, 200, 16, 16, (char*)"ATOM@ALIENTEK");  
	lcd_show_string(50, 60, 200, 16, 16, (char*)"2024/3/04");   
	lcd_show_string(50, 90, 400, 16, 16, (char*)"PWM Duty:   %");  
	tftlcd_dev.forecolor = LCD_BLUE;

    /* 设置默认占空比 10% */
	if(tftlcd_dev.id == ATKVGA)
		duty=100;	//VGA只能在满输出时才能亮屏
	else
		duty = 10;
	lcd_shownum(50 + 72, 90, duty, 3, 16);
	pwm1_setduty(duty);

    pwm_reflash_init();	

    while(1){
        lcd_shownum(50 + 72, 90, duty, 3, 16);
		pwm1_setduty(duty);		/* 设置占空比 */

        delayms(10);
		i++;
		if(i == 50)
		{	
			i = 0;
			state = !state;
			led_switch(LED0,state);	
		}
    }
}