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

#include "device-info.h"
#include <string.h>

/******************************************************************************/
void
ks_devinfo_manufacturer(vs_device_manufacture_id_t manufacture_id) {
    memset(manufacture_id, 0, sizeof(vs_device_manufacture_id_t));
}

/******************************************************************************/
void
ks_devinfo_device_type(vs_device_type_t device_type) {
    memset(device_type, 0, sizeof(vs_device_type_t));
}

/******************************************************************************/
void
ks_devinfo_device_serial(vs_device_serial_t serial) {
    memset(serial, 0, sizeof(vs_device_serial_t));
}

/******************************************************************************/
