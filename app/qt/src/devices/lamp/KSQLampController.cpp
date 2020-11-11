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

/******************************************************************************/
KSQLampController::KSQLampController() {
    m_lamps.insert(KSQLamp(broadcastMac, "lamp 1"));
    m_lamps.insert(KSQLamp(broadcastMac, "lamp 2"));
    m_lamps.insert(KSQLamp(broadcastMac, "lamp 3"));
    m_lamps.insert(KSQLamp(broadcastMac, "lamp 4"));
    m_lamps.insert(KSQLamp(broadcastMac, "lamp 5"));
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
        auto l = std::next(m_lamps.begin(), index.row());

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
