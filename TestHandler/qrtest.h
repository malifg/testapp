#ifndef QRTEST_H
#define QRTEST_H

#include "Utilities/common.h"
#include "Utilities/enumerations.h"
#include "Utilities/constants.h"
#include "Utilities/utils.h"
#include "Utilities/threading.h"
#include "Utilities/Logger.h"
#include "testresult.h"
#include "HardwareController/hardwarecontroller.h"

class QRTest : public Singleton<QRTest>, public Thread
{
public:
    QRTest();
    int initialize();
    void run();

    bool                                testStart = false;
    int                                 mHandle;
    std::atomic<bool>                   mThreadCondition;
    std::thread                         mThread;
    int                                 mInterface;
};

#endif // QRTEST_H
