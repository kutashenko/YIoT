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

#include <KSQBLEController.h>

#include <virgil/iot/qt/VSQIoTKit.h>

/******************************************************************************/
KSQBLEController::KSQBLEController() {
    m_netifBLE = QSharedPointer<VSQNetifBLE>::create();
    m_bleEnumerator.startDiscovery();

    // Connect signals and slots
    connect(m_netifBLE.data(),
            &VSQNetifBLE::fireDeviceReady,
            this,
            &KSQBLEController::onConnected);

    connect(m_netifBLE.data(),
            &VSQNetifBLE::fireDeviceDisconnected,
            this,
            &KSQBLEController::onDisconnected);

    connect(m_netifBLE.data(),
            &VSQNetifBLE::fireDeviceError,
            this,
            &KSQBLEController::onDeviceError);

    connect(&VSQIoTKitFacade::instance().snapCfgClient(),
            &VSQSnapCfgClient::fireConfigurationDone,
            this,
            &KSQBLEController::onConfigurationDone);
}

/******************************************************************************/
KSQBLEController::~KSQBLEController() {
    m_netifBLE->close();
}

/******************************************************************************/
QSharedPointer<VSQNetifBLE>
KSQBLEController::netif() {
    return m_netifBLE;
}

/******************************************************************************/
VSQNetifBLEEnumerator *
KSQBLEController::model() {
    return &m_bleEnumerator;
}

/******************************************************************************/
void
KSQBLEController::onConnected(bool success) {
    if (!success) {
        emit fireError(tr("Connection error"));
        return;
    }

    emit fireConnected();

    if (m_needWiFiConfig) {
        m_needWiFiConfig = false;
        VSQIoTKitFacade::instance().snapCfgClient().onConfigureDevices();
        emit fireDataSent();
    }
}

/******************************************************************************/
void
KSQBLEController::onDisconnected() {
    emit fireDisconnected();
}

/******************************************************************************/
void
KSQBLEController::onDeviceError() {
    emit fireError(tr("unknown"));
}

/******************************************************************************/
void
KSQBLEController::onConfigurationDone(bool) {
    m_netifBLE->close();
    emit fireDataReceived();
}

/******************************************************************************/
bool
KSQBLEController::configureWiFi(const QString & deviceName, const QString & ssid, const QString & password) {
    qDebug() << "deviceName: " << deviceName;
    qDebug() << "ssid      : " << ssid;
    qDebug() << "password  : " << password;

    auto ble = m_bleEnumerator.devInfo(deviceName);
    if (!ble.isValid()) {
        return false;
    }

    VSQIoTKitFacade::instance().snapCfgClient().onSetConfigData(ssid, password);
    m_needWiFiConfig = true;
    return m_netifBLE->open(ble);
}

/******************************************************************************/
