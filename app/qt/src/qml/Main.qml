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
//   30 July 2020
//   Lead Maintainer: Roman Kutashenko <kutashenko@gmail.com>

import QtQuick 2.5
import QtQuick.Controls 2.12
import QtQuick.Window 2.2
import QtQuick.Layouts 1.5

import "./pages"
import "./pages/settings"
import "./components"
import "./components/Popups"
import "./theme"

ApplicationWindow {

    id: applicationWindow
    visible: true
    width: 400
    height: 600
    title: app.applicationDisplayName

    background: Rectangle {
        color: Theme.mainBackgroundColor
    }

    LeftSideMenu {
        id: leftSideMenu
    }

    Popup {
        id: inform
    }

    SwipeView {
        readonly property int devicePageIdx: 0
        readonly property int setupDevicePageIdx: 1
        readonly property int settingsPageIdx: 2

        property int backPageIdx: devicePageIdx

        id: swipeView
        anchors.fill: parent
        visible: !aboutPage.visible
        interactive: false
        currentIndex: devicePageIdx

        DevicesPage {
            id: devicesPage
        }

        DevicesSetupPage {
            id: devicesSetupPage
        }

        SharePage {
            id: sharePage
        }

        SettingsPage {
            id: settingsPage
        }
    }

    AboutPage {
        id: aboutPage
        visible: false
    }

    footer: TabBar {
        readonly property int iconSz: 50

        id: tabBar
        visible: !aboutPage.visible
        currentIndex: swipeView.currentIndex

        background: Rectangle {
            color: "transparent"
        }

        TabButton {
            icon.color: Theme.tabImages
            icon.source: "resources/icons/dark/control-devices.png"
            icon.height: tabBar.iconSz
            icon.width: tabBar.iconSz
            background: Rectangle {
                height: 2
                width: tabBar.iconSz
                anchors.horizontalCenter: parent.horizontalCenter
                color: tabBar.currentIndex == 0 ? Theme.buttonPrimaryColor : Theme.buttonInvertedColor
            }
            onClicked: swipeShow(0)
        }

        TabButton {
            icon.color: "transparent"
            icon.source: "resources/icons/dark/setup-devices.png"
            icon.height: tabBar.iconSz
            icon.width: tabBar.iconSz
            background: Rectangle {
                height: 2
                width: tabBar.iconSz
                anchors.horizontalCenter: parent.horizontalCenter
                color: tabBar.currentIndex == 1 ? Theme.buttonPrimaryColor : Theme.buttonInvertedColor
            }
            onClicked: swipeShow(1)
        }

        TabButton {
            icon.color: "transparent"
            icon.source: "resources/icons/dark/share-access.png"
            icon.height: tabBar.iconSz
            icon.width: tabBar.iconSz
            background: Rectangle {
                height: 2
                width: tabBar.iconSz
                anchors.horizontalCenter: parent.horizontalCenter
                color: tabBar.currentIndex == 2 ? Theme.buttonPrimaryColor : Theme.buttonInvertedColor
            }
            onClicked: swipeShow(2)
        }

        TabButton {
            icon.color: "transparent"
            icon.source: "resources/icons/dark/settings.png"
            icon.height: tabBar.iconSz
            icon.width: tabBar.iconSz
            background: Rectangle {
                height: 2
                width: tabBar.iconSz
                anchors.horizontalCenter: parent.horizontalCenter
                color: tabBar.currentIndex == 3 ? Theme.buttonPrimaryColor : Theme.buttonInvertedColor
            }
            onClicked: swipeShow(3)
        }
    }

    function showLeftMenu() {
        leftSideMenu.open()
    }

    function showAbout() {
        aboutPage.visible = true
    }

    function swipeShow(idx) {
        aboutPage.visible = false
        swipeView.currentIndex = idx
        for (var i = 0; i < swipeView.count; ++i) {
            var item = swipeView.itemAt(i)
            item.visible = i == swipeView.currentIndex
        }
    }

    function showDevices() {
        swipeShow(swipeView.devicePageIdx)
    }

    function showDevicesSetup() {
        swipeShow(swipeView.setupDevicePageIdx)
    }

    function showSettings() {
        swipeShow(swipeView.settingsPageIdx)
    }

    function showSettingsElement(idx) {
        swipeShow(swipeView.settingsPageIdx)
        settingsPage.swipeSettingsShow(idx)
    }

    function showSettingsForWiFi() {
        showSettingsElement(settingsPage.wifiNetworksIdx)
    }

    // Show Popup message
    function showPopup(message, color, textColor, isOnTop, isModal, action) {
        inform.popupColor = color
        inform.popupColorText = textColor
        inform.popupView.popMessage = message
        inform.popupOnTop = isOnTop
        inform.popupModal = isModal
        inform.action = action
        inform.popupView.open()
    }

    function showPopupError(message, action) {
        showPopup(message, Theme.buttonPrimaryColor, Theme.buttonPrimaryTextColor, true, true, action)
    }

    function showPopupInform(message) {
        // TODO: Add
    }
}
