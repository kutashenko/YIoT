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

#include <devices/lamp/KSQLampController.h>

#include <virgil/iot/qt/protocols/snap/VSQSnapLampClient.h>
#include <virgil/iot/qt/protocols/snap/VSQSnapINFOClient.h>

/******************************************************************************/
KSQLampController::KSQLampController() {
    // SNAP::INFO service
    connect(&VSQSnapInfoClient::instance(), &VSQSnapInfoClient::fireNewDevice,
            this, &KSQLampController::onDeviceInfoUpdate, Qt::QueuedConnection);

    connect(&VSQSnapInfoClient::instance(), &VSQSnapInfoClient::fireDeviceInfo,
            this, &KSQLampController::onDeviceInfoUpdate, Qt::QueuedConnection);

    // SNAP::LAMP service
    connect(&VSQSnapLampClient::instance(), &VSQSnapLampClient::fireStateUpdate,
            this, &KSQLampController::onLampStateUpdate, Qt::QueuedConnection);

    connect(&VSQSnapLampClient::instance(), &VSQSnapLampClient::fireStateError,
            this, &KSQLampController::onLampError, Qt::QueuedConnection);


    // Test data
#if 1
    auto t = new QTimer();
    connect(t, &QTimer::timeout, [t, this]() {
        static int n = 0;
        if (n++ >= 10) {
            t->deleteLater();
            return;
        }

        vs_mac_addr_t mac;
        mac.bytes[0] = 0;
        mac.bytes[1] = 1;
        mac.bytes[2] = 2;
        mac.bytes[3] = 3;
        mac.bytes[4] = 4;
        mac.bytes[5] = n;

        vs_snap_lamp_state_t state = {0};
        state.is_on = n % 2;
        onLampStateUpdate(mac, state);

        VSQDeviceInfo deviceInfo;
        deviceInfo.m_mac = mac;
        deviceInfo.m_hasGeneralInfo = true;
        deviceInfo.m_deviceType = VSQDeviceType();
        deviceInfo.m_deviceRoles = VSQDeviceRoles() << VS_SNAP_DEV_THING;
        deviceInfo.m_tlVer = VSQFileVersion();
        deviceInfo.m_fwVer = VSQFileVersion();
        deviceInfo.m_manufactureId = VSQManufactureId();
        deviceInfo.m_hasStatistics = true;
        deviceInfo.m_sent = 123134;
        deviceInfo.m_received = 456234;
        onDeviceInfoUpdate(deviceInfo);
    });
    t->start(1000);
#endif
    // ~Test data
}

/******************************************************************************/
void
KSQLampController::onDeviceInfoUpdate(const VSQDeviceInfo &deviceInfo) {
    auto res = findLamp(deviceInfo.m_mac);
    auto lamp = res.second;
    if (lamp) {
        if (deviceInfo.m_hasGeneralInfo) {
            lamp->setDeviceID(deviceInfo.m_deviceRoles);
            lamp->setManufacture(deviceInfo.m_manufactureId);
            lamp->setDeviceID(deviceInfo.m_deviceType);
            lamp->setFwVersion(deviceInfo.m_fwVer);
            lamp->setTlVersion(deviceInfo.m_tlVer);
        }

        if (deviceInfo.m_hasStatistics) {
            lamp->setSentBytes(QString("%1").arg(deviceInfo.m_sent));
            lamp->setReceivedBytes(QString("%1").arg(deviceInfo.m_received));
        }

        const auto _idx = createIndex(res.first, 0);
        emit dataChanged(_idx, _idx);
    }
}

/******************************************************************************/
void
KSQLampController::onLampStateUpdate(const vs_mac_addr_t mac,
                                     const vs_snap_lamp_state_t state) {
    auto res = findLamp(mac);
    auto lamp = res.second;
    if (!lamp) {
        // Add lamp

        bool activating = !m_lamps.size();

        if (activating) {
            emit fireAboutToActivate();
        }

        beginInsertRows(QModelIndex(), m_lamps.size(), m_lamps.size());

        auto newLamp = QSharedPointer<KSQLamp>::create(VSQMac(mac),
                                                       QString("test-%1").arg(m_lamps.size()));
        connect(newLamp.get(), &KSQLamp::fireSetDeviceParams,
                this, &KSQLampController::onSetDeviceParams);
        m_lamps.push_back(newLamp);

        endInsertRows();

        if (activating) {
            emit fireActivated();
        }
    }

    res = findLamp(mac);
    lamp = res.second;
    if (!lamp) {
        qDebug() << "Lamp adding error: " << VSQMac(mac).description();
        return;
    }

    lamp->setState(state.is_on ? KSQLamp::kStateOn : KSQLamp::kStateOff);

    const auto _idx = createIndex(res.first, 0);
    emit dataChanged(_idx, _idx);
}

/******************************************************************************/
void
KSQLampController::onLampError(const vs_mac_addr_t mac) {
    auto res = findLamp(mac);
    auto lamp = res.second;
    if (lamp) {
        qDebug() << "Lamp error: " << VSQMac(mac).description();
    }
}

/******************************************************************************/
void
KSQLampController::onSetDeviceParams(const KSQLamp &lamp) {
    vs_snap_lamp_state_t state;

    memset(&state, 0, sizeof(state));

    state.is_on = lamp.state() == KSQLamp::kStateOn;

    VSQSnapLampClient::instance().setState(lamp.qMacAddr(), state);
}

/******************************************************************************/
std::pair <int, QSharedPointer<KSQLamp>>
KSQLampController::findLamp(const vs_mac_addr_t &mac) {
    VSQMac qMac(mac);
    int pos = 0;
    for (auto el: m_lamps) {
        if (el->qMacAddr() == qMac) {
            return std::make_pair(pos, el);
        }
        ++pos;
    }
    return std::make_pair(-1, QSharedPointer<KSQLamp> (nullptr));
}

/******************************************************************************/
int
KSQLampController::rowCount(const QModelIndex &parent) const {
    return m_lamps.size();
}

/******************************************************************************/
int
KSQLampController::columnCount(const QModelIndex &parent) const {
    return 1;
}

/******************************************************************************/
QVariant
KSQLampController::data(const QModelIndex &index, int role) const {
    if (index.row() < m_lamps.size()) {
        auto l = *std::next(m_lamps.begin(), index.row());

        switch (role) {
        case Element::Name:
            return l->name();

        case Element::Type:
            return l->deviceType();

        case Element::Mac:
            return l->macAddr();

        case Element::Active:
            return l->active();

        case Element::State:
            return l->state();

        case Element::Device:
            QVariant res;
            res.setValue(const_cast<KSQLamp*>(&(*l)));
            return res;
        }
    }

    return QVariant();
}

/******************************************************************************/
QHash<int, QByteArray>
KSQLampController::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[Name] = "name";
    roles[Type] = "deviceType";
    roles[Mac] = "mac";
    roles[Active] = "active";
    roles[State] = "state";
    roles[Device] = "deviceController";
    return roles;
}

/******************************************************************************/
