cmake_minimum_required(VERSION 3.13)

set(PICO_SDK_PATH "${CMAKE_CURRENT_LIST_DIR}/pico-sdk")

include(${PICO_SDK_PATH}/pico_sdk_init.cmake)

project(PicoSmartFrame C CXX ASM)

# Disable Bluetooth
set(PICO_BLUETOOTH 0)
set(PICO_ENABLE_BLUETOOTH 0)
set(PICO_ENABLE_BTSTACK 0)

# Enable USB if you need it
set(PICO_ENABLE_USB 1)

pico_sdk_init()

# Add your source files here (adjust paths if in "src/")
add_executable(pico_smart_display
    display_utils.c
    fat32.c 
    main.c 
    tiny_jpeg.c
)

target_link_libraries(pico_smart_display
    pico_stdlib
    # Only add tinyusb_device if you *actually* use TinyUSB features
    # tinyusb_device
)

pico_add_extra_outputs(pico_smart_display)
