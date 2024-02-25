#include "imx6ul.h"
/*
* @description : 使能 I.MX6U 所有外设时钟
* @param : 无
* @return : 无
*/
void clk_enable(void)
{
    CCM->CCGR0 = 0xFFFFFFFF;
    CCM->CCGR1 = 0xFFFFFFFF;
    CCM->CCGR2 = 0xFFFFFFFF;
    CCM->CCGR3 = 0xFFFFFFFF;
    CCM->CCGR4 = 0xFFFFFFFF;
    CCM->CCGR5 = 0xFFFFFFFF;
    CCM->CCGR6 = 0xFFFFFFFF;
}

/*
* @description : 初始化 LED 对应的 GPIO
* @param : 无
* @return : 无
*/
void led_init(void)
{
    /* 1、初始化 IO 复用, 复用为 GPIO1_IO03 */
    IOMUX_SW_MUX->GPIO1_IO03 = 0x5;

    /* 2、配置 GPIO1_IO03 的 IO 属性
    *bit 16:0 HYS 关闭
    *bit [15:14]: 00 默认下拉
    *bit [13]: 0 kepper 功能
    *bit [12]: 1 pull/keeper 使能
    *bit [11]: 0 关闭开路输出
    *bit [7:6]: 10 速度 100Mhz
    *bit [5:3]: 110 R0/6 驱动能力
    *bit [0]: 0 低转换率
    */

    IOMUX_SW_PAD->GPIO1_IO03 = 0X10B0;
    /* 3、初始化 GPIO, GPIO1_IO03 设置为输出 */
    GPIO1->GDIR = 0X0000008;
    /* 4、设置 GPIO1_IO03 输出低电平，打开 LED0 */
    GPIO1->DR &= ~(1 << 3);
}

/*
* @description : 打开 LED 灯
* @param : 无
* @return : 无
*/
void led_on(void)
{
    /*
    * 将 GPIO1_DR 的 bit3 清零
    */
    GPIO1->DR &= ~(1<<3);
}

/*
* @description : 关闭 LED 灯
* @param : 无
* @return : 无
*/
void led_off(void)
{
    /*
    * 将 GPIO1_DR 的 bit3 置 1
    */
    GPIO1->DR |= (1<<3);
}

/*
* @description : 短时间延时函数
* @param - n : 要延时循环次数(空操作循环次数，模式延时)
* @return : 无
*/
void delay_short(volatile unsigned int n)
{
    while(n--){}
}

void delay(volatile unsigned int n)
{
    while(n--)
    {
        delay_short(0x7ff);
    }
}

int main(void)
{
    clk_enable(); /* 使能所有的时钟 */
    led_init(); /* 初始化 led */
    while(1) /* 死循环 */
    {
        led_off(); /* 关闭 LED */
        delay(1500); /* 延时大约 500ms */

        led_on(); /* 打开 LED */
        delay(500); /* 延时大约 500ms */
    }

    return 0;
}