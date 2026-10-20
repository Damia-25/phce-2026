
#include <iostream>

#include "pico/stdlib.h"

// Swap by value: gets copies of the variables.
void swap_by_value(int a, int b)
{
    const int temp {a};
    a = b;
    b = temp;
}

// TODO 1: Swap by pointer.
void swap_by_pointer(int* a, int* b)
{
    const int temp {*a};
    *a = *b;
    *b = temp;
}

// TODO 2: Swap by reference.
void swap_by_reference(int& a, int& b)
{
    const int temp {a};
    a = b;
    b = temp;
}

int main()
{
    stdio_init_all();
    sleep_ms(2000);  // Time to open the Serial Monitor

    int x {1};
    int y {2};

    std::cout << "start:        x = " << x << ", y = " << y << std::endl;

    swap_by_value(x, y);
    std::cout << "by value:     x = " << x << ", y = " << y << std::endl;

    swap_by_pointer(&x, &y);
    std::cout << "by pointer:   x = " << x << ", y = " << y << std::endl;

    swap_by_reference(x, y);
    std::cout << "by reference: x = " << x << ", y = " << y << std::endl;

    while (true)
    {
        sleep_ms(1000);
    }
}
