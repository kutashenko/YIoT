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

#ifndef PROVISION_NETIF_BLE_LINUX_IMPL_H
#define PROVISION_NETIF_BLE_LINUX_IMPL_H

#include <virgil/iot/protocols/snap/snap-structs.h>

#ifdef __cplusplus
using namespace VirgilIoTKit;
extern "C" {
#endif

vs_netif_t *
ks_netif_ble(void);

#ifdef __cplusplus
}
#endif

#endif // PROVISION_NETIF_BLE_LINUX_IMPL_H
