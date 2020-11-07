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

#ifndef PROVISION_QT_LAMP_MONO_CONTROLLER_H
#define PROVISION_QT_LAMP_MONO_CONTROLLER_H

#include <QtCore>

#include <virgil/iot/qt/netif/VSQNetifBLEEnumerator.h>
#include <virgil/iot/qt/netif/VSQNetifBLE.h>

class KSQLampMonoController : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString state READ state WRITE setState NOTIFY fireStateChanged)

public:
    KSQLampMonoController();
    virtual ~KSQLampMonoController() = default;

    Q_INVOKABLE QString
    state();

signals:
    void fireStateChanged(QString);

public slots:
    Q_INVOKABLE void
    setState(QString state);

private:
    static const QString kStateUnknown;
    static const QString kStateOn;
    static const QString kStateOff;
    static const QStringList kStates;

    QString m_state;
};

#endif // PROVISION_QT_LAMP_MONO_CONTROLLER_H
