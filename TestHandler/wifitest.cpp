#include "wifitest.h"

WiFiTest::WiFiTest()
{
}

int WiFiTest::initialize(){
    testStart = false;
    connectionStatus = "";
    IP = "";
    MAC = "";
}


void WiFiTest::run(){
    while(true){
        if(testStart){
            int ethernetRet = EthernetTest::instance()->getStatus();
            int wifiRet = WiFiTest::instance()->getStatus();
            int gsm4gRet = GSM4GTest::instance()->getStatus();

            if(ethernetRet == OK){
                EthernetTest::instance()->disconnect();
            }
            if(wifiRet != OK){
                WiFiTest::instance()->connect();
            }
            if(gsm4gRet == OK){
                GSM4GTest::instance()->disconnect();
            }

            wifiRet = WiFiTest::instance()->checkConnectionTerminal();
            if(wifiRet == OK)
                connectionStatus = "Connected";
            if(wifiRet == WIFI_DOES_NOT_CONNECT)
                connectionStatus = "Disconnected";
            if(wifiRet == WIFI_DOES_NOT_FOUND)
                connectionStatus = "HardwareError";

            IP = getIP();
            MAC = getMAC();
            sendShortResult();
            receiveData();

            testStart = false;
        }
    }
}

int WiFiTest::getStatus(){
    QString wifiStatus = HardwareController::instance()->executeCommand("nmcli d | awk '/wlan0/ {print $3}'").c_str();

    wifiStatus.remove(wifiStatus.size() - 1, 1);

    if(wifiStatus == "connected"){
        return OK;
    }
    if(wifiStatus == "disconnected"){
        return WIFI_DOES_NOT_CONNECT;
    }
    return WIFI_DOES_NOT_FOUND;
}

int WiFiTest::checkConnectionTerminal(){
    QString wifiStatus = HardwareController::instance()->executeCommand("nmcli d | awk '/wlan0/ {print $3}'").c_str();

    wifiStatus.remove(wifiStatus.size() - 1, 1);

    if(wifiStatus == "connected"){
        TestResult::instance()->_testResult[TestCase::WIFI_Connection_Status] = true;
        return OK;
    }
    if(wifiStatus == "disconnected"){
        TestResult::instance()->_testResult[TestCase::WIFI_Connection_Status] = false;
        return WIFI_DOES_NOT_CONNECT;
    }
    TestResult::instance()->_testResult[TestCase::WIFI_Connection_Status] = false;
    return WIFI_DOES_NOT_FOUND;
}

QString WiFiTest::getIP(){
    QString wifiIP = HardwareController::instance()->executeCommand("nmcli -p device show wlan0 | awk '/IP4.ADDRESS/ {print $2}'").c_str();

    if(wifiIP.size() < 4){
        TestResult::instance()->_testResult[TestCase::WIFI_Get_IP] = false;
        return "";
    }

    wifiIP.remove(wifiIP.size() - 4, 4);
    TestResult::instance()->_testResult[TestCase::WIFI_Get_IP] = true;
    return wifiIP;
}

QString WiFiTest::getMAC(){
    QString wifiMAC = HardwareController::instance()->executeCommand("nmcli -p device show wlan0 | awk '/GENERAL.HWADDR/ {print $2}'").c_str();

    if(wifiMAC.size() < 18){
        TestResult::instance()->_testResult[TestCase::WIFI_Get_MAC] = false;
        return "";
    }

    wifiMAC.remove(wifiMAC.size() - 1, 1);
    TestResult::instance()->_testResult[TestCase::WIFI_Get_MAC] = true;
    return wifiMAC;
}

int WiFiTest::connect(){
    HardwareController::instance()->executeCommand("nmcli d wifi connect " WIFI_SSID " password " WIFI_PASSWORD).c_str();

    return OK;
}

int WiFiTest::disconnect(){
    HardwareController::instance()->executeCommand("nmcli d disconnect wlan0").c_str();

    return OK;
}


int WiFiTest::sendShortResult(){
    if(TestResult::instance()->deviceID != ""){
        if(FTPHandler::instance()->wifiSendFile(TEST_FILE_PREFIX + TestResult::instance()->deviceID + ".SCV", REMOTE_SHORT_TEST_RESULT_DIRECTORY) == OK){
            TestResult::instance()->_testResult[TestCase::WIFI_Send_Data] = true;
            return OK;
        }
    }
    return WIFI_SEND_DATA_ERROR;
}

int WiFiTest::sendLongResult(){
    if(TestResult::instance()->deviceID != ""){
        if(FTPHandler::instance()->wifiSendFile(TEST_FILE_PREFIX + TestResult::instance()->deviceID + ".SCV", REMOTE_LONG_TEST_RESULT_DIRECTORY) == OK){
            TestResult::instance()->_testResult[TestCase::WIFI_Send_Data] = true;
            return OK;
        }
    }
    return WIFI_SEND_DATA_ERROR;
}

int WiFiTest::receiveData(){
    if(FTPHandler::instance()->wifiReceiveFile(REMOTE_WIFI_TEST_FILE_1, NETWORK_TEST_LOCATION) == OK){
        if(FTPHandler::instance()->wifiReceiveFile(REMOTE_WIFI_TEST_FILE_2, NETWORK_TEST_LOCATION) == OK){
            QString wifiTestRet = HardwareController::instance()->executeCommand("cat " NETWORK_TEST_LOCATION "/" LOCAL_WIFI_TEST_FILE).c_str();
            if(wifiTestRet == "OK"){
                TestResult::instance()->_testResult[TestCase::WIFI_Receive_Data] = true;
                HardwareController::instance()->executeCommand("rm " NETWORK_TEST_LOCATION "/" LOCAL_WIFI_TEST_FILE).c_str();
                return OK;
            }
        }
    }
    return WIFI_RECEIVE_DATA_ERROR;
}
