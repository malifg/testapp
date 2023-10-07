#ifndef GSM4GTEST_H
#define GSM4GTEST_H

#include "Utilities/common.h"
#include "Utilities/enumerations.h"
#include "Utilities/constants.h"
#include "Utilities/utils.h"
#include "Utilities/threading.h"
#include "Utilities/Logger.h"
#include "testresult.h"
#include "HardwareController/hardwarecontroller.h"
#include "NetworkManager/ftphandler.h"
#include "TestHandler/wifitest.h"
#include "TestHandler/ethernettest.h"

class GSM4GTest : public Singleton<GSM4GTest>, public Thread
{
public:
    GSM4GTest();
    int initialize();
    void run();
    int getStatus();
    int checkConnectionTerminal();
    QString getIP();
    QString getIMEI();
    int setConfiguration();
    int connect();
    int disconnect();
    int sendShortResult();
    int sendLongResult();
    int receiveData();

    bool                                testStart = false;
    std::string                         APN;
    std::string                         username;
    std::string                         password;
    std::string                         PIN;
    QString                             connectionStatus;
    QString                             IP;
    QString                             IMEI;


};

#endif // GSM4GTEST_H
