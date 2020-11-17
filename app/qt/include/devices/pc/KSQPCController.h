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

#ifndef YIOT_PC_CONTROLLER_H
#define YIOT_PC_CONTROLLER_H

#include <set>

#include <QtCore>
#include <QAbstractTableModel>

#include <virgil/iot/qt/VSQIoTKit.h>

#include <devices/KSQControllerBase.h>
#include <devices/pc/KSQPC.h>

class KSQPCController : public KSQControllerBase {
Q_OBJECT
public:
    enum Element { Name = Qt::UserRole, Type, Mac, Active, Device, ElementMax };

    KSQPCController();
    virtual ~KSQPCController() = default;

    virtual QString name() const final { return tr("PC"); }

    virtual QString type() const final { return "pc"; }

    virtual QString image() const final { return tr("pc"); }

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
    // SNAP::INFO
    void
    onDeviceInfoUpdate(const VSQDeviceInfo &deviceInfo);

    // UI
    void
    onSetDeviceParams(const KSQPC &pc);

protected:
    std::pair <int, QSharedPointer<KSQPC>>
    findPC(const vs_mac_addr_t &mac);

private:
    std::list<QSharedPointer<KSQPC>> m_pcs;
};

#endif // YIOT_PC_CONTROLLER_H
