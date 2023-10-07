#ifndef CVENDTEST_H
#define CVENDTEST_H

#include <atomic>
#include <thread>
#include <string>

enum Request_type
{
    Send_Data_req,
    Send_Mac_req,
    Send_Ping_req
};

class CVENDTest
{
public:
    CVENDTest();
    ~CVENDTest();
    int  initialize();
    void start(Request_type req);
    void stop();
    bool isWorking() const;
    std::string getReceivedData() const;

private:
    void run(Request_type req);
    bool pingCVEND();
    bool pingCVENDNMAP();
    void doPing(std::string baseIP, std::string mac, int min, int max);

private:
    int mHandle;
    std::string         deviceIP = "";
    std::string         mac = "";
    std::string         recievedData;
    std::atomic<bool>   mThreadCondition;
    std::atomic<bool>   macFound;
    std::thread         mThread;
    TestResultsHandler* mTestResultsHandler;

};

#endif // CVENDTEST_H
