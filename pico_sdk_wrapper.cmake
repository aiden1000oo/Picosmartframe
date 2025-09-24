# pico_sdk_wrapper.cmake
#
# Simple wrapper to import the Pico SDK.
# Put this file somewhere in your CMAKE_MODULE_PATH.

# If the path isn’t already set, try to infer it
if(NOT DEFINED PICO_SDK_PATH)
    if(DEFINED ENV{PICO_SDK_PATH})
        set(PICO_SDK_PATH $ENV{PICO_SDK_PATH})
    else()
        # Assume pico-sdk is checked out next to this project
        get_filename_component(_WRAPPER_DIR "${CMAKE_CURRENT_LIST_DIR}" ABSOLUTE)
        set(PICO_SDK_PATH "${_WRAPPER_DIR}/pico-sdk" CACHE PATH "Path to the Raspberry Pi Pico SDK")
    endif()
endif()

# Load the official import
include("${PICO_SDK_PATH}/external/pico_sdk_import.cmake")
