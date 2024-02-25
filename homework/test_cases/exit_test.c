#include "bsp_exit.h"
#include "bsp_delay.h"
#include "bsp_led.h"

void exit_test(void)
{
    unsigned char state = OFF;

    while (1) {
        state = !state;
        led_switch(LED0, state);
        delay(500);
    }
}