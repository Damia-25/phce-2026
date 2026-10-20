
#include <iostream>

#include "hardware/gpio.h"
#include "pico/stdlib.h"

constexpr uint LED_PIN {7};

// Pass by value: gets a copy
void toggle_by_value(bool led_on)
{
    led_on = !led_on;
}

// Pass by pointer: gets the address
void toggle_by_pointer(bool* led_on)
{
    // TODO 1: Flip the bool that led_on points at
    *led_on = !*led_on;
}

// Pass by reference: gets another name for the same bool
void toggle_by_reference(bool& led_on)
{
    // TODO 2: Flip the bool
    led_on = !led_on;
}

int main()
{
    stdio_init_all();

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    bool led_on {false};

    while (true)
    {
       toggle_by_reference(led_on);

        gpio_put(LED_PIN, led_on);

        std::cout << "led_on is "
                  << (led_on ? "ON" : "OFF")
                  << std::endl;

        sleep_ms(500);
    }
}
