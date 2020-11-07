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
//   09 October 2020
//   Lead Maintainer: Roman Kutashenko <kutashenko@gmail.com>

import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import "../theme"
import "../components"

Page {

    background: Rectangle {
        color: "transparent"
    }

    header: Header {
        title: qsTr("Controlled devices")
        showBackButton: false
        showMenuButton: true
        showSettingsButton: true
    }

    ListView {
        id: list
        anchors.fill: parent
        anchors.topMargin: 1

        spacing: 1
        model: activeDevEnum

        delegate: Rectangle {
            id: base
            width: parent.width
            height: 45
            color: "transparent"

            RowLayout {
                id: listDelegate
                anchors.fill: parent
                clip: true

                Image {
                    id: icon
                    source: "qrc:/qml/resources/icons/dark/%1.png".arg(image)
                    Layout.maximumHeight: listDelegate.height * 0.7
                    Layout.maximumWidth: Layout.maximumHeight
                    Layout.leftMargin: 5
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
                    Layout.rightMargin: 5
                }

//                RowLayout {
//                    id: actionsBlock
//                    Layout.rightMargin: 10
//
//                    ImageButton {
//                        id: btnInfo
//                        image: "Search"
//                        z: 100
//
//                        onClicked: {
//                            console.log("Click: Info")
//                        }
//                    }
//
//                    ImageButton {
//                        id: btnProvision
//                        image: "Plus"
//
//                        onClicked: {
//                            showPopupError(qsTr("Need to set WiFi credentials"), showWiFiSettings)
//                        }
//                    }
//
//                    states: [
//                            State { when: list.currentIndex == index;
//                                PropertyChanges {   target: actionsBlock; Layout.maximumWidth: 80    }
//                            },
//                            State { when: list.currentIndex != index;
//                                PropertyChanges {   target: actionsBlock; Layout.maximumWidth: 0    }
//                            }]
//
//                    transitions: Transition {
//                        NumberAnimation { property: "Layout.maximumWidth"; duration: 100}
//                    }
//                }
            }

            MouseArea {
                enabled: true
                anchors.fill: parent
                hoverEnabled: true
                anchors.rightMargin: 0
                onClicked: {
                    showLampMono()
                }

                onEntered: {
                    list.currentIndex = index
                    base.color = Theme.contrastBackgroundColor
                }

                onExited: {
                    base.color = "transparent"
                }
            }
        }

        Component.onCompleted: {

        }
    }
}
