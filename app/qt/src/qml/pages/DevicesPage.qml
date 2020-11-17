//
//                                  _____   _______
//                                 |_   _| |__   __|
//                                   | |  ___ | |
//                                   | | / _ \| |
//                                  _| || (_) | |
//                                 |_____\___/|_|
//
//    _  ________ ______ _____    _____ _______    _____ _____ __  __ _____  _      ______
//   | |/ /  ____|  ____|  __ \  |_   _|__   __|  / ____|_   _|  \/  |  __ \| |    |  ____|
//   | ' /| |__  | |__  | |__) |   | |    | |    | (___   | | | \  / | |__) | |    | |__
//   |  < |  __| |  __| |  ___/    | |    | |     \___ \  | | | |\/| |  ___/| |    |  __|
//   | . \| |____| |____| |       _| |_   | |     ____) |_| |_| |  | | |    | |____| |____
//   |_|\_\______|______|_|      |_____|  |_|    |_____/|_____|_|  |_|_|    |______|______|
//
//
//
//   09 October 2020
//   Lead Maintainer: Roman Kutashenko <kutashenko@gmail.com>

import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import "../theme"
import "../components"
import "../components/devices"

Page {

    background: Rectangle {
        color: "transparent"
    }

    header: Header {
        title: qsTr("Controlled devices")
        showBackButton: false
        showMenuButton: true
        showSettingsButton: true
    }

    AllDevicesList {
        id: list
        model: deviceControllers
    }

    function deviceCategoryActions(deviceType) {
        if (deviceType === "lamps") {
            return "qrc:/qml/components/devices/lamp/LampCategoryControls.qml"
        }

        console.error("Unknown Device Type")
        return ""
    }

    function deviceActions(deviceType) {
        if (deviceType === "lampMono") {
            return "qrc:/qml/components/devices/lamp/LampControls.qml"
        }

        console.error("Unknown Device Type")
        return ""
    }

    function activateDeviceView(deviceType, deviceName, deviceController) {
        if (deviceType === "lampMono") {
            lampMonoPage.deviceName = deviceName
            lampMonoPage.controller = deviceController
            showLampMono()
        } else {
            console.error("Unknown Device Type")
        }
    }

    function deviceStateImage(model) {
        if (model.deviceType === "lampMono") {
            return "devices/lamp/mono/%1".arg(model.state)
        }

        console.error("Unknown Device Type")
        return ""
    }
}
