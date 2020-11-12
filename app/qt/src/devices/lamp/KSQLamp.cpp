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

const QString KSQLamp::kStateUnknown = "unknown";
const QString KSQLamp::kStateOn = "on";
const QString KSQLamp::kStateOff = "off";
const QStringList KSQLamp::kStates = QStringList() << KSQLamp::kStateUnknown
                                                             << KSQLamp::kStateOn
                                                             << KSQLamp::kStateOff;
/******************************************************************************/

KSQLamp::KSQLamp(VSQMac mac, QString name, QString img) :
 KSQDeviceBase(mac, name, img) {
    m_state = kStateUnknown;
}

/******************************************************************************/
KSQLamp::KSQLamp(const KSQLamp& l) : KSQDeviceBase(l) {
    m_state = l.m_state;
}

/******************************************************************************/
QString
KSQLamp::state() const {
    return m_state;
}

/******************************************************************************/
void
KSQLamp::setState(QString state) {
    if (kStates.contains(state)) {
        m_state = state;
    } else {
        m_state = kStateUnknown;
    }
    emit fireStateChanged(m_state);
    emit fireSetDeviceParams(*this);
}

/******************************************************************************/
