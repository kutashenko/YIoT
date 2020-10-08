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
//   30 July 2020
//   Lead Maintainer: Roman Kutashenko <kutashenko@gmail.com>

import QtQuick 2.5
import QtQuick.Controls 2.12
import QtQuick.Window 2.2
import QtQuick.Layouts 1.5

ApplicationWindow {

    id: applicationWindow
    visible: true
    title: qsTr("BLE Provisioner")
    background: Rectangle {
        color: "#303030"
    }

    property int dpi: Screen.pixelDensity * 25.4
    property int desktopDPI: 120
    property int dip2pixels: 160

    function dp(x) {
        if(dpi < desktopDPI) {
            return x
        } else {
            return x * (dpi / dip2pixels)
        }
    }

    property int footerHeight: dp(80)
    property int listItemHeight: dp(80)
    property int minWidthPerElement : 200
    property int elementCount : 3
    property int margin: dp(5)
    property int dataFontSize: 15

    RowLayout {
        anchors.fill: parent

        BLEManager {
            id: btScanerForm

            Layout.fillHeight: true
            Layout.fillWidth: true

            visible: true
        }

        Provision {
            id: provision
        }
    }
}
