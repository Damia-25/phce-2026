#include <cstdio>

#include "pico/stdlib.h"
#include "hardware/gpio.h"

constexpr uint LED_PIN = 7;
constexpr uint BUTTON_PIN = 10;
constexpr uint32_t DEBOUNCE_MS = 0;

int main()
{
    stdio_init_all();

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_down(BUTTON_PIN);

    bool stable_state = false;
    bool last_reading = false;
    bool last_raw = false;

    uint32_t last_change_ms =
        to_ms_since_boot(get_absolute_time());

    while (true)
    {
        bool reading = gpio_get(BUTTON_PIN);

        uint32_t now_ms =
            to_ms_since_boot(get_absolute_time());

        // Raw, un-debounced edge on the pin.
        if (reading != last_raw)
        {
            printf(
                "raw   %s at %u ms\n",
                reading ? "rising (0->1)" : "falling (1->0)",
                now_ms
            );

            last_raw = reading;
        }

        // TODO 1:
        // Detect a raw change and restart the debounce timer.
        if (reading != last_reading)
        {
            last_reading = reading;
            last_change_ms = now_ms;
        }

        bool stable_state_changed = false;

        // TODO 2:
        // Accept the new state only after it has stayed stable
        // for at least DEBOUNCE_MS.
        if ((now_ms - last_change_ms >= DEBOUNCE_MS) &&
            (last_reading != stable_state))
        {
            stable_state = last_reading;
            stable_state_changed = true;
        }

        // TODO 3:
        // Print only when the debounced state changes.
        if (stable_state_changed)
        {
            printf(
                "%s\n",
                stable_state ? "pressed" : "released"
            );
        }

        // TODO 4:
        // LED follows the debounced state.
        gpio_put(LED_PIN, stable_state);

        sleep_ms(1);
    }
}