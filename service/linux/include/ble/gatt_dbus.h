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

#ifndef PROVISION_BLE_GATT_LINUX_H
#define PROVISION_BLE_GATT_LINUX_H


/**
 * @name BlueZ GATT Service D-Bus Object Paths
 *
 * GATT Service hierarchy is the following:
 *
 *  -> /com/kutashenko/gatt/advertisement0
 *
 *  -> /com/kutashenko/gatt/<hciX>/service0
 *    |   - OIC GATT Service
 *    |
 *    -> /com/kutashenko/gatt/<hciX>/service0/char0
 *    | |   - OIC GATT Request Characteristic Value
 *    | |
 *    | -> /com/kutashenko/gatt/<hciX>/service0/char0/desc0
 *    |       - OIC GATT Request User Description Descriptor
 *    |
 *    -> /com/kutashenko/gatt/<hciX>/service0/char1
 *      |   - OIC GATT Response Characteristic Value
 *      |
 *      -> /com/kutashenko/gatt/<hciX>/service0/char1/desc0
 *            - OIC GATT Response User Description Descriptor
 */

#define KS_GATT_SERVICE_ROOT_PATH "/com/kutashenko/gatt"
#define KS_LE_ADVERTISEMENT_PATH "advertisement0"
#define KS_GATT_SERVICE_PATH  "service0"
#define KS_GATT_REQUEST_CHRC_PATH "char0"
#define KS_GATT_REQUEST_USER_DESC_PATH "desc0"
#define KS_GATT_RESPONSE_CHRC_PATH "char1"
#define KS_GATT_RESPONSE_USER_DESC_PATH "desc0"

#endif // PROVISION_BLE_GATT_LINUX_H
