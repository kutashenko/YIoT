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

#include <KSQActiveDevicesEnumerator.h>

#include <thread>

/******************************************************************************/
KSQActiveDevicesEnumerator::KSQActiveDevicesEnumerator() {
    m_devicesList["Lamp 1"] = KSActiveDeviceInfo("Bulb");
    m_devicesList["Temp Sensor 123"] = KSActiveDeviceInfo("Temp");
    m_devicesList["Front door lock 1"] = KSActiveDeviceInfo("Lock");
    m_devicesList["Lamp Office"] = KSActiveDeviceInfo("Bulb");
    m_devicesList["Test"] = KSActiveDeviceInfo("Bulb");
}

/******************************************************************************/
KSQActiveDevicesEnumerator::~KSQActiveDevicesEnumerator() {
    stop();
}

/******************************************************************************/
void
KSQActiveDevicesEnumerator::start() {
}

/******************************************************************************/
void
KSQActiveDevicesEnumerator::stop() {
}

/******************************************************************************/
int
KSQActiveDevicesEnumerator::rowCount(const QModelIndex &parent) const {
    return m_devicesList.count();
}

/******************************************************************************/
int
KSQActiveDevicesEnumerator::columnCount(const QModelIndex &paren) const {
    return 1;
}

/******************************************************************************/
QVariant
KSQActiveDevicesEnumerator::data(const QModelIndex &index, int role) const {
    if (index.row() < m_devicesList.count()) {
        auto key = m_devicesList.keys().at(index.row());

        switch (role) {
        case Element::Name:
            return key;

        case Element::Image:
            return m_devicesList[key].image;
        }
    }

    return QVariant();
}

/******************************************************************************/
QHash<int, QByteArray>
KSQActiveDevicesEnumerator::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[Name] = "name";
    roles[Image] = "image";
    return roles;
}

/******************************************************************************/
QString
KSQActiveDevicesEnumerator::get(int index) const {
    if (index >= 0 && index < m_devicesList.count()) {
        return m_devicesList.keys().at(index);
    }

    return "";
}

/******************************************************************************/
