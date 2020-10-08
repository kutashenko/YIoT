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
//   07 October 2020
//   Lead Maintainer: Roman Kutashenko <kutashenko@gmail.com>

import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Dialog {

//    property string ssid: editSSID.text
//    property string pass: editPass.text

    x: (parent.width - width) / 2
    y: (parent.height - height) / 2
    visible: true
    title: qsTr("Initialization parameters")
    standardButtons: Dialog.Apply | Dialog.Cancel

    contentItem: Rectangle {
        color: "darkgrey"
        implicitWidth: 400
        implicitHeight: 120

        Label {
            id: labelWiFi
            text: "WiFi SSID"
            color: "black"
        }

        ComboBox {
            id: editSSID
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: labelWiFi.bottom
            anchors.topMargin: 5

            model: wifiEnum

            delegate: Rectangle {
                id: wifiDelegate
                width: parent.width
                height: columnName.height

//                clip: true
                Image {
                    id: bticon
                    source: "qrc:/qml/default.png";
                    width: bttext.height - anchors.margins
                    height: bttext.height - anchors.margins
                    anchors.top: parent.top
                    anchors.left: parent.left
                    anchors.leftMargin: 5
                    anchors.rightMargin: 5
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

                color: editSSID.currentIndex === index ? "white" : "steelblue"

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        editSSID.currentIndex = index
                    }
                }
            }
        }

        Label {
            id: labelPass
            text: "WiFi Password"
            anchors.top: editSSID.bottom
            color: "black"
        }

        TextField {
            id: editPass
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: labelPass.bottom
            anchors.topMargin: 3

            color: "black"
            placeholderText: qsTr("WiFi Password")
        }
    }
}
