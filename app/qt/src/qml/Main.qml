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
import "./components"
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

    SwipeView {
        readonly property int _localDevicePageIdx: 0
        readonly property int _settingsPageIdx: 1

        property int _backPageIdx: _localDevicePageIdx

        id: swipeView
        anchors.fill: parent
        currentIndex: _localDevicePageIdx

        DevicesPage {
            id: devicesPage
        }

        SettingsPage {
            id: settingsPage
        }
    }

    function showLeftMenu() {
        leftSideMenu.open()
    }

    function showLocalDevices() {
        leftSideMenu.close()
        swipeView.currentIndex = swipeView._localDevicePageIdx
    }

    function showSettings() {
        leftSideMenu.close()
        swipeView.currentIndex = swipeView._settingsPageIdx
    }

    function back() {
        swipeView.currentIndex = swipeView._backPageIdx
    }
}
