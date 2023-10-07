#ifndef FTPHANDLER_H
#define FTPHANDLER_H

#include "Utilities/common.h"
#include "Utilities/enumerations.h"
#include "Utilities/constants.h"
#include "Utilities/utils.h"
#include "Utilities/threading.h"
#include "Utilities/Logger.h"

class FTPHandler : public Singleton<FTPHandler>
{
public:
    FTPHandler();
    int initialize();
    int wifiSendFile(std::string fileLocation, std::string destFolder);
    int ethernetSendFile(std::string fileLocation, std::string destFolder);
    int gsm4GSendFile(std::string fileLocation, std::string destFolder);
    int wifiReceiveFile(std::string fileLocation, std::string destFolder);
    int ethernetReceiveFile(std::string fileLocation, std::string destFolder);
    int gsm4GReceiveFile(std::string fileLocation, std::string destFolder);

    std::string                     wifiUsername;
    std::string                     wifiPassword;
    std::string                     wifiServerAddress;
    std::string                     wifiServerPort;
    std::string                     ethernetUsername;
    std::string                     ethernetPassword;
    std::string                     ethernetServerAddress;
    std::string                     ethernetServerPort;
    std::string                     gsm4GUsername;
    std::string                     gsm4GPassword;
    std::string                     gsm4GServerAddress;
    std::string                     gsm4GServerPort;
};

#endif // FTPHANDLER_H
