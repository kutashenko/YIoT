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
#include <ui/VSQUiHelper.h>
#include <virgil/iot/logger/logger.h>

#ifdef Q_OS_ANDROID
#include "android/KSQAndroid.h"
#endif // Q_OS_ANDROID

/******************************************************************************/
int
KSQApplication::run() {
    QQmlApplicationEngine engine;
    VSQUiHelper uiHelper;

    // Prepare IoTKit data
    auto features = VSQFeatures() << VSQFeatures::SNAP_CFG_CLIENT;
    auto impl = VSQImplementations() << m_bleController.netif();
    auto roles = VSQDeviceRoles() << VirgilIoTKit::VS_SNAP_DEV_CONTROL;
    auto appConfig = VSQAppConfig() << VSQManufactureId() << VSQDeviceType() << VSQDeviceSerial()
                                    << VirgilIoTKit::VS_LOGLEV_DEBUG << roles;

    // Initialize IoTKit
    if (!VSQIoTKitFacade::instance().init(features, impl, appConfig)) {
        VS_LOG_CRITICAL("Unable to initialize IoTKIT");
        return -1;
    }

    // Initialize QML
    QQmlContext *context = engine.rootContext();
    context->setContextProperty("UiHelper", &uiHelper);
    context->setContextProperty("app", this);
    context->setContextProperty("activeDevEnum", &m_activeDevicesEnumerator);
    context->setContextProperty("bleController", &m_bleController);
    context->setContextProperty("bleEnum", m_bleController.model());
    context->setContextProperty("wifiEnum", &m_wifiEnumerator);
    context->setContextProperty("monoLampController", &m_lampMonoController);
    qmlRegisterSingletonType(QUrl("qrc:/qml/theme/Theme.qml"), "Theme", 1, 0, "Theme");
    const QUrl url(QStringLiteral("qrc:/qml/Main.qml"));
    engine.load(url);

    QTimer::singleShot(200, []() {
#ifdef Q_OS_ANDROID
        KSQAndroid::hideSplashScreen();
        KSQAndroid::requestPermissions();
#endif
    });

    return QGuiApplication::instance()->exec();
}

/******************************************************************************/
QString
KSQApplication::organizationDisplayName() const {
    return tr("Your IoT");
}

/******************************************************************************/
QString
KSQApplication::applicationDisplayName() const {
    return tr("YIoT");
}

/******************************************************************************/
