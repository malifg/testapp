#ifndef AUDIOTEST_H
#define AUDIOTEST_H

#include "Utilities/common.h"
#include "Utilities/enumerations.h"
#include "Utilities/constants.h"
#include "Utilities/utils.h"
#include "Utilities/threading.h"
#include "Utilities/Logger.h"
#include "testresult.h"

class AudioTest : public Singleton<AudioTest>, public Thread
{
public:
    AudioTest();
    int initialize();
    void run();
    int playSound();

    bool                                testStart = false;
    QProcess                            _processAplay;
};

#endif // AUDIOTEST_H
