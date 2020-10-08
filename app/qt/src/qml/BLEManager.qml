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

            delegate: Rectangle {
                property variant selectedData: model

                id: btDelegate
                width: parent.width
                height: columnName.height

                clip: true
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

                color: ListView.view.currentIndex === index ? "white" : "steelblue"

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        mainList.currentIndex = index
                    }
                }
            }

            focus: true
        }


        RowLayout {
            Layout.alignment: Qt.AlignBottom
            Layout.preferredHeight: 50

            spacing: 20

            Button {
                id: btnSetConfig
                text: qsTr("Set parameters")
                Layout.fillWidth: true
                onClicked: setParameters()
            }

            Button {
                id: btnInitialize
                text: qsTr("Initialize")
                Layout.fillWidth: true
                onClicked: initializeDevice()
            }
        }
    }


    Component.onCompleted: {
        bleEnum.startDiscovery()
    }

    function selectedDevice() {
        return mainList.currentItem.selectedData.modelData
    }

    function setParameters() {
        var component = Qt.createComponent("InitDialog.qml")
        if (component.status === Component.Ready) {
            var dialog = component.createObject(applicationWindow)
            dialog.applied.connect(function()
            {
                try {
                    SnapCfgClient.onSetConfigData(dialog.ssid, dialog.pass, dialog.account)
                } catch (error) {
                    console.error("Cannot start initialization of device")
                }
                dialog.close()
            })
            dialog.open()
            return dialog
        }
        console.error(component.errorString())
        return null
    }

    function initializeDevice() {
        try {
            var deviceName = btScanerForm.selectedDevice();
            bleEnum.select(deviceName);
        } catch (error) {
            console.error("Cannot start initialization of device")
        }
    }

}

