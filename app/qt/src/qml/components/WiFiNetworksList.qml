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
    id: list
    anchors.fill: parent

    spacing: 1
    model: wifiEnum

    delegate: Rectangle {
        id: base
        width: parent.width
        height: 45
        color: (list.currentIndex == index) ? Theme.contactsBackgroundColor : "transparent"

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
            onClicked: {
                list.currentIndex = index
                showWiFiPassword(wifiEnum.get(index))
            }
        }
    }

    Component.onCompleted: {
        wifiEnum.start()
    }
}
