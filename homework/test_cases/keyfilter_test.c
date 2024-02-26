#include "bsp_keyfilter.h"
#include "bsp_delay.h"
#include "bsp_led.h"

extern unsigned int ms;

void keyfilter_test(void)
{
    unsigned char state = OFF;

    filterkey_init();

    while(1)			
	{	
		state = !state;
		led_switch(LED0, state);
		delay(ms);
	}
}