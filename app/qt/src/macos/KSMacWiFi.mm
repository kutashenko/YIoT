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
//   04 August 2020
//   Lead Maintainer: Roman Kutashenko <kutashenko@gmail.com>

#include <macos/KSMacWiFi.h>
#import <CoreWLAN/CoreWLAN.h>

/******************************************************************************/
QStringList wifi_enum_mac() {
    QStringList res;
    CWInterface* wifi = [[CWWiFiClient sharedWiFiClient] interface];
    NSArray *networkScan = [[wifi scanForNetworksWithName:nil error:nil] allObjects];
    for (CWNetwork *network in networkScan) {
        #if 1
        NSLog ( @"SSID: %@ ,\n \
              BSSID: %@ , \n \
              rssiValue: %ld , \n \
              noiseMeasurement: %ld, \n\
              beaconInterval: %ld , \n \
              countryCode: %@ \n ,\
              ibss: %i ,\n\
              wlanChannel: %@ , \n\
              ", [network ssid],[network bssid],[network rssiValue],[network noiseMeasurement],(long)[network beaconInterval], [network countryCode] , [network ibss], [[network wlanChannel]description]);
        #endif
        res << QString::fromNSString([network ssid]);
    }

    return res;
}

/******************************************************************************/
