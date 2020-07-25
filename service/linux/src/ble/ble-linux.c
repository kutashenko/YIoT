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
//   24 July 2020
//   Lead Maintainer: Roman Kutashenko <kutashenko@gmail.com>

#include "ble/ble-linux.h"
#include "ble/bluez.h"

#include <gio/gio.h>

#include <virgil/iot/logger/logger.h>
#include <virgil/iot/protocols/snap/snap-structs.h>

#define BLE_ADAPTER_0 "/org/bluez/hci0"

/******************************************************************************/
vs_status_e
ks_ble_start_advertisement(void) {
    VS_LOG_DEBUG(">>> advertisement");
    return VS_CODE_ERR_NOT_IMPLEMENTED;
}

/******************************************************************************/
vs_status_e
ks_ble_stop_advertisement(void) {
    VS_LOG_DEBUG("<<< advertisement");
    return VS_CODE_ERR_NOT_IMPLEMENTED;
}

/******************************************************************************/
vs_status_e
ks_ble_mac(vs_mac_addr_t *mac_addr) {
    static vs_mac_addr_t prepared_mac_addr;
    static bool is_ready = false;

    vs_status_e res = VS_CODE_ERR_MAC_SNAP;
    GDBusProxy *ifproxy = NULL;
    GVariant *prop = NULL;

    CHECK_NOT_ZERO_RET(mac_addr, VS_CODE_ERR_ZERO_ARGUMENT);

    if (!is_ready) {
        // Get DBus interface
        ifproxy = g_dbus_proxy_new_for_bus_sync(G_BUS_TYPE_SYSTEM,
                                                G_DBUS_PROXY_FLAGS_NONE,
                                                NULL,
                                                BLUEZ_NAME,
                                                BLE_ADAPTER_0,
                                                BLUEZ_ADAPTER_INTERFACE,
                                                NULL,
                                                NULL);
        BOOL_CHECK(ifproxy, "Cannot get DBus proxy for Adapter properties");

        // Get Address property as a string
        prop = g_dbus_proxy_get_cached_property(ifproxy, "Address");
        BOOL_CHECK(prop, "Cannot get BLE Address property");
        gchar const *const mac_str = g_variant_get_string(prop, NULL);

        // Parse MAC address string
        int values[6];
        int i;
        const int MAC_PARTS = 6;
        if (MAC_PARTS == sscanf(mac_str,
                                "%x:%x:%x:%x:%x:%x%*c",
                                &values[0],
                                &values[1],
                                &values[2],
                                &values[3],
                                &values[4],
                                &values[5])) {
            for (i = 0; i < 6; ++i) {
                prepared_mac_addr.bytes[i] = (uint8_t)values[i];
            }
            is_ready = true;
        }
    }

    if (is_ready) {
        memcpy(mac_addr, &prepared_mac_addr, sizeof(vs_mac_addr_t));
        res = VS_CODE_OK;
    }

terminate:

    // Clean
    if (ifproxy) {
        g_object_unref(ifproxy);
    }

    if (prop) {
        g_variant_unref(prop);
    }

    return res;
}

/******************************************************************************/