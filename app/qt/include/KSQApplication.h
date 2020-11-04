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

#ifndef PROVISION_QT_APP_H
#define PROVISION_QT_APP_H

#include <QtCore>
#include <QGuiApplication>

#include <KSQActiveDevicesEnumerator.h>
#include <KSQWiFiEnumerator.h>

#include <virgil/iot/qt/netif/VSQNetifBLEEnumerator.h>
#include <virgil/iot/qt/VSQIoTKit.h>
#include <virgil/iot/qt/netif/VSQUdpBroadcast.h>
#include <virgil/iot/qt/netif/VSQNetifBLE.h>

class KSQApplication : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString organizationDisplayName READ organizationDisplayName CONSTANT)
    Q_PROPERTY(QString applicationDisplayName READ applicationDisplayName CONSTANT)
public:
    KSQApplication() = default;
    virtual ~KSQApplication() = default;

    int
    run();

    QString
    organizationDisplayName() const;

    QString
    applicationDisplayName() const;

    Q_INVOKABLE bool
    deviceConfigureWiFi(QString deviceName);

private:
    KSQActiveDevicesEnumerator m_activeDevicesEnumerator;
    VSQNetifBLEEnumerator m_bleEnumerator;
    KSQWiFiEnumerator m_wifiEnumerator;
    QSharedPointer<VSQNetifBLE> m_netifBLE;
};

#endif // PROVISION_QT_APP_H
