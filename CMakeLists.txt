cmake_minimum_required(VERSION 3.13)

# Set the path to the pico-sdk submodule (edit if needed)
set(PICO_SDK_PATH "${CMAKE_CURRENT_LIST_DIR}/pico-sdk")

# Pull in the SDK (must be before project())
include(${PICO_SDK_PATH}/pico_sdk_init.cmake)

project(PicoSmartFrame C CXX ASM)

set(PICO_BLUETOOTH 0)
set(PICO_ENABLE_BLUETOOTH 0)
set(PICO_ENABLE_BTSTACK 0)

pico_sdk_init()

# Collect all source files
file(GLOB_RECURSE SOURCES "display_utils.c" "fat32.c" "main.c" "tiny_jpeg.c")

add_executable(pico_smart_display ${SOURCES})


target_include_directories(pico_smart_display PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/src
)

target_link_libraries(pico_smart_display
    pico_stdlib
    tinyusb_board
    tinyusb_device
)

pico_add_extra_outputs(pico_smart_display)


