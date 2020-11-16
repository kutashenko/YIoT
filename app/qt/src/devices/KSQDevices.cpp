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

#include <devices/KSQDevices.h>

void fireAboutToActivate();
void fireActivated();

/******************************************************************************/
KSQDevices &
KSQDevices::operator<<(KSQControllerBase *controller) {
    connect(controller, &KSQControllerBase::fireActivated, this, &KSQDevices::onGroupActivated);
    QSharedPointer<KSQControllerBase> e(controller);
    m_elements.push_back(e);
    return *this;
}

/******************************************************************************/
void
KSQDevices::onGroupActivated() {
    // TODO: Use correct insertion
    beginResetModel();
    endResetModel();
}

/******************************************************************************/
int
KSQDevices::rowCount(const QModelIndex &parent) const {
    int cnt = 0;
    for (const auto &el: m_elements) {
        if (el->rowCount()) {
            ++cnt;
        }
    }
    return cnt;
}

/******************************************************************************/
int
KSQDevices::columnCount(const QModelIndex &parent) const {
    return 1;
}

/******************************************************************************/
QVariant
KSQDevices::data(const QModelIndex &index, int role) const {
    int cnt = 0;
    for (const auto &el: m_elements) {
        if (el->rowCount()) {
            if (index.row() == cnt) {
                switch (role) {
                case Element::Name:
                    return el->name();

                case Element::Image:
                    return el->image();

                case Element::SubModel:
                    QVariant res;
                    res.setValue(el.get());
                    return res;
                }
            }
            ++cnt;
        }
    }
    return cnt;
}

/******************************************************************************/
QHash<int, QByteArray>
KSQDevices::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[Name] = "name";
    roles[Image] = "image";
    roles[SubModel] = "subModel";
    return roles;
}

/******************************************************************************/
