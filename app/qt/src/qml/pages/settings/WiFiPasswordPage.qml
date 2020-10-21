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

import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import "../../theme"
import "../../components"

Page {
    property string ssid: ""

    id: wifiSettingsPage

    background: Rectangle {
        color: "transparent"
    }

    header: Header {
        id: header
        title: qsTr("Set WiFi password ") + ssid
        backAction: function() { showWiFiSettings() }
    }

    ColumnLayout {
        width: parent.width
        anchors.topMargin: 30
        spacing: 20

        TextField {
            id: password
            placeholderText: qsTr("Password Hint")
            Layout.preferredWidth: parent.width - 20
            Layout.alignment: Qt.AlignHCenter
            color: Theme.primaryTextColor
            font.pointSize: UiHelper.fixFontSz(14)
            leftPadding: 30
            echoMode: TextField.PasswordEchoOnEdit
            background: Rectangle {
                implicitWidth: 200
                implicitHeight: 50
                radius: implicitHeight / 2
                color: "transparent"

                Rectangle {
                    width: parent.width - 10
                    height: 1
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.bottom: parent.bottom
                    color: Theme.brandColor
                }
            }
        }

        FormPrimaryButton {
            Layout.bottomMargin: 10
            text: qsTr("Apply password")
            onClicked: {
                showDevicesSetup()
            }
        }
    }

    function setTitle(aSsid) {
        ssid = aSsid;
        header.title = qsTr("WiFi password for ") + ssid
    }
}
