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

/******************************************************************************/
KSQWiFiEnumerator::KSQWiFiEnumerator() {
#if defined(Q_OS_MACOS)
    m_timer.setSingleShot(false);
    m_timer.setInterval(kScanPeriodMs);
    connect(&m_timer, &QTimer::timeout, this, &KSQWiFiEnumerator::onFindWiFi);
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
#if !defined(Q_OS_MACOS) && !defined(Q_OS_WIN32)
KSQWiFiNetworks
KSQWiFiEnumerator::wifi_enum() {
    KSQWiFiNetworks wifiList;
    auto netcfgList = m_ncm.allConfigurations();
    for (auto &x : netcfgList) {
        qDebug() << x.name() << " : " << x.bearerTypeName();
        if (x.bearerType() == QNetworkConfiguration::BearerWLAN) {
            if (x.name() != "") {
                wifiList[x.name()] = KSWiFiInfo();
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
        auto list = wifi_enum();
        const bool isSame = list.keys() == m_wifiList.keys();
        m_wifiList = list;

        QVector<int> roles;
        if (isSame) {
            roles << RSSI;
        } else {
            beginResetModel();
            endResetModel();
        }

        auto topLeft = createIndex(0, 0);
        auto bottomRight = createIndex(m_wifiList.count(), 0);
        emit dataChanged(topLeft, bottomRight, roles);

        qDebug() << m_wifiList.keys();
        emit fireWiFiListUpdated(m_wifiList.keys());
    });

    t.detach();
}

/******************************************************************************/
int
KSQWiFiEnumerator::rowCount(const QModelIndex &parent) const {
    return m_wifiList.count();
}

/******************************************************************************/
int
KSQWiFiEnumerator::columnCount(const QModelIndex &paren) const {
    return 1;
}

/******************************************************************************/
QVariant
KSQWiFiEnumerator::data(const QModelIndex &index, int role) const {
    if (index.row() < m_wifiList.count()) {
        auto key = m_wifiList.keys().at(index.row());

        switch (role) {
        case Element::Name:
            return key;

        case Element::RSSI:
            return m_wifiList[key].rssi;
        }
    }

    return QVariant();
}

/******************************************************************************/
QHash<int, QByteArray>
KSQWiFiEnumerator::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[Name] = "name";
    roles[RSSI] = "rssi";
    return roles;
}

/******************************************************************************/
QString
KSQWiFiEnumerator::get(int index) const {
    if (index >= 0 && index < m_wifiList.count()) {
        return m_wifiList.keys().at(index);
    }

    return "";
}

/******************************************************************************/
