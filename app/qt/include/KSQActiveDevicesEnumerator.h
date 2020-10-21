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

#ifndef PROVISION_QT_ACTIVE_DEVICES_ENUM_H
#define PROVISION_QT_ACTIVE_DEVICES_ENUM_H

#include <QtCore>
#include <QAbstractTableModel>

#include <virgil/iot/qt/VSQIoTKit.h>

#include <KSActiveDevice.h>

class KSQActiveDevicesEnumerator : public QAbstractTableModel {
    Q_OBJECT
public:
    enum Element { Name = Qt::UserRole, Image, ElementMax };

    KSQActiveDevicesEnumerator();
    virtual ~KSQActiveDevicesEnumerator();

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

    Q_INVOKABLE
    QString
    get(int index) const;

public slots:
    void
    start();

    void
    stop();

private:
    KSQActiveDevices m_devicesList;
};

#endif // PROVISION_QT_ACTIVE_DEVICES_ENUM_H
