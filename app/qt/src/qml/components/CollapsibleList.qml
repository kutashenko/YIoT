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
//   04 August 2020
//   Lead Maintainer: Roman Kutashenko <kutashenko@gmail.com>

import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import "../theme"

Item {
    property alias model: list.model
    property int w: parent.width

    anchors.fill: parent
    anchors.topMargin: 1

    ListView {
        id: list
        anchors.fill: parent
        delegate: categoryDelegate
    }

    Component {
        id: categoryDelegate

        Column {
            width: w

            Rectangle {
                id: categoryItem
                color: "transparent"
                height: 50
                width: w

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
                        id: categoryText
                        text: name
                        color: Theme.primaryTextColor
                        verticalAlignment: Text.AlignVCenter
                        font.pointSize: UiHelper.fixFontSz(14)

                        Layout.alignment: Qt.AlignLeft
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        Layout.rightMargin: 5
                    }
                }

                MouseArea {
                    enabled: true
                    anchors.fill: parent
                    hoverEnabled: true
                    anchors.rightMargin: 0
                    onClicked: {
                        subModel.collapsed = !subModel.collapsed
                    }

                    onEntered: {
                        list.currentIndex = index
                        categoryItem.color = Theme.contrastBackgroundColor
                    }

                    onExited: {
                        categoryItem.color = "transparent"
                    }
                }
            }

            Loader {
                id: subItemLoader

                // This is a workaround for a bug/feature in the Loader element. If sourceComponent is set to null
                // the Loader element retains the same height it had when sourceComponent was set. Setting visible
                // to false makes the parent Column treat it as if it's height was 0.
                visible: !subModel.collapsed
                property variant subItemModel : subModel
                sourceComponent: subModel.collapsed ? null : subItemColumnDelegate
                onStatusChanged: if (status == Loader.Ready) item.model = subItemModel
            }
        }

    }

    Component {
        id: subItemColumnDelegate
        Column {
            property alias model : subItemRepeater.model
            width: w
            Repeater {
                id: subItemRepeater
                delegate: Rectangle {
                    id: deviceItem
                    color: "transparent"
                    height: itemText.height + 10
                    width: w

                    Text {
                        id: itemText
                        anchors.verticalCenter: parent.verticalCenter
                        x: 30
                        font.pointSize: UiHelper.fixFontSz(14)
                        text: name
                        color: Theme.primaryTextColor
                    }

                    MouseArea {
                        enabled: true
                        anchors.fill: parent
                        hoverEnabled: true
                        anchors.rightMargin: 0
                        onClicked: {
                            activateDeviceView(deviceType, name, deviceController)
                        }

                        onEntered: {
                            list.currentIndex = index
                            deviceItem.color = Theme.contrastBackgroundColor
                        }

                        onExited: {
                            deviceItem.color = "transparent"
                        }
                    }
                }
            }
        }
    }
}