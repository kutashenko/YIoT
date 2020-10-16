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

    delegate: Rectangle {
        width: parent.width
        height: 45
        color: "transparent"

        RowLayout {
            id: listDelegate
            anchors.fill: parent
            clip: true

            Image {
                id: icon
                source: Theme.btImg
                Layout.maximumHeight: listDelegate.height * 0.7
                Layout.maximumWidth: Layout.maximumHeight
                fillMode: Image.PreserveAspectFit
                Layout.alignment: Qt.AlignLeft
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
                Layout.rightMargin: 5
            }

            RowLayout {
                id: actionsBlock
                Layout.rightMargin: 10

                ImageButton {
                    id: btnInfo
                    image: "Search"

                    onClicked: {
                        console.log("Click: Info")
                    }
                }

                ImageButton {
                    id: btnProvision
                    image: "Plus"

                    onClicked: {
                        console.log("Click: Provision")
                    }
                }

                states: [
                        State { when: list.currentIndex == index;
                            PropertyChanges {   target: actionsBlock; Layout.maximumWidth: 80    }
                        },
                        State { when: list.currentIndex != index;
                            PropertyChanges {   target: actionsBlock; Layout.maximumWidth: 0    }
                        }]

                transitions: Transition {
                    NumberAnimation { property: "Layout.maximumWidth"; duration: 100}
                }
            }
        }

        MouseArea {
            enabled: list.currentIndex != index
            anchors.fill: parent
            onClicked: {
                list.currentIndex = index
                console.log(">>> click ", index)
            }
        }
    }
}
