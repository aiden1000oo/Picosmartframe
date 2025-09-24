# pico_sdk_importer.cmake
#
# A wrapper that imports the Pico SDK directory directly.
# So instead of sprinkling add_subdirectory() everywhere,
# you just include this once.

# Option 1: Use an explicit path if already set
if(NOT DEFINED PICO_SDK_PATH)
    if(DEFINED ENV{PICO_SDK_PATH})
        set(PICO_SDK_PATH $ENV{PICO_SDK_PATH})
    else()
        # Assume pico-sdk is checked out next to this project
        get_filename_component(_IMPORT_DIR "${CMAKE_CURRENT_LIST_DIR}" ABSOLUTE)
        set(PICO_SDK_PATH "${_IMPORT_DIR}/pico-sdk" CACHE PATH "Path to the Pico SDK")
    endif()
endif()

# Sanity check
if(NOT EXISTS "${PICO_SDK_PATH}/CMakeLists.txt")
    message(FATAL_ERROR "Pico SDK not found at ${PICO_SDK_PATH}")
endif()
