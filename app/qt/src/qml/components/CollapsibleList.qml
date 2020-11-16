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
import "../components/devices/lamp"

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
                    height: 40
                    width: w

                    Label {
                        id: itemText
                        z: 1
                        anchors.leftMargin: 30
                        anchors.left: parent.left
                        anchors.top: parent.top
                        anchors.bottom: parent.bottom
                        width: w - 100
                        verticalAlignment: Qt.AlignVCenter
                        font.pointSize: UiHelper.fixFontSz(14)
                        text: name
                        color: Theme.primaryTextColor
                    }

                    Loader {
                        id: loader
                        source: "qrc:/qml/components/devices/lamp/LampControls.qml"
                        onLoaded: {
                            z = 1
                            anchors.left = itemText.right
                            anchors.right = parent.right
                            item.state = "hidden"
                            item.width = 0
                            item.onContainsMouseChanged.connect(function() {
                                checkActivity()
                            })
                        }
                    }

                    MouseArea {
                        id: mainMouseArea
                        z: 0
                        enabled: true
                        anchors.fill: parent
                        hoverEnabled: true
                        onClicked: {
                            activateDeviceView(deviceType, name, deviceController)
                        }

                        onEntered: {
                            list.currentIndex = index
                            checkActivity()
                        }

                        onExited: {
                            checkActivity()
                        }
                    }

                    function timerObj() {
                        return Qt.createQmlObject("import QtQuick 2.0; Timer {}", list);
                    }

                    function delay(delayTime, cb) {
                        var timer = new timerObj()
                        timer.interval = delayTime
                        timer.repeat = false
                        timer.triggered.connect(cb)
                        timer.start()
                    }

                    function checkActivity() {
                        delay(5, function() {
                            var v = loader.item.containsMouse || mainMouseArea.containsMouse
                            loader.item.state = v ? "visible" : "hidden"
                            deviceItem.color = v ? Theme.contrastBackgroundColor : "transparent"
                        })
                    }

                }
            }
        }
    }
}
