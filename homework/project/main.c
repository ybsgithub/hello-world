#include "bsp_clk.h"
#include "bsp_delay.h"
#include "bsp_led.h"
#include "beep.h"
#include "bsp_key.h"
#include "test.h"
#include "bsp_exit.h"
#include "bsp_init.h"
#include "bsp_uart.h"
#include "bsp_lcd.h"
#include "bsp_lcdapi.h"
#include "bsp_rtc.h"
#include "stdio.h"

// #define LED_BEEP_TEST
// #define KEY_TEST
// #define EXIT_TEST
// #define EPIT_TIMER_TEST
// #define KEYFILTER_TEST
// #define UART_TEST
// #define LCD_TEST
// #define ICM_SPI_TEST
// #define AP3216C_TEST
// #define TOUCHSCREEN_TEST
#define BACKLIGHT_TEST

void imx6ul_hardfpu_enable(void)
{
	uint32_t cpacr;
	uint32_t fpexc;

	/* 使能NEON和FPU */
	cpacr = __get_CPACR();
	cpacr = (cpacr & ~(CPACR_ASEDIS_Msk | CPACR_D32DIS_Msk))
		   |  (3UL << CPACR_cp10_Pos) | (3UL << CPACR_cp11_Pos);
	__set_CPACR(cpacr);
	fpexc = __get_FPEXC();
	fpexc |= 0x40000000UL;	
	__set_FPEXC(fpexc);
}

void run_test_case(void)
{
#ifdef LED_BEEP_TEST
    led_beep_test();
#endif
#ifdef KEY_TEST
    key_test();
#endif
#ifdef EXIT_TEST
    exit_test();
#endif
#ifdef EPIT_TIMER_TEST
    epit_timer_test();
#endif
#ifdef KEYFILTER_TEST
    keyfilter_test();
#endif
#ifdef UART_TEST
    uart_test();
#endif
#ifdef LCD_TEST
    lcd_test();
#endif
#ifdef ICM_SPI_TEST
    icm_spi_test();
#endif
#ifdef AP3216C_TEST
    ap3216c_test();
#endif
#ifdef TOUCHSCREEN_TEST
    touchscreen_test();
#endif
#ifdef BACKLIGHT_TEST
    backlight_test();
#endif
}

int main()
{
	char buf[160];
	struct rtc_datetime rtcdate;
    unsigned char state = OFF;

    imx6ul_hardfpu_enable();	/* 使能I.MX6U的硬件浮点 			*/
    int_init(); //init irq
    imx6u_clkinit();
    delay_init();
    clk_enable();
    led_init();
    beep_init();
    key_init();
    uart_init();
    lcd_init();
    rtc_init();

#ifdef EXIT_TEST
    exit_init();
#endif

    tftlcd_dev.forecolor = LCD_RED;
	lcd_show_string(50, 10, 400, 24, 24, (char*)"ALPHA-IMX6UL RTC TEST");    /* 显示字符串 */
	lcd_show_string(50, 40, 200, 16, 16, (char*)"ATOM@ALIENTEK");  
	lcd_show_string(50, 60, 200, 16, 16, (char*)"2024/3/3");  
	tftlcd_dev.forecolor = LCD_BLUE;
	memset(buf, 0, sizeof(buf));

    rtcdate.year = 2024;
    rtcdate.month = 3;
    rtcdate.day = 3;
    rtcdate.hour = 22;
    rtcdate.minute = 58;
    rtcdate.second = 0;
    rtc_setdatetime(&rtcdate); /* 初始化时间和日期 */

	tftlcd_dev.forecolor = LCD_RED;
	lcd_fill(50, 90, 370, 110, tftlcd_dev.backcolor); /* 清屏 */
	lcd_show_string(50, 90, 200, 16, 16, (char*)"Current Time:");  			/* 显示字符串 */
	tftlcd_dev.forecolor = LCD_BLUE;

	while(1)					
	{	
		rtc_getdatetime(&rtcdate);
		sprintf(buf,"%d/%d/%d %d:%d:%d",rtcdate.year, rtcdate.month, rtcdate.day, rtcdate.hour, rtcdate.minute, rtcdate.second);
		lcd_fill(50,110, 300,130, tftlcd_dev.backcolor);
		lcd_show_string(50, 110, 250, 16, 16,(char*)buf);  /* 显示字符串 */
		
		state = !state;
		led_switch(LED0,state);
		delayms(1000);	/* 延时一秒 */

        run_test_case();
	}
	return 0;
}