#include "gsm4gtest.h"

GSM4GTest::GSM4GTest()
{
}


int GSM4GTest::initialize(){
    testStart = false;
    APN = GSM_4G_APN;
    username = GSM_4G_USERNAME;
    password = GSM_4G_PASSWORD;
    PIN = GSM_4G_PIN;
    connectionStatus = "";
    IP = "";
    disconnect();
    setConfiguration();
}

void GSM4GTest::run(){
    while(true){
        if(testStart){
            int ethernetRet = EthernetTest::instance()->getStatus();
            int wifiRet = WiFiTest::instance()->getStatus();
            int gsm4gRet = GSM4GTest::instance()->getStatus();

            if(ethernetRet == OK){
                EthernetTest::instance()->disconnect();
            }
            if(wifiRet == OK){
                WiFiTest::instance()->disconnect();
            }
            if(gsm4gRet != OK){
                GSM4GTest::instance()->connect();
            }


            gsm4gRet = GSM4GTest::instance()->checkConnectionTerminal();
            if(gsm4gRet == OK)
                connectionStatus = "Connected";
            if(gsm4gRet == GSM_4G_DOES_NOT_CONNECT)
                connectionStatus = "Disconnected";
            if(gsm4gRet == GSM_4G_DOES_UNAVAILABLE)
                connectionStatus = "Unavailable";
            if(gsm4gRet == GSM_4G_DOES_UNMANAGED)
                connectionStatus = "Unmanaged";
            if(gsm4gRet == GSM_4G_DOES_NOT_FOUND)
                connectionStatus = "HardwareError";


            IP = getIP();
            IMEI = getIMEI();

            sendShortResult();
            receiveData();

            testStart = false;
        }
    }
}

int GSM4GTest::getStatus(){
    QString GSM4GStatus = HardwareController::instance()->executeCommand("nmcli d | awk '/gsm/ {print $3}'").c_str();

    GSM4GStatus.remove(GSM4GStatus.size() - 1, 1);

    if(GSM4GStatus == "connected"){
        return OK;
    }
    if(GSM4GStatus == "disconnected"){
        return WIFI_DOES_NOT_CONNECT;
    }
    if(GSM4GStatus == "unavailable"){
        return GSM_4G_DOES_UNAVAILABLE;
    }
    if(GSM4GStatus == "unmanaged"){
        return GSM_4G_DOES_UNMANAGED;
    }
    return WIFI_DOES_NOT_FOUND;
}


int GSM4GTest::checkConnectionTerminal(){
    QString GSM4GStatus = HardwareController::instance()->executeCommand("nmcli d | awk '/ttyUSB/ {print $3}'").c_str();

    GSM4GStatus.remove(GSM4GStatus.size() - 1, 1);

    if(GSM4GStatus == "connected"){
        TestResult::instance()->_testResult[TestCase::GSM4G_Connection_Status] = true;
        return OK;
    }
    if(GSM4GStatus == "disconnected"){
        TestResult::instance()->_testResult[TestCase::GSM4G_Connection_Status] = false;
        return GSM_4G_DOES_NOT_CONNECT;
    }
    if(GSM4GStatus == "unavailable"){
        TestResult::instance()->_testResult[TestCase::GSM4G_Connection_Status] = false;
        return GSM_4G_DOES_UNAVAILABLE;
    }
    if(GSM4GStatus == "unmanaged"){
        TestResult::instance()->_testResult[TestCase::GSM4G_Connection_Status] = false;
        return GSM_4G_DOES_UNMANAGED;
    }
    TestResult::instance()->_testResult[TestCase::GSM4G_Connection_Status] = false;
    return GSM_4G_DOES_NOT_FOUND;
}

QString GSM4GTest::getIP(){
    char gsm4GGetIPCmd [2048];

    QString GSM4GPort = HardwareController::instance()->executeCommand("nmcli d | awk '/ttyUSB/ {print $1}'").c_str();
    GSM4GPort.remove(GSM4GPort.size() - 1, 1);


    sprintf(gsm4GGetIPCmd, "nmcli -p device show %s | awk '/IP4.ADDRESS/ {print $2}'", GSM4GPort.toStdString().data());
    QString gsm4GIP = HardwareController::instance()->executeCommand(gsm4GGetIPCmd).c_str();


    if(gsm4GIP.size() < 4){
        TestResult::instance()->_testResult[TestCase::GSM4G_Get_IP] = false;
        return "";
    }

    gsm4GIP.remove(gsm4GIP.size() - 4, 4);
    TestResult::instance()->_testResult[TestCase::GSM4G_Get_IP] = true;
    return gsm4GIP;
}

