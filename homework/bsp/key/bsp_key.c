#include "bsp_key.h"
#include "bsp_gpio.h"
#include "bsp_delay.h"

void key_init(void)
{
    gpio_pin_config_t key_config;
    IOMUXC_SetPinMux(IOMUXC_UART1_CTS_B_GPIO1_IO18, 0);
    IOMUXC_SetPinConfig(IOMUXC_UART1_CTS_B_GPIO1_IO18, 0xF080);

    key_config.direction = kGPIO_DigitalInput;
    gpio_init(GPIO1, 18, &key_config);
}

int key_getvalue(void)
{
    int ret = 0;
    static unsigned char release = 1;

    if ((release == 1) && gpio_pinread(GPIO1, 18)) {
        delay(10);
        release = 0;
        if (gpio_pinread(GPIO1, 18) == 0)
            ret = KEY0_VALUE;
    } else if (gpio_pinread(GPIO1, 18) == 1) {
        ret = 0;
        release = 1;
    }
    return ret;
}