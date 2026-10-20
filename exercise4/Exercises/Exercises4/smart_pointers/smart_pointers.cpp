
#include <iostream>
#include <memory>
#include <utility>

#include "pico/stdlib.h"

int main()
{
    stdio_init_all();

    // Give the Serial Monitor time to connect
    sleep_ms(3000);

    std::cout << "Program started!" << std::endl;

    // Part 1: Raw pointer
    int* raw {new int {42}};
    std::cout << "*raw = " << *raw << std::endl;

    // TODO 1
    delete raw;
    raw = nullptr;

    std::cout << "raw is "
              << (raw ? "still set" : "nullptr")
              << std::endl;

    // Part 2: Smart pointer
    std::unique_ptr<int> first {std::make_unique<int>(42)};
    std::unique_ptr<int> second {nullptr};

    // TODO 2
    second = std::move(first);

    std::cout << "first is "
              << (first ? "full" : "empty")
              << ", second is "
              << (second ? "full" : "empty")
              << std::endl;

    // Step 4: Memory leak experiment
    std::cout << "Starting memory leak test..." << std::endl;

    sleep_ms(1000);

    int leaked_kb {0};

    while (true)
    {
        int* leak {new int[256]};

        ++leaked_kb;

        std::cout << "leaked " << leaked_kb
                  << " KB, last one at "
                  << leak << std::endl;

        sleep_ms(20);
    }
}
