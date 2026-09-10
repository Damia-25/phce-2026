/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/stdlib.h"

// Pico W devices use a GPIO on the WIFI chip for the LED,
// so when building for Pico W, CYW43_WL_GPIO_LED_PIN will be defined
#ifdef CYW43_WL_GPIO_LED_PIN
#include "pico/cyw43_arch.h"
#endif

#define TIME_UNIT_MS 200

// Perform initialisation
int pico_led_init(void) {
#if defined(PICO_DEFAULT_LED_PIN)
    // A device like Pico that uses a GPIO for the LED will define PICO_DEFAULT_LED_PIN
    // so we can use normal GPIO functionality to turn the led on and off
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
    return PICO_OK;
#elif defined(CYW43_WL_GPIO_LED_PIN)
    // For Pico W devices we need to initialise the driver etc
    return cyw43_arch_init();
#endif
}

// Turn the led on or off
void pico_set_led(bool led_on) {
#if defined(PICO_DEFAULT_LED_PIN)
    // Just set the GPIO on or off
    gpio_put(PICO_DEFAULT_LED_PIN, led_on);
#elif defined(CYW43_WL_GPIO_LED_PIN)
    // Ask the wifi "driver" to set the GPIO on or off
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, led_on);
#endif
}

// Blink one dot: 1 time unit
void dot(void) {
    pico_set_led(true);
    sleep_ms(TIME_UNIT_MS);

    pico_set_led(false);
    sleep_ms(TIME_UNIT_MS);
}

// Blink one dash: 3 time units
void dash(void) {
    pico_set_led(true);
    sleep_ms(TIME_UNIT_MS * 3);

    pico_set_led(false);
    sleep_ms(TIME_UNIT_MS);
}

// Blink one letter represented as a Morse code string
void blink_letter(const char *morse_code) {
    for (int i = 0; morse_code[i] != '\0'; i++) {
        if (morse_code[i] == '.') {
            dot();
        } else if (morse_code[i] == '-') {
            dash();
        }
    }

    // dot() and dash() already add 1 unit of silence.
    // Add 2 more units to get a total 3-unit gap between letters.
    sleep_ms(TIME_UNIT_MS * 2);
}

int main() {
    int rc = pico_led_init();
    hard_assert(rc == PICO_OK);

    while (true) {
        blink_letter("....");    // H
        blink_letter(".");       // E
        blink_letter(".-..");    // L
        blink_letter(".--.");    // P
        blink_letter("-.-.--");  // !

        // blink_letter() already gives 3 units after "!".
        // Add 4 more to make a total gap of 7 units before repeating.
        sleep_ms(TIME_UNIT_MS * 4);
    }
}