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
        readonly property int aboutPageIdx: 0
        readonly property int localDevicePageIdx: 1
        readonly property int settingsPageIdx: 2
        readonly property int wifiSettingsPageIdx: 3
        readonly property int wifiPasswordPageIdx: 4
        readonly property int eventsSettingsPageIdx: 5

        property int backPageIdx: localDevicePageIdx

        id: swipeView
        anchors.fill: parent
        interactive: false
        currentIndex: localDevicePageIdx

        AboutPage {
            id: aboutPage
        }

        DevicesPage {
            id: devicesPage
        }

        SettingsPage {
            id: settingsPage
        }

        WiFiSettingsPage {
            id: wifiSettingsPage
        }

        WiFiPasswordPage {
            id: wifiPasswordPage
        }

        EventsSettingsPage {
            id: eventsSettingsPage
        }
    }

    function showLeftMenu() {
        leftSideMenu.open()
    }

    function showLocalDevices() {
        swipeView.currentIndex = swipeView.localDevicePageIdx
    }

    function showSettings() {
        swipeView.currentIndex = swipeView.settingsPageIdx
    }

    function showWiFiSettings() {
        swipeView.currentIndex = swipeView.wifiSettingsPageIdx
    }

    function showWiFiPassword(ssid) {
        wifiPasswordPage.setTitle(ssid)
        swipeView.currentIndex = swipeView.wifiPasswordPageIdx
    }

    function showEventsSettings() {
        swipeView.currentIndex = swipeView.eventsSettingsPageIdx
    }

    function showAbout() {
        swipeView.currentIndex = swipeView.aboutPageIdx
    }

    function back() {
        swipeView.currentIndex = swipeView.backPageIdx
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
        showPopup(message, Theme.buttonPrimaryColor, Theme.primaryTextColor, true, true, action)
    }

    function showPopupInform(message) {
        // TODO: Add
    }
}
