#
#                                  _____   _______
#                                 |_   _| |__   __|
#                                   | |  ___ | |
#                                   | | / _ \| |
#                                  _| || (_) | |
#                                 |_____\___/|_|
#
#    _  ________ ______ _____    _____ _______    _____ _____ __  __ _____  _      ______
#   | |/ /  ____|  ____|  __ \  |_   _|__   __|  / ____|_   _|  \/  |  __ \| |    |  ____|
#   | ' /| |__  | |__  | |__) |   | |    | |    | (___   | | | \  / | |__) | |    | |__
#   |  < |  __| |  __| |  ___/    | |    | |     \___ \  | | | |\/| |  ___/| |    |  __|
#   | . \| |____| |____| |       _| |_   | |     ____) |_| |_| |  | | |    | |____| |____
#   |_|\_\______|______|_|      |_____|  |_|    |_____/|_____|_|  |_|_|    |______|______|
#
#
#
#   21 July 2020
#   Lead Maintainer: Roman Kutashenko <kutashenko@gmail.com>

cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

# ---------------------------------------------------------------------------
# Include Cmake helpers
# ---------------------------------------------------------------------------
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

include(vsplatforms)
include(varpadding)

# ---------------------------------------------------------------------------
# Project version
# ---------------------------------------------------------------------------
set(KS_TARGET_VERSION "0.1.0")

# ---------------------------------------------------------------------------
# Define project
# ---------------------------------------------------------------------------
project(ble-provision VERSION ${KS_TARGET_VERSION} LANGUAGES C CXX)

# ---------------------------------------------------------------------------
#	CMake Helpers
# ---------------------------------------------------------------------------
set (IOTKIT_PATH "${CMAKE_CURRENT_LIST_DIR}/ext/iotkit")
set (CMAKE_MODULE_PATH "${IOTKIT_PATH}/sdk/cmake" ${CMAKE_MODULE_PATH})
include(helpers)

# ---------------------------------------------------------------------------
#   Detecting platform if KS_PLATFORM not specified
# ---------------------------------------------------------------------------
if(NOT KS_PLATFORM)
    if(ANDROID)
        message(STATUS "Detected target platform: [Android]")
        set(KS_PLATFORM "android")
    elseif(UNIX)
        message(STATUS "Detected target platform: [Unix]")
        set(KS_PLATFORM "linux")
    elseif(MACOS)
        message(STATUS "Detected target platform: [MacOS]")
        set(KS_PLATFORM "macos")
    elseif(IOS)
        message(STATUS "Detected target platform: [IOS]")
        set(KS_PLATFORM "ios")
    elseif(MINGW32)
        message(STATUS "Detected target platform: [Windows]")
        set(KS_PLATFORM "windows")
    endif()
endif()


if ((KS_PLATFORM STREQUAL "linux") OR (KS_PLATFORM STREQUAL "macos") OR (KS_PLATFORM STREQUAL "windows"))
    set (KS_PLATFORM_DESKTOP ON)
else()
    set (KS_PLATFORM_DESKTOP OFF)
endif()

message(STATUS "KS_PLATFORM: ${KS_PLATFORM}")
message(STATUS "KS_PLATFORM_DESKTOP: ${KS_PLATFORM_DESKTOP}")

# ---------------------------------------------------------------------------
#   Options
# ---------------------------------------------------------------------------
option(BUILD_DEVICE_ENABLE "Enable building of Device app" ON)
option(BUILD_APP_ENABLE "Enable building of Application" ON)
option(BUILD_ISO_PACKER_ENABLE "Enable building of ISO Packer" ON)


# ---------------------------------------------------------------------------
#   Platform limitations
# ---------------------------------------------------------------------------
if (NOT KS_PLATFORM STREQUAL "linux")
    set (BUILD_DEVICE_ENABLE OFF)
endif()

# set (BUILD_ISO_PACKER_ENABLE FORCE)


# ---------------------------------------------------------------------------
#	IoTKit
# ---------------------------------------------------------------------------
#   Configure

set(IOTKIT_PATH "${CMAKE_CURRENT_LIST_DIR}/ext/iotkit")
#TODO: Fix it !
set(VIRGIL_IOT_CONFIG_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/device/control-app/linux/include/config)
#set(GO_DISABLE CACHE BOOL ON FORCE)
option(ENABLE_TESTING OFF)
option(ENABLE_HEAVY_TESTS OFF)
option(VIRGIL_IOT_CLOUD OFF)
option(VIRGIL_IOT_HIGH_LEVEL OFF)
option(VIRGIL_IOT_THREADSAFE ON)
option(VIRGIL_IOT_DEFAULT_CLOUD_CURL_HTTP OFF)
option(VIRGIL_IOT_DEFAULT_CLOUD_MESSAGE_BIN_AWS OFF)

#   Add
add_subdirectory(${IOTKIT_PATH}/sdk)
add_subdirectory(${IOTKIT_PATH}/demo/nix/common)

# ---------------------------------------------------------------------------
#	Device provisioning service
# ---------------------------------------------------------------------------
if (BUILD_DEVICE_ENABLE)
    add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/device)
endif()

# ---------------------------------------------------------------------------
#	ISO packer for BLE provisioning Service
# ---------------------------------------------------------------------------
if (BUILD_ISO_PACKER_ENABLE)
    add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/iso-packer)
endif()

# ---------------------------------------------------------------------------
#	Linux BLE provisioning Application (Desktop and mobile)
# ---------------------------------------------------------------------------
if (BUILD_APP_ENABLE)
    add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/app)
endif()
