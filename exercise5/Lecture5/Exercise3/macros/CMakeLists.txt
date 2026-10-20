# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location

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

project(macros C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable
add_executable(macros
    macros.cpp
)

pico_set_program_name(macros "macros")
pico_set_program_version(macros "0.1")

# Enable UART output
pico_enable_stdio_uart(macros 1)
pico_enable_stdio_usb(macros 0)

# Link required libraries
target_link_libraries(macros
    pico_stdlib
    hardware_adc
    pico_cyw43_arch_none
)

# Add standard include directories
target_include_directories(macros PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
)

# Generate UF2, BIN and other output files
pico_add_extra_outputs(macros)