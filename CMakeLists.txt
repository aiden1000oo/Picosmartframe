cmake_minimum_required(VERSION 3.13)

# Allow overriding Pico SDK path
if(NOT DEFINED PICO_SDK_PATH)
    set(PICO_SDK_PATH "${CMAKE_CURRENT_LIST_DIR}/pico-sdk")
endif()

# Validate Pico SDK exists
if(NOT EXISTS "${PICO_SDK_PATH}/pico_sdk_import.cmake")
    message(FATAL_ERROR "Pico SDK not found at ${PICO_SDK_PATH}. Clone it with submodules or set PICO_SDK_PATH.")
endif()

include(${PICO_SDK_PATH}/pico_sdk_import.cmake)

project(PicoSmartFrame C CXX ASM)

pico_sdk_init()

# Collect all source files
file(GLOB_RECURSE SOURCES "src/*.c")

add_executable(pico_smart_display ${SOURCES})

target_link_libraries(pico_smart_display
    pico_stdlib
    tinyusb_device
    tinyusb_board
)

pico_add_extra_outputs(pico_smart_display)
