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

Item {
    id: mainItem

//    property alias selectedDevice: mainList.currentItem.selectedData.modelData

    ColumnLayout {
        anchors.fill: parent
        anchors.leftMargin: 5
        anchors.rightMargin: 5

        spacing: 2

        ListView {
            id: mainList

            Layout.alignment: Qt.AlignTop
            Layout.fillHeight: true
            Layout.fillWidth: true

            model: bleEnum

            spacing: 2
            focus: true

            delegate: Rectangle {
                property variant selectedData: model

                id: btDelegate
                width: parent.width
                height: columnName.height
                clip: true
                color: ListView.view.currentIndex === index ? "white" : "steelblue"

                Image {
                    id: bticon
                    source: "qrc:/qml/default.png";
                    width: bttext.height * 2 / 3
                    height: bttext.height * 2 / 3
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                    anchors.left: parent.left
                    anchors.margins: 7
                }

                Column {
                    id: columnName
                    anchors.left: bticon.right
                    anchors.leftMargin: 5
                    Text {
                        id: bttext
                        text: name
                        height: 40
                        verticalAlignment: Text.AlignVCenter
                        font.pixelSize: Qt.application.font.pixelSize
                    }
                }

                Column {
                    id: columnRSSI
                    anchors.right : parent.right
                    anchors.rightMargin: 5
                    Text {
                        id: btRSSI
                        text: rssi
                        height: 40
                        verticalAlignment: Text.AlignVCenter
                        font.pixelSize: Qt.application.font.pixelSize
                    }
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        mainList.currentIndex = index
                    }
                }
            }
        }
    }

    Component.onCompleted: {
        bleEnum.startDiscovery()
    }
}

