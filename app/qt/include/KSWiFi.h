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

#ifndef PROVISION_QT_WIFI_MACOS_H
#define PROVISION_QT_WIFI_MACOS_H

#include <QtCore>

struct KSWiFiInfo {
    int rssi;
    QDateTime lastUpdate;

    KSWiFiInfo(int _rssi) {
        rssi = _rssi;
        lastUpdate = QDateTime::currentDateTime();
    }

    KSWiFiInfo() {
        rssi = -100;
        lastUpdate = QDateTime::currentDateTime().addYears(-1);
    }
};

typedef QMap<QString, KSWiFiInfo> KSQWiFiNetworks;

#if defined(Q_OS_MACOS) || defined(Q_OS_WIN32)
KSQWiFiNetworks
wifi_enum();
#endif

#endif // PROVISION_QT_WIFI_MACOS_H
