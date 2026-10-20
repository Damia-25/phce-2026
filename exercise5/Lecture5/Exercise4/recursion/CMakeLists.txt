
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

# Raspberry Pi Pico W (RP2040)
set(PICO_BOARD pico_w CACHE STRING "Board type")

# Import Pico SDK
include(pico_sdk_import.cmake)

project(recursion C CXX ASM)

# Initialise Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable
add_executable(recursion
    recursion.cpp
)

# Program information
pico_set_program_name(recursion "recursion")
pico_set_program_version(recursion "0.1")

# Enable UART output for Serial Monitor
pico_enable_stdio_uart(recursion 1)
pico_enable_stdio_usb(recursion 0)

# Link required libraries
target_link_libraries(recursion
    pico_stdlib
)

# Include project directory
target_include_directories(recursion PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
)

# Generate ELF, UF2, BIN and other output files
pico_add_extra_outputs(recursion)
