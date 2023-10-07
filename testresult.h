#ifndef TESTRESULT_H
#define TESTRESULT_H

#include "Utilities/common.h"
#include "Utilities/enumerations.h"
#include "Utilities/constants.h"
#include "Utilities/utils.h"
#include "Utilities/threading.h"
#include "Utilities/Logger.h"

class TestResult : public Singleton<TestResult>
{
public:
    TestResult();
    void reset();
    bool _testResult[TestCase::TestCount];
    std::string deviceID = "";
};

#endif // TESTRESULT_H
