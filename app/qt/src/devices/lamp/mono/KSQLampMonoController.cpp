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

#include <devices/lamp/mono/KSQLampMonoController.h>

const QString KSQLampMonoController::kStateUnknown = "unknown";
const QString KSQLampMonoController::kStateOn = "on";
const QString KSQLampMonoController::kStateOff = "off";
const QStringList KSQLampMonoController::kStates = QStringList() << KSQLampMonoController::kStateUnknown
                                                                 << KSQLampMonoController::kStateOn
                                                                 << KSQLampMonoController::kStateOff;
/******************************************************************************/
KSQLampMonoController::KSQLampMonoController() : m_state(kStateUnknown) {
}

/******************************************************************************/
QString
KSQLampMonoController::state() {
    return m_state;
}

/******************************************************************************/
void
KSQLampMonoController::setState(QString state) {
    if (kStates.contains(state)) {
        m_state = state;
    } else {
        m_state = kStateUnknown;
    }
    emit fireStateChanged(m_state);
}

/******************************************************************************/
