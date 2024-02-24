#include "bsp_clk.h"
#include "bsp_delay.h"
#include "bsp_led.h"

void led_breath(u8 roat)
{
    led_switch(LED0, ON);
    delay(roat);
    led_switch(LED0, OFF);
    delay(100 - roat);
}

int main()
{
    int cnt = 0;
    uint8_t inv = 1;
    clk_enable();
    led_init();

    while (1) {
        led_breath(cnt);
        if (inv) {
            cnt++;
        }else {
            cnt--;
        }
        if ( cnt == 100 || cnt == 0 ) {
            inv ^= 1;
        }
    }
}