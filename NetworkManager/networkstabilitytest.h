#ifndef NETWORKSTABILITYTEST_H
#define NETWORKSTABILITYTEST_H

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
#include "TestHandler/wifitest.h"
#include "TestHandler/gsm4gtest.h"


class NetworkStabilityTest : public Singleton<NetworkStabilityTest>, public Thread
{
public:
    NetworkStabilityTest();
    int initialize();
    void run();

    bool            testStart;
    int             ethernetNumberOfSuccess;
    int             wifiNumberOfSuccess;
    int             gsm4GNumberOfSuccess;
    int             numberOfTests;
};

#endif // NETWORKSTABILITYTEST_H
