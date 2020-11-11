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
//   05 August 2020
//   Lead Maintainer: Roman Kutashenko <kutashenko@gmail.com>

import QtQuick 2.5
import QtQuick.Layouts 1.5
import QtQuick.Controls 2.12

import "../theme"

ListView {
    id: wifiList
    Layout.fillHeight: true
    Layout.fillWidth: true

    spacing: 1
    model: wifiEnum

    delegate: Rectangle {
        id: base
        width: wifiList.width
        height: 45
        color: colorIfActive(name)

        RowLayout {
            id: listDelegate
            anchors.fill: parent
            clip: true

            Image {
                id: icon
                source: Theme.wifiImg
                Layout.maximumHeight: listDelegate.height * 0.6
                Layout.maximumWidth: Layout.maximumHeight
                fillMode: Image.PreserveAspectFit
                Layout.alignment: Qt.AlignLeft
                Layout.leftMargin: 5
            }

            Text {
                id: nameText
                text: name
                color: Theme.primaryTextColor
                verticalAlignment: Text.AlignVCenter
                font.pointSize: UiHelper.fixFontSz(14)

                Layout.alignment: Qt.AlignLeft
                Layout.fillHeight: true
                Layout.fillWidth: true
            }

            Text {
                id: rssiText
                text: rssi
                color: Theme.primaryTextColor
                verticalAlignment: Text.AlignVCenter
                font.pointSize: UiHelper.fixFontSz(14)

                Layout.alignment: Qt.AlignLeft
                Layout.fillHeight: true
                Layout.rightMargin: 15
            }
        }

        MouseArea {
            enabled: true
            anchors.fill: parent
            hoverEnabled: true
            onClicked: {
                wifiList.currentIndex = index
                showWiFiPassword(name)
            }

            onEntered: {
                wifiList.currentIndex = index
                base.color = Theme.contrastBackgroundColor
            }

            onExited: {
                base.color = colorIfActive(name)
            }
        }
    }

    Component.onCompleted: {
    }

    function colorIfActive(name) {
        var isActive = settings.defaultWiFi === name
        return isActive ? Theme.contrastBackgroundColor : "transparent"
    }
}
