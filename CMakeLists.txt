cmake_minimum_required(VERSION 3.13)
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(PicoSmartFrame)
pico_sdk_init()

add_executable(pico_smart_display
    main.c
    tiny_jpeg.c
    fat32.c
)

target_link_libraries(pico_smart_display pico_stdlib tinyusb_device tinyusb_board)
pico_add_extra_outputs(pico_smart_display)
