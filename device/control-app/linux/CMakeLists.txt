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

cmake_minimum_required(VERSION 3.11 FATAL_ERROR)

project(ble-provision-service VERSION 0.1.0 LANGUAGES C CXX)

# ---------------------------------------------------------------------------
#   C++
# ---------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ---------------------------------------------------------------------------
#   Options
# ---------------------------------------------------------------------------
option(SECURE_PROVISION "Enable secure provision" OFF)

# ---------------------------------------------------------------------------
#	Add dependencies
# ---------------------------------------------------------------------------

#   Ext projects path
set(EXT_PATH "${CMAKE_CURRENT_LIST_DIR}/../../ext")

#   Path to Bluez-DBus
set(BLUEZ_DBUS_PATH "${EXT_PATH}/bluez-dbus")

#   Build and install sdbus-cpp
virgil_depends(
        PACKAGE_NAME "sdbus"
        CONFIG_DIR "${EXT_PATH}/cmake"
)

#   Add BlueZ-DBus
unset(BUILD_SHARED_LIBS CACHE)
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "${VIRGIL_DEPENDS_PREFIX}/lib/cmake/sdbus-c++" "${VIRGIL_DEPENDS_PREFIX}/lib64/cmake/sdbus-c++")
add_subdirectory(${BLUEZ_DBUS_PATH} bluez-dbus)
set(BUILD_SHARED_LIBS CACHE BOOL OFF FORCE)

# ---------------------------------------------------------------------------
#	Linux BLE provisioning application
# ---------------------------------------------------------------------------
add_executable(ble-provision-service)


# ---------------------------------------------------------------------------
#	Header/Source files
# ---------------------------------------------------------------------------
target_sources(ble-provision-service
        PRIVATE
        # Headers
        ${CMAKE_CURRENT_LIST_DIR}/include/iotkit-impl/init.h
        ${CMAKE_CURRENT_LIST_DIR}/include/iotkit-impl/netif/netif-ble-linux.h
        ${CMAKE_CURRENT_LIST_DIR}/include/device-info.h
        ${CMAKE_CURRENT_LIST_DIR}/include/wifi-cred.h

        # Sources
        ${CMAKE_CURRENT_LIST_DIR}/src/main.c
        ${CMAKE_CURRENT_LIST_DIR}/src/device-info.c
        ${CMAKE_CURRENT_LIST_DIR}/src/wifi-cred.c
        ${CMAKE_CURRENT_LIST_DIR}/src/iotkit-impl/helpers.c
        ${CMAKE_CURRENT_LIST_DIR}/src/iotkit-impl/init.c
        ${CMAKE_CURRENT_LIST_DIR}/src/iotkit-impl/netif/netif-ble-linux.cpp
        )


# ---------------------------------------------------------------------------
#	Definitions
# ---------------------------------------------------------------------------
target_compile_definitions(ble-provision-service
        PRIVATE
        $<$<BOOL:${SECURE_PROVISION}>:SECURE_PROVISION=1>
        )


# ---------------------------------------------------------------------------
#   Include directories
# ---------------------------------------------------------------------------
target_include_directories(ble-provision-service
        PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/include
        )


# ---------------------------------------------------------------------------
#	Compile options
# ---------------------------------------------------------------------------
target_compile_options(ble-provision-service
        PRIVATE
        -Wno-multichar
        )


# ---------------------------------------------------------------------------
#	Link libraries
# ---------------------------------------------------------------------------
target_link_libraries(ble-provision-service
        PRIVATE

        # IoTKit
        nix-common
        vs-module-snap-thing

        # Bluez DBus
        bluez-dbus-cpp

        # Helpers
        enable_sanitizers
        #       enable_pedantic_mode
        )


# ---------------------------------------------------------------------------
#   Format code
# ---------------------------------------------------------------------------
if (COMMAND add_clangformat)
    add_clangformat(ble-provision-service)
endif ()


#------------------------------------------------------------------------------
#   Install
# ---------------------------------------------------------------------------
install(TARGETS ble-provision-service
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        )
