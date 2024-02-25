#include "bsp_clk.h"
#include "bsp_delay.h"
#include "bsp_led.h"
#include "beep.h"
#include "bsp_key.h"
#include "test.h"
#include "bsp_exit.h"
#include "bsp_init.h"

// #define LED_BEEP_TEST
// #define KEY_TEST
#define EXIT_TEST

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
}

int main()
{
    int_init(); //init irq
    imx6u_clkinit();
    clk_enable();

    led_init();
    beep_init();
    key_init();

#ifdef EXIT_TEST
    exit_init();
#endif

    while (1) {
        run_test_case();
    }
    return 0;
}