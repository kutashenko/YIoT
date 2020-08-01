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
//   01 August 2020
//   Lead Maintainer: Roman Kutashenko <kutashenko@gmail.com>

#ifndef PROVISION_QT_WIFI_ENUM_H
#define PROVISION_QT_WIFI_ENUM_H

#include <QtCore>
#include <virgil/iot/qt/VSQIoTKit.h>

class KSQWiFiEnumerator : public QObject {
    Q_OBJECT
    Q_PROPERTY(QStringList wifiList MEMBER m_wifiList NOTIFY fireWiFiListUpdated)
public:
    KSQWiFiEnumerator();
    virtual ~KSQWiFiEnumerator();

public slots:
    void
    start();

    void
    stop();

signals:
    void
    fireWiFiListUpdated(QStringList list);

private slots:
    void
    onFindWiFi();

private:
    QStringList m_wifiList;
    QNetworkConfigurationManager m_ncm;
};

#endif // PROVISION_QT_WIFI_ENUM_H
