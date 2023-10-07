#ifndef WIFITEST_H
#define WIFITEST_H

#include "Utilities/common.h"
#include "Utilities/enumerations.h"
#include "Utilities/constants.h"
#include "Utilities/utils.h"
#include "Utilities/threading.h"
#include "Utilities/Logger.h"
#include "testresult.h"
#include "HardwareController/hardwarecontroller.h"
#include "NetworkManager/ftphandler.h"
#include "TestHandler/ethernettest.h"
#include "TestHandler/gsm4gtest.h"

class WiFiTest : public Singleton<WiFiTest>, public Thread
{
public:
    WiFiTest();
    int initialize();
    void run();
    int getStatus();
    int checkConnectionTerminal();
    QString getIP();
    QString getMAC();
    int connect();
    int disconnect();
    int sendShortResult();
    int sendLongResult();
    int receiveData();

    bool                                testStart = false;
    QString                             connectionStatus;
    QString                             IP;
    QString                             MAC;
};

#endif // WIFITEST_H
