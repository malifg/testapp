#ifndef RS232TEST_H
#define RS232TEST_H

#include "Utilities/common.h"
#include "Utilities/enumerations.h"
#include "Utilities/constants.h"
#include "Utilities/utils.h"
#include "Utilities/threading.h"
#include "Utilities/Logger.h"
#include "testresult.h"

class RS232Test : public Singleton<RS232Test>, public Thread
{
public:
    RS232Test();
    void run();
    int  initialize();
    void closePort();
    bool                isTester = false;
    bool                testStart = false;

private:
    void run(bool isTester);

private:
    int                 mHandle;
    std::atomic<bool>   mThreadCondition;
    std::thread         mThread;
    int                 mInterface;



};

#endif // RS232TEST_H
