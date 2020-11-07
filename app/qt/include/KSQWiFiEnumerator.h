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
#include <QAbstractTableModel>

#include <virgil/iot/qt/VSQIoTKit.h>

#include <KSWiFi.h>

class KSQWiFiEnumerator : public QAbstractTableModel {
    Q_OBJECT
public:
    enum Element { Name = Qt::UserRole, RSSI, ElementMax };

    KSQWiFiEnumerator();
    virtual ~KSQWiFiEnumerator();

    /**
     * QAbstractTableModel implementation
     */
    int
    rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int
    columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant
    data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray>
    roleNames() const override;

public slots:

signals:

private slots:
    void
    start();

    void
    stop();

    void
    onFindWiFi();

    void
    updateList(KSQWiFiNetworks &list);

private:
    KSQWiFiNetworks m_wifiList;

#if defined(Q_OS_MACOS) || defined(Q_OS_ANDROID)
    static const int kScanPeriodMs = 5000;
    QTimer m_timer;
#else

#if 1
    // TODO: Remove after fixing of deprecated functionality
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif
    QNetworkConfigurationManager m_ncm;
#if 1
#pragma GCC diagnostic pop
#endif
    QStringList
    _findWiFiGeneral();
#endif

#if defined(Q_OS_LINUX)
    KSQWiFiNetworks
    wifi_enum();
#endif
};

#endif // PROVISION_QT_WIFI_ENUM_H