QString GSM4GTest::getIMEI(){
    QString gsm4GIMEI = HardwareController::instance()->executeCommand("mmcli -m 0 | awk '/imei/  {print $4}'").c_str();

    if(gsm4GIMEI.size() < 17){
        TestResult::instance()->_testResult[TestCase::GSM4G_Get_IMEI] = false;
        return "";
    }

    gsm4GIMEI.remove(gsm4GIMEI.size() - 2, 2);
    gsm4GIMEI.remove(0, 1);


    TestResult::instance()->_testResult[TestCase::GSM4G_Get_IMEI] = true;
    return gsm4GIMEI;
}

int GSM4GTest::setConfiguration(){

    std::string gsm4GAPNCmd = "nmcli connection edit type gsm con-name \"GPRS\" <<! \nset gsm.apn " + APN + "\n";
    gsm4GAPNCmd += "\nset gsm.username " + username + "\n";
    gsm4GAPNCmd += "\nset gsm.password " + password + "\n";
    gsm4GAPNCmd += "\nset gsm.pin " + PIN + "\n";
    gsm4GAPNCmd += "\nsave\nyes\nquit\n!\n";

    HardwareController::instance()->executeCommand("rm /etc/NetworkManager/system-connections/GPRS*");
    HardwareController::instance()->executeCommand(gsm4GAPNCmd).c_str();

    return OK;

}

int GSM4GTest::connect(){
    char gsm4GConnectCmd [2048];

    QString GSM4GPort = HardwareController::instance()->executeCommand("nmcli d | awk '/ttyUSB/ {print $1}'").c_str();
    GSM4GPort.remove(GSM4GPort.size() - 1, 1);

    sprintf(gsm4GConnectCmd, "nmcli device connect %s",
            GSM4GPort.toStdString().data());

    int retGsm4GConnect= system(gsm4GConnectCmd);
    if(retGsm4GConnect == 0){
        return OK;
    }
    else{
        return GSM_4G_CONNECT_ERROR;
    }
}

int GSM4GTest::disconnect(){
    char gsm4GDisconnectCmd [2048];

    QString GSM4GPort = HardwareController::instance()->executeCommand("nmcli d | awk '/ttyUSB/ {print $1}'").c_str();
    GSM4GPort.remove(GSM4GPort.size() - 1, 1);

    sprintf(gsm4GDisconnectCmd, "nmcli device disconnect %s",
            GSM4GPort.toStdString().data());

    int retGsm4GDisconnect= system(gsm4GDisconnectCmd);
    if(retGsm4GDisconnect == 0){
        return OK;
    }
    else{
        return GSM_4G_DISCONNECT_ERROR;
    }

    return OK;
}

int GSM4GTest::sendShortResult(){
    if(TestResult::instance()->deviceID != ""){
        if(FTPHandler::instance()->gsm4GSendFile(TEST_FILE_PREFIX + TestResult::instance()->deviceID + ".SCV", REMOTE_SHORT_TEST_RESULT_DIRECTORY) == OK){
            TestResult::instance()->_testResult[TestCase::GSM4G_Send_Data] = true;
            return OK;
        }
    }
    return GSM_4G_SEND_DATA_ERROR;
}

int GSM4GTest::sendLongResult(){
    if(TestResult::instance()->deviceID != ""){
        if(FTPHandler::instance()->gsm4GSendFile(TEST_FILE_PREFIX + TestResult::instance()->deviceID + ".SCV", REMOTE_LONG_TEST_RESULT_DIRECTORY) == OK){
            TestResult::instance()->_testResult[TestCase::GSM4G_Send_Data] = true;
            return OK;
        }
    }
    return GSM_4G_SEND_DATA_ERROR;
}

int GSM4GTest::receiveData(){
    if(FTPHandler::instance()->gsm4GReceiveFile(REMOTE_GSM_4G_TEST_FILE_1, NETWORK_TEST_LOCATION) == OK){
        if(FTPHandler::instance()->gsm4GReceiveFile(REMOTE_GSM_4G_TEST_FILE_2, NETWORK_TEST_LOCATION) == OK){
            QString gsm4GRet = HardwareController::instance()->executeCommand("cat " NETWORK_TEST_LOCATION "/" LOCAL_GSM_4G_TEST_FILE).c_str();
            if(gsm4GRet == "OK"){
                TestResult::instance()->_testResult[TestCase::GSM4G_Receive_Data] = true;
                HardwareController::instance()->executeCommand("rm " NETWORK_TEST_LOCATION "/" LOCAL_GSM_4G_TEST_FILE).c_str();
                return OK;
            }
        }
    }
    return GSM_4G_RECEIVE_DATA_ERROR;
}
