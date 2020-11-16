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

import "../../../theme"
import "../../../components"

RowLayout {
    property bool containsMouse: btnInfo.containsMouse || btnProvision.containsMouse
    property int wSz: 100

    id: actionsBlock
    visible: false
    anchors.right: parent.right
    width: 0

    ImageButton {
        id: btnInfo
        image: "Search"
        onClicked: {
            console.log("Click: Info")
        }
    }

    ImageButton {
        id: btnProvision
        image: "dark/wifi-dimmed"
        onClicked: { startProvision(name) }
    }

    Item {
        Layout.fillWidth: true
    }

    state: "hidden"
    states: [
        State {
            name: "visible"
            PropertyChanges { target: actionsBlock; width: wSz    }
            PropertyChanges { target: actionsBlock; visible: true }
        },
        State {
            name: "hidden"
            PropertyChanges { target: actionsBlock; width: 0       }
            PropertyChanges { target: actionsBlock; visible: false }
        }]

    transitions: Transition {
        NumberAnimation { property: "width"; duration: 100 }
    }
}
