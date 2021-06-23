//  ────────────────────────────────────────────────────────────
//                     ╔╗  ╔╗ ╔══╗      ╔════╗
//                     ║╚╗╔╝║ ╚╣╠╝      ║╔╗╔╗║
//                     ╚╗╚╝╔╝  ║║  ╔══╗ ╚╝║║╚╝
//                      ╚╗╔╝   ║║  ║╔╗║   ║║
//                       ║║   ╔╣╠╗ ║╚╝║   ║║
//                       ╚╝   ╚══╝ ╚══╝   ╚╝
//    ╔╗╔═╗                    ╔╗                     ╔╗
//    ║║║╔╝                   ╔╝╚╗                    ║║
//    ║╚╝╝  ╔══╗ ╔══╗ ╔══╗  ╔╗╚╗╔╝  ╔══╗ ╔╗ ╔╗╔╗ ╔══╗ ║║  ╔══╗
//    ║╔╗║  ║║═╣ ║║═╣ ║╔╗║  ╠╣ ║║   ║ ═╣ ╠╣ ║╚╝║ ║╔╗║ ║║  ║║═╣
//    ║║║╚╗ ║║═╣ ║║═╣ ║╚╝║  ║║ ║╚╗  ╠═ ║ ║║ ║║║║ ║╚╝║ ║╚╗ ║║═╣
//    ╚╝╚═╝ ╚══╝ ╚══╝ ║╔═╝  ╚╝ ╚═╝  ╚══╝ ╚╝ ╚╩╩╝ ║╔═╝ ╚═╝ ╚══╝
//                    ║║                         ║║
//                    ╚╝                         ╚╝
//
//    Lead Maintainer: Roman Kutashenko <kutashenko@gmail.com>
//  ────────────────────────────────────────────────────────────

#ifndef YIOT_EXTENSION_CONTROLLER_BASE_H
#define YIOT_EXTENSION_CONTROLLER_BASE_H

#include <QtCore>
#include <QHash>
#include <QAbstractTableModel>

#include <virgil/iot/qt/VSQIoTKit.h>
#include <virgil/iot/qt/helpers/VSQMac.h>

#include <yiot-iotkit/secmodule/KSQSessionKey.h>

#include <common/protocols/snap/user/user-structs.h>
#include <controllers/devices/KSQDevicesType.h>
#include <controllers/extensions/KSQOneExtension.h>

class KSQExtensionControllerBase : public QObject {
    Q_OBJECT
public:
    KSQExtensionControllerBase() = default;
    virtual ~KSQExtensionControllerBase() = default;

    virtual bool
    load(const QString &integrationDir, QSharedPointer<KSQOneExtension> extension) = 0;

    QSharedPointer<QObject>
    qmlProcessor() {
        return m_qmlProcessor;
    }

    void
    setQmlEngine(QQmlApplicationEngine *engine) {
        m_engine = engine;
    }

protected:
    QSharedPointer<QObject> m_qmlProcessor;

    QQmlApplicationEngine *m_engine;
};

#endif // YIOT_EXTENSION_CONTROLLER_BASE_H
