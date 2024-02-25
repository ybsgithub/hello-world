#include "bsp_clk.h"
#include "bsp_delay.h"
#include "bsp_led.h"
#include "beep.h"
#include "bsp_key.h"
#include "test.h"

// #define LED_BEEP_TEST
#define KEY_TEST

void run_test_case(void)
{
#ifdef LED_BEEP_TEST
    led_beep_test();
#endif
#ifdef KEY_TEST
    key_test();
#endif
}

int main()
{
    while (1) {
        run_test_case();
    }
    return 0;
}