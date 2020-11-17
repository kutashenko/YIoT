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

#ifndef YIOT_DEVICE_CONTROLLER_BASE_H
#define YIOT_DEVICE_CONTROLLER_BASE_H

#include <QtCore>
#include <QHash>
#include <QAbstractTableModel>

#include <virgil/iot/qt/VSQIoTKit.h>

class KSQControllerBase : public QAbstractTableModel {
Q_OBJECT
    Q_PROPERTY(bool collapsed READ collapsed WRITE setCollapsed NOTIFY fireCollapsedChanged)
public:

    KSQControllerBase() = default;
    virtual ~KSQControllerBase() = default;

    virtual QString
    name() const = 0;

    virtual QString
    type() const = 0;

    virtual QString
    image() const = 0;

    Q_INVOKABLE void
    setCollapsed(bool c) {
        if (m_collapsed != c) {
            m_collapsed = c;
            emit fireCollapsedChanged(m_collapsed);
        }
    }

    Q_INVOKABLE bool
    collapsed() { return m_collapsed; }

signals:
    void fireCollapsedChanged(bool);

    void fireAboutToActivate();
    void fireActivated();

private:
    bool m_collapsed = true;
};

#endif // YIOT_DEVICE_CONTROLLER_BASE_H
