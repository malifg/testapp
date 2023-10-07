#ifndef RS485TEST_H
#define RS485TEST_H

#include "Utilities/common.h"
#include "Utilities/enumerations.h"
#include "Utilities/constants.h"
#include "Utilities/utils.h"
#include "Utilities/threading.h"
#include "Utilities/Logger.h"
#include "testresult.h"

class RS485Test : public Singleton<RS485Test>, public Thread
{
public:
    RS485Test();
    void run();
    int  initialize();
    void closePort();
    bool                isTester;
    bool                testStart = false;

private:
    void run(bool isTester);

private:
    int                 mHandle;
    std::atomic<bool>   mThreadCondition;
    std::thread         mThread;
    int                 mInterface;


};

#endif // RS485TEST_H
