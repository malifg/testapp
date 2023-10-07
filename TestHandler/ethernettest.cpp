#include "ethernettest.h"

EthernetTest::EthernetTest()
{
}

int EthernetTest::initialize(){
    testStart = false;
    connectionStatus = "";
    IP = "";
    MAC = "";
}


void EthernetTest::run(){
    while(true){
        if(testStart){
            int ethernetRet = EthernetTest::instance()->getStatus();
            int wifiRet = WiFiTest::instance()->getStatus();
            int gsm4gRet = GSM4GTest::instance()->getStatus();

            if(ethernetRet != OK){
                EthernetTest::instance()->connect();
            }
            if(wifiRet == OK){
                WiFiTest::instance()->disconnect();
            }
            if(gsm4gRet == OK){
                GSM4GTest::instance()->disconnect();
            }

            ethernetRet = EthernetTest::instance()->checkConnectionTerminal();
            if(ethernetRet == OK)
                connectionStatus = "Connected";
            if(ethernetRet == ETHERNET_DOES_NOT_CONNECT)
                connectionStatus = "Disconnected";
            if(ethernetRet == ETHERNET_DOES_NOT_FOUND)
                connectionStatus = "HardwareError";

            IP = getIP();
            MAC = getMAC();
            sendShortResult();
            receiveData();

            testStart = false;
        }
    }
}

int EthernetTest::getStatus(){
    QString ethernetStatus = HardwareController::instance()->executeCommand("nmcli d | awk '/eth0/ {print $3}'").c_str();

    ethernetStatus.remove(ethernetStatus.size() - 1, 1);

    if(ethernetStatus == "connected"){
        return OK;
    }
    if(ethernetStatus == "disconnected"){
        return WIFI_DOES_NOT_CONNECT;
    }
    return WIFI_DOES_NOT_FOUND;
}

int EthernetTest::checkConnectionTerminal(){
    QString ethernetStatus = HardwareController::instance()->executeCommand("nmcli d | awk '/eth0/ {print $3}'").c_str();

    ethernetStatus.remove(ethernetStatus.size() - 1, 1);

    if(ethernetStatus == "connected"){
        TestResult::instance()->_testResult[TestCase::Ethernet_Connection_Status] = true;
        return OK;
    }
    if(ethernetStatus == "disconnected"){
        TestResult::instance()->_testResult[TestCase::Ethernet_Connection_Status] = false;
        return ETHERNET_DOES_NOT_CONNECT;
    }
    TestResult::instance()->_testResult[TestCase::Ethernet_Connection_Status] = false;
    return ETHERNET_DOES_NOT_FOUND;
}

QString EthernetTest::getIP(){
    QString ethernetIP = HardwareController::instance()->executeCommand("nmcli -p device show eth0 | awk '/IP4.ADDRESS/ {print $2}'").c_str();

    if(ethernetIP.size() < 4){
        TestResult::instance()->_testResult[TestCase::Ethernet_Get_IP] = false;
        return "";
    }

    ethernetIP.remove(ethernetIP.size() - 4, 4);
    TestResult::instance()->_testResult[TestCase::Ethernet_Get_IP] = true;
    return ethernetIP;
}

QString EthernetTest::getMAC(){
    QString ethernetMAC = HardwareController::instance()->executeCommand("nmcli -p device show eth0 | awk '/GENERAL.HWADDR/ {print $2}'").c_str();

    if(ethernetMAC.size() < 18){
        TestResult::instance()->_testResult[TestCase::Ethernet_Get_MAC] = false;
        return "";
    }

    ethernetMAC.remove(ethernetMAC.size() - 1, 1);
    TestResult::instance()->_testResult[TestCase::Ethernet_Get_MAC] = true;
    return ethernetMAC;
}

int EthernetTest::connect(){
    HardwareController::instance()->executeCommand("nmcli d connect eth0").c_str();

    return OK;
}

int EthernetTest::disconnect(){
    HardwareController::instance()->executeCommand("nmcli d disconnect eth0").c_str();

    return OK;
}

int EthernetTest::sendShortResult(){
    if(TestResult::instance()->deviceID != ""){
        if(FTPHandler::instance()->ethernetSendFile(TEST_FILE_PREFIX + TestResult::instance()->deviceID + ".SCV", REMOTE_SHORT_TEST_RESULT_DIRECTORY) == OK){
            TestResult::instance()->_testResult[TestCase::Ethernet_Send_Data] = true;
            return OK;
        }
    }
    return ETHERNET_SEND_DATA_ERROR;
}

int EthernetTest::sendLongResult(){
    if(TestResult::instance()->deviceID != ""){
        if(FTPHandler::instance()->ethernetSendFile(TEST_FILE_PREFIX + TestResult::instance()->deviceID + ".SCV", REMOTE_LONG_TEST_RESULT_DIRECTORY) == OK){
            TestResult::instance()->_testResult[TestCase::Ethernet_Send_Data] = true;
            return OK;
        }
    }
    return ETHERNET_SEND_DATA_ERROR;
}

int EthernetTest::receiveData(){
    if(FTPHandler::instance()->ethernetReceiveFile(REMOTE_ETHERNET_TEST_FILE_1, NETWORK_TEST_LOCATION) == OK){
        if(FTPHandler::instance()->ethernetReceiveFile(REMOTE_ETHERNET_TEST_FILE_2, NETWORK_TEST_LOCATION) == OK){
            QString ethernetTestRet = HardwareController::instance()->executeCommand("cat " NETWORK_TEST_LOCATION "/" LOCAL_ETHERNET_TEST_FILE).c_str();
            if(ethernetTestRet == "OK"){
                TestResult::instance()->_testResult[TestCase::Ethernet_Receive_Data] = true;
                HardwareController::instance()->executeCommand("rm " NETWORK_TEST_LOCATION "/" LOCAL_ETHERNET_TEST_FILE).c_str();
                return OK;
            }
        }
    }
    return ETHERNET_RECEIVE_DATA_ERROR;
}
