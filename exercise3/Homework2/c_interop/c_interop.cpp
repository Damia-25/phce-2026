#include "hardware/gpio.h"
#include "pico/stdlib.h"

constexpr unsigned LED_PIN = 7;

void led_set(unsigned pin, int value);

class LedController
{
public:
    explicit LedController(unsigned pin) : pin_(pin) {}

    void set(bool on) { led_set(pin_, on ? 1 : 0); }

private:
    unsigned pin_;
};

int main()
{
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    LedController led(LED_PIN);
    led.set(true);

    while (true)
    {
        sleep_ms(1000);
    }
}
