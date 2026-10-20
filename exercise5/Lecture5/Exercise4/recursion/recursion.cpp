
#include <iostream>

#include "pico/stdlib.h"

// Prints n, n - 1, ... 1, then "Liftoff!".
// Then each call says when it ends.
void countdown(int n)
{
    if (n == 0)  // the base case: stop here
    {
        std::cout << "Liftoff!" << std::endl;
        return;
    }

    std::cout << n << std::endl;
    countdown(n - 1);  // the function calls itself
    std::cout << "back in " << n << std::endl;
}

// Adds 1 + 2 + ... + n.
int sum_to(int n)
{
    if (n == 0)
    {
        return 0;
    }

    return n + sum_to(n - 1);
}

int factorial(int n)
{
    if (n == 0)
    {
        return 1;
    }

    return n * factorial(n - 1);
}

int main()
{
    stdio_init_all();
    sleep_ms(2000);  // time to open the Serial Monitor

    countdown(5);
    std::cout << "sum_to(10) = " << sum_to(10) << std::endl;
    std::cout << "factorial(5) = " << factorial(5) << std::endl;

    while (true)
    {
        sleep_ms(1000);
    }
}
