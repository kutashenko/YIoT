
#ifndef KSQANDROID_H
#define KSQANDROID_H

#include <QObject>
#include <KSWiFi.h>

class KSQAndroid {
public:
    KSQAndroid() = delete;

    static void
    hideSplashScreen();

    static KSQWiFiNetworks
    enumWifi();
};


#endif // KSQANDROID_H
