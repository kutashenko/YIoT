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
#   23 July 2020
#   Lead Maintainer: Roman Kutashenko <kutashenko@gmail.com>

cmake_minimum_required(VERSION 3.11 FATAL_ERROR)

project(ble-provision-app VERSION 0.1.0 LANGUAGES C CXX)

# ---------------------------------------------------------------------------
#   C++
# ---------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


# ---------------------------------------------------------------------------
#   Qt
# ---------------------------------------------------------------------------
find_package(Qt5 COMPONENTS Core Widgets Test Network Concurrent Qml)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)


# ---------------------------------------------------------------------------
#   IoTKit Qt Wrapper
# ---------------------------------------------------------------------------
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/cmake/iotkit-qt)

# ---------------------------------------------------------------------------
#   Application
# ---------------------------------------------------------------------------
if (APPLE)
    include(${CMAKE_CURRENT_LIST_DIR}/cmake/macdeploy.cmake)
    add_executable(ble-provision-app MACOSX_BUNDLE)
else ()
    add_executable(ble-provision-app)
endif ()


# ---------------------------------------------------------------------------
#	Header/Source files
# ---------------------------------------------------------------------------
target_sources(ble-provision-app
        PRIVATE

        # Headers
        ${CMAKE_CURRENT_LIST_DIR}/include/KSQApplication.h
        ${CMAKE_CURRENT_LIST_DIR}/include/KSQWiFiEnumerator.h
        $<$<PLATFORM_ID:Darwin>:${CMAKE_CURRENT_LIST_DIR}/include/macos/KSMacWiFi.h>
        $<$<PLATFORM_ID:Windows>:${CMAKE_CURRENT_LIST_DIR}/include/win/KSWinWiFi.h>

        # Sources
        ${CMAKE_CURRENT_LIST_DIR}/src/KSQApplication.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/KSQWiFiEnumerator.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/main.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/iotkit-hal.cpp
        $<$<PLATFORM_ID:Darwin>:${CMAKE_CURRENT_LIST_DIR}/src/macos/KSMacWiFi.mm>
        $<$<PLATFORM_ID:Windows>:${CMAKE_CURRENT_LIST_DIR}/src/win/KSWinWiFi.cpp>

        # Qt Resources
        ${CMAKE_CURRENT_LIST_DIR}/src/resources.qrc
        )


# ---------------------------------------------------------------------------
#	Definitions
# ---------------------------------------------------------------------------
target_compile_definitions(ble-provision-app
        PRIVATE
        )


# ---------------------------------------------------------------------------
#   Include directories
# ---------------------------------------------------------------------------
target_include_directories(ble-provision-app
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
        )


# ---------------------------------------------------------------------------
#	Compile options
# ---------------------------------------------------------------------------
target_compile_options(ble-provision-app
        PRIVATE
        )


# ---------------------------------------------------------------------------
#	Link libraries
# ---------------------------------------------------------------------------
target_link_libraries(ble-provision-app
        PUBLIC

        # Qt5
        Qt5::Core
        Qt5::Widgets
        Qt5::Test
        Qt5::Network
        Qt5::Concurrent
        Qt5::Qml

        #   IoTKit Qt
        iotkit-qt-lib

        #   Windows
        $<$<PLATFORM_ID:Windows>:wlanapi>

        # Compiler options
        enable_pedantic_mode
        )

if (APPLE)
    #   macOS
    target_link_libraries(ble-provision-app
            PUBLIC
            "-framework CoreWLAN"
            "-framework Foundation"
            )

endif()

#------------------------------------------------------------------------------
#   Format code
# ---------------------------------------------------------------------------
if (COMMAND add_clangformat)
    add_clangformat(ble-provision-app)
endif ()


#------------------------------------------------------------------------------
#   Install
# ---------------------------------------------------------------------------
install(TARGETS ble-provision-app
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        BUNDLE DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
        )


#------------------------------------------------------------------------------
#   Deployment
# ---------------------------------------------------------------------------
if (APPLE)
   #
   #   Configure plist file
   #
   set_target_properties(ble-provision-app PROPERTIES MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_LIST_DIR}/platform/macos/macos-info.plist)
   set (MACOSX_DEPLOYMENT_TARGET 10.14)
   set (PLIST_DST "${CMAKE_CURRENT_LIST_DIR}/platform/macos/macos-info.plist")
   set (PLIST_TMPL "${PLIST_DST}.in")
   configure_file(${PLIST_TMPL} ${PLIST_DST})

#   macdeployqt(ble-provision-app "${CMAKE_CURRENT_LIST_DIR}/src/qml")
endif ()

