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

# ---------------------------------------------------------------------------
#   Application
# ---------------------------------------------------------------------------
if (KS_PLATFORM STREQUAL "macos")
    include(${CMAKE_CURRENT_LIST_DIR}/cmake/macdeploy.cmake)
    add_executable(ble-provision-app MACOSX_BUNDLE)
else ()
    add_executable(ble-provision-app)
endif ()

# ---------------------------------------------------------------------------
#   Detecting build type
# ---------------------------------------------------------------------------
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()
string( TOLOWER "${CMAKE_BUILD_TYPE}" CMAKE_BUILD_TYPE_LOWER )
message("-- Build type: [${CMAKE_BUILD_TYPE}]")

# ---------------------------------------------------------------------------
# Prepare platform depends
# ---------------------------------------------------------------------------
set(KS_QT_EXTRA "")

# IOS, IOS_SIM
if(KS_PLATFORM STREQUAL "ios")
    # Android
elseif(KS_PLATFORM STREQUAL "android")
    # Get firebase
    get_firebase()

    # Set Android version name
    set(ANDROID_VERSION_NAME "${KS_TARGET_VERSION}")
    # Fill Android version code
    string(REPLACE "." ";" KS_VERSION_LIST ${KS_TARGET_VERSION})

    list(GET KS_VERSION_LIST 0 TMP_VERS)
    PAD_STRING(ANDROID_VERSION_CODE 3 "0" "1${TMP_VERS}")

    list(GET KS_VERSION_LIST 1 TMP_VERS)
    PAD_STRING(TMP_VERS 2 "0" "${TMP_VERS}")
    string(APPEND ANDROID_VERSION_CODE "${TMP_VERS}")

    list(GET KS_VERSION_LIST 2 TMP_VERS)
    PAD_STRING(TMP_VERS 2 "0" "${TMP_VERS}")
    string(APPEND ANDROID_VERSION_CODE "${TMP_VERS}")

    # Get build number ( or zero)
    if (DEFINED ENV{BUILD_NUMBER})
        set(KS_BUILD_NUMBER "$ENV{BUILD_NUMBER}")
    else()
        set(KS_BUILD_NUMBER "0")
    endif()
    PAD_STRING(TMP_VERS 3 "0" "${KS_BUILD_NUMBER}")
    string(APPEND ANDROID_VERSION_CODE "${TMP_VERS}")
    message(STATUS "Android version name: [${ANDROID_VERSION_NAME}]")
    message(STATUS "Android version code: [${ANDROID_VERSION_CODE}]")

    # Android QT Extra
    string(APPEND KS_QT_EXTRA "AndroidExtras")
    # Android gradle path
    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/platforms/android")
endif()

# ---------------------------------------------------------------------------
#   Prepare for build target
# ---------------------------------------------------------------------------
# Android
if(KS_PLATFORM STREQUAL "android")
    message("-- Prepare sources for Android ...")
    add_library(${KS_TARGET_NAME} SHARED)
    include(${ANDROID_SDK}/android_openssl/CMakeLists.txt)

    if (ANDROID_ABI STREQUAL "armeabi-v7a")
        set(KS_ANDROID_SSL_DIR "${SSL_ROOT_PATH}/latest/arm/")
    elseif (ANDROID_ABI STREQUAL "arm64-v8a")
        set(KS_ANDROID_SSL_DIR "${SSL_ROOT_PATH}/latest/arm64/")
    elseif (ANDROID_ABI STREQUAL "x86")
        set(KS_ANDROID_SSL_DIR "${SSL_ROOT_PATH}/latest/x86/")
    elseif (ANDROID_ABI STREQUAL "x86_64")
        set(KS_ANDROID_SSL_DIR "${SSL_ROOT_PATH}/latest/x86_64/")
    endif()

    message(STATUS "Android OpenSSL root path:    [${SSL_ROOT_PATH}]")
    message(STATUS "Android OpenSSL library path: [${KS_ANDROID_SSL_DIR}]")

    # MacOS
elseif(KS_PLATFORM STREQUAL "macos")

    set(App_ICON "${KS_CUSTOMER_DIR}/platforms/macos/pkg_resources/${MACOSX_BUNDLE_ICON_FILE}.icns")
    set_source_files_properties(${App_ICON}
            PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")

    # Sparkle
    message(STATUS "Copy Sparkle framework")
    execute_process(
            COMMAND mkdir -p ${CMAKE_BINARY_DIR}/${KS_TARGET_NAME}.app/Contents/Frameworks
            COMMAND cp -Rf ${PREBUILT_DIR}/${KS_PLATFORM}/sparkle/Sparkle.framework ${CMAKE_BINARY_DIR}/${KS_TARGET_NAME}.app/Contents/Frameworks
    )

    add_executable(${KS_TARGET_NAME} MACOSX_BUNDLE ${App_ICON} )

    set_target_properties(${KS_TARGET_NAME}
            PROPERTIES MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_LIST_DIR}/platforms/macos/Info.plist.in"
            )
    set_target_properties(${KS_TARGET_NAME}
            PROPERTIES LINK_FLAGS "-F${PREBUILT_DIR}/${KS_PLATFORM}/sparkle -framework Sparkle -framework CoreFoundation -framework Foundation"
            )


    #    macdeployqt(${KS_TARGET_NAME} "${CMAKE_CURRENT_LIST_DIR}/src/qml")
    # Other
else()
    add_executable(${KS_TARGET_NAME})
endif()

# ---------------------------------------------------------------------------
#	Header/Source files
# ---------------------------------------------------------------------------
target_sources(ble-provision-app
        PRIVATE

        # Headers
        ${CMAKE_CURRENT_LIST_DIR}/include/KSQApplication.h
        ${CMAKE_CURRENT_LIST_DIR}/include/ui/VSQUiHelper.h
        ${CMAKE_CURRENT_LIST_DIR}/include/KSQActiveDevicesEnumerator.h
        ${CMAKE_CURRENT_LIST_DIR}/include/KSQWiFiEnumerator.h
        ${CMAKE_CURRENT_LIST_DIR}/include/KSActiveDevice.h
        $<$<PLATFORM_ID:Darwin>:${CMAKE_CURRENT_LIST_DIR}/include/KSWiFi.h>
        $<$<PLATFORM_ID:Windows>:${CMAKE_CURRENT_LIST_DIR}/include/KSWiFi.h>

        # Sources
        ${CMAKE_CURRENT_LIST_DIR}/src/KSQApplication.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/ui/VSQUiHelper.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/KSQActiveDevicesEnumerator.cpp
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

