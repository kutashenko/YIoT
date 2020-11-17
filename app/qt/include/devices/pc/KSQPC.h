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

#ifndef YIOT_PC_H
#define YIOT_PC_H

#include <QtCore>
//#include <virgil/iot/protocols/snap/lamp/lamp-structs.h>

#include <devices/KSQDeviceBase.h>

class KSQPC : public KSQDeviceBase {
Q_OBJECT
public:
    KSQPC() : KSQDeviceBase() { }
    KSQPC(VSQMac mac, QString name, QString img = "");
    KSQPC(const KSQPC& l);
    virtual ~KSQPC() = default;

    virtual QString
    _deviceType() const final { return "pc"; }

signals:
    void fireSetDeviceParams(const KSQPC &lamp);

public slots:

private:
    QString m_state;
};

Q_DECLARE_METATYPE(KSQPC)
Q_DECLARE_METATYPE(KSQPC*)

#endif // YIOT_PC_H
