cmake_minimum_required(VERSION 3.13)

set(PICO_SDK_PATH "${CMAKE_CURRENT_LIST_DIR}/pico-sdk")
include(${PICO_SDK_PATH}/pico_sdk_init.cmake)

project(PicoSmartFrame C CXX ASM)

# Disable Bluetooth
set(PICO_BLUETOOTH 0)
set(PICO_ENABLE_BLUETOOTH 0)
set(PICO_ENABLE_BTSTACK 0)

set(PICO_ENABLE_USB 1)

pico_sdk_init()

add_executable(pico_smart_display
    fat32.c
    main.c
    tiny_jpeg.c
    display_utils.c
)

target_link_libraries(pico_smart_display
    pico_stdlib
    tinyusb_device
)

pico_add_extra_outputs(pico_smart_display)
