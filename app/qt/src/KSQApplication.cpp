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

#include <QtCore>
#include <QtQml>

#include <KSQApplication.h>
#include <KSQWiFiEnumerator.h>
#include <virgil/iot/qt/netif/VSQNetifBLE.h>
#include <virgil/iot/qt/netif/VSQNetifBLEEnumerator.h>
#include <virgil/iot/logger/logger.h>

/******************************************************************************/
int
KSQApplication::run() {
    QQmlApplicationEngine engine;
    VSQNetifBLEEnumerator bleEnumerator;
    KSQWiFiEnumerator wifiEnumerator;

    // Prepare IoTKit data
    auto netifBLE = QSharedPointer<VSQNetifBLE>::create();
    auto features = VSQFeatures() << VSQFeatures::SNAP_CFG_CLIENT;
    auto impl = VSQImplementations() << netifBLE;
    auto roles = VSQDeviceRoles() << VirgilIoTKit::VS_SNAP_DEV_CONTROL;
    auto appConfig = VSQAppConfig() << VSQManufactureId() << VSQDeviceType() << VSQDeviceSerial()
                                    << VirgilIoTKit::VS_LOGLEV_DEBUG << roles;

    // Connect signals and slots
    connect(&bleEnumerator, &VSQNetifBLEEnumerator::fireDeviceSelected, netifBLE.data(), &VSQNetifBLE::onOpenDevice);

    connect(netifBLE.data(),
            &VSQNetifBLE::fireDeviceReady,
            &VSQIoTKitFacade::instance().snapCfgClient(),
            &VSQSnapCfgClient::onConfigureDevices);

    connect(&VSQIoTKitFacade::instance().snapCfgClient(),
            SIGNAL(fireConfigurationDone(bool)),
            netifBLE.data(),
            SLOT(onCloseDevice()));

    // Initialize IoTKit
    if (!VSQIoTKitFacade::instance().init(features, impl, appConfig)) {
        VS_LOG_CRITICAL("Unable to initialize IoTKIT");
        return -1;
    }

    // Start WiFi enumeration
    wifiEnumerator.start();

    // Initialize QML
    QQmlContext *context = engine.rootContext();
    context->setContextProperty("bleEnum", &bleEnumerator);
    context->setContextProperty("SnapCfgClient", &VSQIoTKitFacade::instance().snapCfgClient());

    const QUrl url(QStringLiteral("qrc:/qml/Main.qml"));
    engine.load(url);

    // Change size of window for desctop version
#if !defined(Q_OS_ANDROID) && !defined(Q_OS_IOS) && !defined(Q_OS_WATCHOS)
    {
        QObject *rootObject(engine.rootObjects().first());
        rootObject->setProperty("width", 640);
        rootObject->setProperty("height", 400);
    }
#endif

    return QGuiApplication::instance()->exec();
}

/******************************************************************************/
