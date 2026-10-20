# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()

set(sdkVersion 2.3.1)
set(toolchainVersion 15_2_Rel1)
set(picotoolVersion 2.3.1)

set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)

if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================

set(PICO_BOARD pico_w CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK
include(pico_sdk_import.cmake)

project(light_led C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable
add_executable(light_led
    light_led.cpp
)

# Tell the SDK that the RGB LED is on GP6
target_compile_definitions(light_led PRIVATE
    PICO_DEFAULT_WS2812_PIN=6
)

pico_set_program_name(light_led "light_led")
pico_set_program_version(light_led "0.1")

# Enable UART output
pico_enable_stdio_uart(light_led 1)
pico_enable_stdio_usb(light_led 0)

# Add libraries
target_link_libraries(light_led
    pico_stdlib
    hardware_adc
    pico_status_led
)

# Add include files
target_include_directories(light_led PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
)

# Generate .uf2, .bin, .hex etc.
pico_add_extra_outputs(light_led)