cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

pico_sdk_init()

project(PicoSmartFrame C CXX ASM)

# Collect all source files
file(GLOB_RECURSE SOURCES "src/*.c")

add_executable(pico_smart_display ${SOURCES})

target_link_libraries(pico_smart_display
    pico_stdlib
    tinyusb_device
    tinyusb_board
)

pico_add_extra_outputs(pico_smart_display)
