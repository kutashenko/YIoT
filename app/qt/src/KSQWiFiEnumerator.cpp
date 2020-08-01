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

/******************************************************************************/
KSQWiFiEnumerator::KSQWiFiEnumerator() {
    connect(&m_ncm, &QNetworkConfigurationManager::updateCompleted, this, &KSQWiFiEnumerator::onFindWiFi);
}

/******************************************************************************/
KSQWiFiEnumerator::~KSQWiFiEnumerator() {
    stop();
}

/******************************************************************************/
void
KSQWiFiEnumerator::start() {
    m_ncm.updateConfigurations();
    onFindWiFi();
}

/******************************************************************************/
void
KSQWiFiEnumerator::stop() {
}

/******************************************************************************/
void
KSQWiFiEnumerator::onFindWiFi() {
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

    wifiList.sort();
    m_wifiList = wifiList;
    qDebug() << m_wifiList;
    emit fireWiFiListUpdated(m_wifiList);
}

/******************************************************************************/
