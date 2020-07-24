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
//   23 July 2020
//   Lead Maintainer: Roman Kutashenko <kutashenko@gmail.com>

#include <arpa/inet.h>
#include <assert.h>
#include <stddef.h>

#include <virgil/iot/protocols/snap/snap-structs.h>

#include "ble/ble-linux.h"
#include "iotkit-impl/netif/netif-ble-linux.h"

static vs_status_e
_ble_init(struct vs_netif_t *netif, const vs_netif_rx_cb_t rx_cb, const vs_netif_process_cb_t process_cb);

static vs_status_e
_ble_deinit(struct vs_netif_t *netif);

static vs_status_e
_ble_tx(struct vs_netif_t *netif, const uint8_t *data, const uint16_t data_sz);

static vs_status_e
_ble_mac(const struct vs_netif_t *netif, struct vs_mac_addr_t *mac_addr);

static vs_netif_t _netif_ble = {.user_data = NULL,
                                .init = _ble_init,
                                .deinit = _ble_deinit,
                                .tx = _ble_tx,
                                .mac_addr = _ble_mac,
                                .packet_buf_filled = 0};

static vs_netif_rx_cb_t _netif_ble_rx_cb = 0;
static vs_netif_process_cb_t _netif_ble_process_cb = 0;

#define RX_BUF_SZ (2048)

/******************************************************************************/
static vs_status_e
_ble_connect() {

    ks_ble_start_advertisement();

    return VS_CODE_ERR_NOT_IMPLEMENTED;

    //    terminate:
    //
    //    _ble_deinit(&_netif_ble);
    //
    //    return VS_CODE_ERR_SOCKET;
}

/******************************************************************************/
static vs_status_e
_ble_tx(struct vs_netif_t *netif, const uint8_t *data, const uint16_t data_sz) {
    return VS_CODE_ERR_NOT_IMPLEMENTED;
}

/******************************************************************************/
static vs_status_e
_ble_init(struct vs_netif_t *netif, const vs_netif_rx_cb_t rx_cb, const vs_netif_process_cb_t process_cb) {
    assert(rx_cb);
    (void)netif;
    _netif_ble_rx_cb = rx_cb;
    _netif_ble_process_cb = process_cb;
    _netif_ble.packet_buf_filled = 0;
    _ble_connect();

    return VS_CODE_OK;
}

/******************************************************************************/
static vs_status_e
_ble_deinit(struct vs_netif_t *netif) {
    ks_ble_stop_advertisement();
    return VS_CODE_ERR_NOT_IMPLEMENTED;
}

/******************************************************************************/
static vs_status_e
_ble_mac(const struct vs_netif_t *netif, struct vs_mac_addr_t *mac_addr) {
    (void)netif;

    if (mac_addr) {
        return VS_CODE_ERR_NOT_IMPLEMENTED;
    }

    return VS_CODE_ERR_NULLPTR_ARGUMENT;
}

/******************************************************************************/
vs_netif_t *
ks_netif_ble(void) {
    return &_netif_ble;
}

/******************************************************************************/
