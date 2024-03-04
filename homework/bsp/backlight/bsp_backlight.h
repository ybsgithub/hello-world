#ifndef __BACKLIGHT_H
#define __BACKLIGHT_H

#include "imx6ul.h"

/* 背光PWM结构体 */
struct backlight_dev_struc
{	
	unsigned char pwm_duty;		/* 占空比	*/
};

void backlight_init(void);
void pwm1_enable(void);
void pwm1_setsample_value(unsigned int value);
void pwm1_setperiod_value(unsigned int value);
void pwm1_setduty(unsigned char duty);
void pwm1_irqhandler(void);

#endif
