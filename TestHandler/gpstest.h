#ifndef GPSTEST_H
#define GPSTEST_H

#include "Utilities/common.h"
#include "Utilities/enumerations.h"
#include "Utilities/constants.h"
#include "Utilities/utils.h"
#include "Utilities/threading.h"
#include "Utilities/Logger.h"
#include "testresult.h"
#include "HardwareController/hardwarecontroller.h"

class GPSTest : public Singleton<GPSTest>, public Thread
{
public:
    GPSTest();
    int initialize();
    void run();
    int checkData();


    QByteArray                          GPSRawData;

    QString                             fixSatus;
    QString                             latitude;
    QString                             longitude;
    QString                             altitude;
    QString                             currentTime;
    QString                             currentDate;
    QString                             numberOfSat;
    QString                             accuracy;


    long                                startTime;
    long                                endTime;
    int                                 TTFF = 0;

    bool                                testStart;

    int                                 mHandle;
    std::atomic<bool>                   mThreadCondition;
    std::thread                         mThread;
    int                                 mInterface;

};

#endif // GPSTEST_H
