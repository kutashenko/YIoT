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

#ifndef YIOT_DEVICE_BASE_H
#define YIOT_DEVICE_BASE_H

#include <QtCore>

#include <virgil/iot/qt/helpers/VSQMac.h>

class KSQDeviceBase : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY fireNameChanged)
    Q_PROPERTY(QString macAddr READ macAddr)
    Q_PROPERTY(bool active READ active NOTIFY fireActiveChanged)
public:
    KSQDeviceBase(VSQMac mac, QString name, QString img = "") {
        m_lastUpdate = QDateTime::currentDateTime();
        m_image = img;
        m_name = name;
        m_mac = mac;
        m_active = true;
    }

    KSQDeviceBase(const KSQDeviceBase& d) {
        m_lastUpdate = d.m_lastUpdate;
        m_image = d.m_image;
        m_name = d.m_name;
        m_mac = d.m_mac;
        m_active = d.m_active;
    }

    Q_INVOKABLE QString
    name() const { return m_name; }

    Q_INVOKABLE QString
    macAddr() const { return m_mac; }

    Q_INVOKABLE bool
    active() const { return m_active; }

    Q_INVOKABLE void
    setName(QString name) {
        if (name != m_name) {
            m_name = name;
            emit fireNameChanged(m_name);
        }
        emit fireSendNameUpdate(name);
    }

    bool operator<(const KSQDeviceBase& rhs) const {
        return m_name < rhs.m_name;
    }

protected:
    void
    _setRecivedName(QString name) {
        if (name != m_name) {
            m_name = name;
            emit fireNameChanged(m_name);
        }
    }

    void
    _setRecivedActivity(bool active) {
        if (active != m_active) {
            m_active = active;
            emit fireActiveChanged(m_active);
        }
    }

signals:
    void fireNameChanged(QString);
    void fireSendNameUpdate(QString);
    void fireActiveChanged(bool);

private:
    bool m_active;
    QDateTime m_lastUpdate;
    QString m_image;
    QString m_name;
    VSQMac m_mac;
};

#endif // YIOT_DEVICE_BASE_H
