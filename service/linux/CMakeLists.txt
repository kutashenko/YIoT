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

project(ble-provision-service VERSION 0.1.0 LANGUAGES C)

#
#   Options
#
option(SECURE_PROVISION "Enable secure provision" OFF)

#
#	Add Virgil IoTKit
#

# Path to IoTKit
set (IOTKIT_PATH "${CMAKE_CURRENT_LIST_DIR}/../../ext/iotkit")

# Configure IoTKit
set (GO_DISABLE ON)
set (VIRGIL_IOT_CONFIG_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/include/config)
set (ENABLE_TESTING OFF)
set (ENABLE_HEAVY_TESTS OFF)
set (VIRGIL_IOT_PROTOCOLS ON)
set (VIRGIL_IOT_CLOUD OFF)
set (VIRGIL_IOT_PROVISION ON)
set (VIRGIL_IOT_SECBOX ON)
set (VIRGIL_IOT_DEFAULT_IMPL ON)
set (VIRGIL_IOT_UPDATE OFF)
set (VIRGIL_IOT_HIGH_LEVEL OFF)
set (VIRGIL_IOT_THREADSAFE ON)
set (VIRGIL_IOT_DEFAULT_CRYPTO_VS_SOFT_SECMODULE ON)
set (VIRGIL_IOT_DEFAULT_CLOUD_CURL_HTTP OFF)
set (VIRGIL_IOT_DEFAULT_CLOUD_MESSAGE_BIN_AWS OFF)

# Add dependencies
add_subdirectory(${IOTKIT_PATH}/sdk iotkit)
add_subdirectory(${IOTKIT_PATH}/demo/nix/common iotkit-demo-common)

#
#	Linux BLE provisioning application
#
add_executable(ble-provision-service)

#
#	Header/Source files
#
target_sources(ble-provision-service
        PRIVATE
		# Headers
		${CMAKE_CURRENT_LIST_DIR}/include/iotkit-impl/init.h
		${CMAKE_CURRENT_LIST_DIR}/include/iotkit-impl/netif/netif-ble-linux.h
		${CMAKE_CURRENT_LIST_DIR}/include/ble/ble-linux.h
		${CMAKE_CURRENT_LIST_DIR}/include/device-info.h
		${CMAKE_CURRENT_LIST_DIR}/include/wifi-cred.h
		${CMAKE_CURRENT_LIST_DIR}/src/ble/bluez-glue.h
		${CMAKE_CURRENT_LIST_DIR}/src/ble/objmanager-glue.h

        # Sources
		${CMAKE_CURRENT_LIST_DIR}/src/main.c
		${CMAKE_CURRENT_LIST_DIR}/src/device-info.c
		${CMAKE_CURRENT_LIST_DIR}/src/wifi-cred.c
		${CMAKE_CURRENT_LIST_DIR}/src/iotkit-impl/helpers.c
		${CMAKE_CURRENT_LIST_DIR}/src/iotkit-impl/init.c
		${CMAKE_CURRENT_LIST_DIR}/src/iotkit-impl/netif/netif-ble-linux.c
		${CMAKE_CURRENT_LIST_DIR}/src/ble/ble-linux.c
		${CMAKE_CURRENT_LIST_DIR}/src/ble/bluez-glue.c
		${CMAKE_CURRENT_LIST_DIR}/src/ble/objmanager-glue.c
		)

#
#	Generate D-Bus glue
#
add_custom_command(TARGET ble-provision-service
		PRE_BUILD
		COMMAND gdbus-codegen --generate-c-code  ${CMAKE_CURRENT_LIST_DIR}/src/ble/bluez-glue --interface-prefix "org.bluez." bluez.xml
		COMMAND gdbus-codegen --generate-c-code  ${CMAKE_CURRENT_LIST_DIR}/src/ble/objmanager-glue --interface-prefix "org.freedesktop." object_manager.xml
		WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/src/ble/data
		COMMENT "Generate D-Bus glue")

#
#	Definitions
#
target_compile_definitions(ble-provision-service
        PRIVATE
		$<$<BOOL:${SECURE_PROVISION}>:SECURE_PROVISION=1>
        )

#
#	PackageConfig
#
find_package(PkgConfig REQUIRED)
pkg_check_modules(GIO_2 REQUIRED gio-unix-2.0)
pkg_check_modules(DBUS_GLIB_1 REQUIRED dbus-glib-1)

#
#   Include directories
#
target_include_directories(ble-provision-service
        PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/include

		# PkgConfig
		${GIO_2_INCLUDE_DIRS}
		${DBUS_GLIB_1_INCLUDE_DIRS}
		)

#
#	Compile options
#
target_compile_options(ble-provision-service
		PRIVATE

		# PkgConfig
		${GIO_2_CFLAGS_OTHER}
		${DBUS_GLIB_1_CFLAGS_OTHER}
		)

#
#	Link libraries
#
target_link_libraries(ble-provision-service
        PRIVATE

		# IoTKit
		nix-common
		vs-module-snap-thing

		# PkgConfig
		${GIO_2_LIBRARIES}
		${DBUS_GLIB_1_LIBRARIES}

		# Helpers
		enable_sanitizers
#       enable_pedantic_mode
        )

if(COMMAND add_clangformat)
	add_clangformat(ble-provision-service)
endif()

install(TARGETS ble-provision-service
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
	)
