#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include "Utilities/common.h"
#include "Utilities/enumerations.h"
#include "Utilities/constants.h"
#include "Utilities/utils.h"
#include "Utilities/threading.h"
#include "Utilities/Logger.h"
#include "testresult.h"
#include "TestHandler/ethernettest.h"
#include "TestHandler/gsm4gtest.h"
#include "TestHandler/wifitest.h"
#include "TestHandler/gpstest.h"
#include "NetworkManager/networkstabilitytest.h"



class FileHandler : public Singleton<FileHandler>
{
public:
    FileHandler();
    int saveResult();
    int loadResult();
};

#endif // FILEHANDLER_H
