#include "bsp_clk.h"
#include "bsp_delay.h"
#include "bsp_led.h"
#include "beep.h"

void led_breath(u8 roat)
{
    led_switch(LED0, ON);
    delay(roat);
    led_switch(LED0, OFF);
    delay(100 - roat);
}

void led_beep_test(void)
{
    int cnt = 0;
    uint8_t inv = 1;

    while (1) {
        led_breath(cnt);
        if (inv) {
            beep_switch(ON);
            cnt++;
        }else {
            beep_switch(OFF);
            cnt--;
        }
        if ( cnt == 100 || cnt == 0 ) {
            inv ^= 1;
        }
    }
}
