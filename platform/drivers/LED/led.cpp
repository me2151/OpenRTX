#include <hwconfig.h>
#ifdef LED_PRESENT
#include <gpio.h>
#endif
#include <stdint.h>

uint32_t last_standby_toggle_tick;
uint32_t last_standby_swap_tick;
bool * standby_active;
bool led_on = false;
bool red_on = false;

void led_tick(uint32_t* tick) {
    if (standby_active) {
        if ((*tick - last_standby_swap_tick) > (uint8_t) 150) {
            // 150ms passed, switch active LED
            red_on != red_on;
            last_standby_swap_tick = *tick;
        } else if ((*tick - last_standby_toggle_tick) > (uint16_t) 5000)
        {
            // 5 seconds has passed, toggle LED
            led_on = !led_on;
            last_standby_toggle_tick = *tick;
        }

        #ifdef LED_PRESENT
        if(led_on) {
            gpio_setPin((red_on) ? RED_LED:GREEN_LED);
            gpio_clearPin((red_on) ? GREEN_LED:RED_LED);
        } else {
            gpio_clearPin(GREEN_LED);
            gpio_clearPin(RED_LED);
        }
        #endif
    }
}

void led_link_standby_state(bool * standby) {
    standby_active = standby;
}
