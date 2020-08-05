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

#include <KSQWiFiEnumerator.h>

#include <thread>

#if defined(Q_OS_MACOS)
#include <macos/KSMacWiFi.h>
#endif

#if defined(Q_OS_WIN32)
#include <win/KSWinWiFi.h>
#endif

/******************************************************************************/
KSQWiFiEnumerator::KSQWiFiEnumerator() {
#if defined(Q_OS_MACOS)
    m_timer.setSingleShot(false);
    m_timer.setInterval(kScanPeriodMs);
#else
    connect(&m_ncm, &QNetworkConfigurationManager::updateCompleted, this, &KSQWiFiEnumerator::onFindWiFi);
#endif
}

/******************************************************************************/
KSQWiFiEnumerator::~KSQWiFiEnumerator() {
    stop();
}

/******************************************************************************/
void
KSQWiFiEnumerator::start() {
#if defined(Q_OS_MACOS)
    m_timer.start();
#else
    m_ncm.updateConfigurations();
#endif
    onFindWiFi();
}

/******************************************************************************/
void
KSQWiFiEnumerator::stop() {
#if defined(Q_OS_MACOS)
    m_timer.stop();
#endif
}

/******************************************************************************/
#if !defined(Q_OS_MACOS)
QStringList
KSQWiFiEnumerator::_findWiFiGeneral() {
    QStringList wifiList;
    auto netcfgList = m_ncm.allConfigurations();
    for (auto &x : netcfgList) {
        qDebug() << x.name() << " : " << x.bearerTypeName();
        if (x.bearerType() == QNetworkConfiguration::BearerWLAN) {
            if (x.name() == "") {
                wifiList << "Unknown(Other Network)";
            } else {
                wifiList << x.name();
            }
        }
    }

    return wifiList;
}
#endif

/******************************************************************************/
void
KSQWiFiEnumerator::onFindWiFi() {
    std::thread t([this]() {
        QStringList wifiList;
#if defined(Q_OS_MACOS)
        wifiList = wifi_enum_mac();
#elif defined(Q_OS_WIN32)
        wifiList = wifi_enum_win();
#else
        wifiList = _findWiFiGeneral();
#endif

        wifiList.sort();
        m_wifiList = wifiList;
        qDebug() << m_wifiList;
        emit fireWiFiListUpdated(m_wifiList);
    });

    t.detach();
}

/******************************************************************************/
