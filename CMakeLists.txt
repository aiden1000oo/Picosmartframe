cmake_minimum_required(VERSION 3.13)
include("${PICO_SDK_PATH}/pico_sdk_import.cmake")

project(pico_smart_display C CXX ASM)
pico_sdk_init()

add_executable(pico_smart_display
    main.c
    display_utils.c
)

target_include_directories(pico_smart_display PRIVATE main)
target_link_libraries(pico_smart_display pico_stdlib)
pico_enable_stdio_usb(pico_smart_display 1)
pico_enable_stdio_uart(pico_smart_display 0)
pico_add_extra_outputs(pico_smart_display)
