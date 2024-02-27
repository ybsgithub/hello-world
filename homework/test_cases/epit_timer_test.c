#include "bsp_epittimer.h"

void epit_timer_test(void)
{   unsigned int frac = 0;
    unsigned int value = 66000000/2;
    epit1_init(frac, value);
}
