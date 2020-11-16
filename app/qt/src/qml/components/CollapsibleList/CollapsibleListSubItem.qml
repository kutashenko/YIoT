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

import "../../theme"
import "../../components/CollapsibleList"
import "../../components/devices/lamp"

Column {
    property int commonWidth: 200
    property alias model : subItemRepeater.model
    width: commonWidth
    Repeater {
        id: subItemRepeater
        delegate: Rectangle {
            id: deviceItem
            color: "transparent"
            height: 40
            width: commonWidth

            Label {
                id: itemText
                z: 1
                anchors.leftMargin: 30
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                width: commonWidth - 100
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
