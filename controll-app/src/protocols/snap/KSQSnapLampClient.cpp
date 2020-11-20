//  ────────────────────────────────────────────────────────────
//                     ╔╗  ╔╗ ╔══╗      ╔════╗
//                     ║╚╗╔╝║ ╚╣╠╝      ║╔╗╔╗║
//                     ╚╗╚╝╔╝  ║║  ╔══╗ ╚╝║║╚╝
//                      ╚╗╔╝   ║║  ║╔╗║   ║║
//                       ║║   ╔╣╠╗ ║╚╝║   ║║
//                       ╚╝   ╚══╝ ╚══╝   ╚╝
//    ╔╗╔═╗                    ╔╗                     ╔╗
//    ║║║╔╝                   ╔╝╚╗                    ║║
//    ║╚╝╝  ╔══╗ ╔══╗ ╔══╗  ╔╗╚╗╔╝  ╔══╗ ╔╗ ╔╗╔╗ ╔══╗ ║║  ╔══╗
//    ║╔╗║  ║║═╣ ║║═╣ ║╔╗║  ╠╣ ║║   ║ ═╣ ╠╣ ║╚╝║ ║╔╗║ ║║  ║║═╣
//    ║║║╚╗ ║║═╣ ║║═╣ ║╚╝║  ║║ ║╚╗  ╠═ ║ ║║ ║║║║ ║╚╝║ ║╚╗ ║║═╣
//    ╚╝╚═╝ ╚══╝ ╚══╝ ║╔═╝  ╚╝ ╚═╝  ╚══╝ ╚╝ ╚╩╩╝ ║╔═╝ ╚═╝ ╚══╝
//                    ║║                         ║║
//                    ╚╝                         ╚╝
//
//    Lead Maintainer: Roman Kutashenko <kutashenko@gmail.com>
//  ────────────────────────────────────────────────────────────

#include <virgil/iot/qt/VSQIoTKit.h>
#include <cstring>

using namespace VirgilIoTKit;

/******************************************************************************/
VSQSnapLampClient::VSQSnapLampClient() {
    vs_snap_lamp_client_service_t impl;
    memset(&impl, 0, sizeof(impl));
    impl.device_state_update = &VSQSnapLampClient::onUpdateState;
    m_snapService = vs_snap_lamp_client(impl);
}

/******************************************************************************/
vs_status_e
VSQSnapLampClient::onUpdateState(vs_status_e res, const vs_mac_addr_t *mac, const vs_snap_lamp_state_t *data) {
    if (VS_CODE_OK == res) {
        emit VSQSnapLampClient::instance().fireStateUpdate(*mac, *data);
    } else {
        emit VSQSnapLampClient::instance().fireStateError(*mac);
    }

    return VS_CODE_OK;
}

/******************************************************************************/
void
VSQSnapLampClient::requestState(const vs_mac_addr_t &mac) {
    vs_snap_lamp_get_state(vs_snap_netif_routing(), &mac);
}

/******************************************************************************/
void
VSQSnapLampClient::setState(const vs_mac_addr_t &mac, const vs_snap_lamp_state_t &state) {
    qDebug() << ">>> setState: " << (state.is_on ? "ON" : "OFF");
    vs_snap_lamp_set_state(vs_snap_netif_routing(), &mac, &state);
}

/******************************************************************************/
