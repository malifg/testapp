#include "filehandler.h"

FileHandler::FileHandler()
{
}


int FileHandler::saveResult(){
    std::string resultFileName(TEST_FILE_PREFIX);
    std::string savedFileName(TEST_FILE_PREFIX);
    resultFileName += TestResult::instance()->deviceID + ".SCV";
    savedFileName += ".SCV";
    std::ofstream resultFile;
    std::ofstream savedFile;
    resultFile.open(resultFileName.c_str(), std::ios::out);
    savedFile.open(savedFileName.c_str(), std::ios::out);

    std::string test;


    //GPS
    test += "Res_GPS_FixStatus=";
    if(TestResult::instance()->_testResult[TestCase::GPS_FixStatus])
        test += "true\n";
    else
        test += "false\n";

    test += "Res_GPS_Accuracy=";
    if(TestResult::instance()->_testResult[TestCase::GPS_Accuracy])
        test += "true\n";
    else
        test += "false\n";

    test += "Res_GPS_NumberOfSat=";
    if(TestResult::instance()->_testResult[TestCase::GPS_NumberOfSat])
        test += "true\n";
    else
        test += "false\n";

    test += "Res_GPS_TTFF=";
    if(TestResult::instance()->_testResult[TestCase::GPS_TTFF])
        test += "true\n";
    else
        test += "false\n";

    test += "Res_GPS_Data_Ready=";
    if(TestResult::instance()->_testResult[TestCase::GPS_Data_Ready])
        test += "true\n";
    else
        test += "false\n";





    //General
    test += "Res_General_AudioPlay=";
    if(TestResult::instance()->_testResult[TestCase::General_AudioPlay])
        test += "true\n";
    else
        test += "false\n";

    test += "Res_General_Brightness=";
    if(TestResult::instance()->_testResult[TestCase::General_Brightness])
        test += "true\n";
    else
        test += "false\n";

    test += "Res_General_DO=";
    if(TestResult::instance()->_testResult[TestCase::General_DO])
        test += "true\n";
    else
        test += "false\n";

    test += "Res_General_DI=";
    if(TestResult::instance()->_testResult[TestCase::General_DI])
        test += "true\n";
    else
        test += "false\n";


    //RS232
    test += "Res_RS232=";
    if(TestResult::instance()->_testResult[TestCase::RS232])
        test += "true\n";
    else
        test += "false\n";


    //RS485
    test += "Res_RS485=";
    if(TestResult::instance()->_testResult[TestCase::RS485])
        test += "true\n";
    else
        test += "false\n";


    //WIFI
    test += "Res_WIFI_Connection_Status=";
    if(TestResult::instance()->_testResult[TestCase::WIFI_Connection_Status])
        test += "true\n";
    else
        test += "false\n";

    test += "Res_WIFI_Get_IP=";
    if(TestResult::instance()->_testResult[TestCase::WIFI_Get_IP])
        test += "true\n";
    else
        test += "false\n";

    test += "Res_WIFI_Get_MAC=";
    if(TestResult::instance()->_testResult[TestCase::WIFI_Get_MAC])
        test += "true\n";
    else
        test += "false\n";

    test += "Res_WIFI_Send_Data=";
    if(TestResult::instance()->_testResult[TestCase::WIFI_Send_Data])
        test += "true\n";
    else
        test += "false\n";

    test += "Res_WIFI_Receive_Data=";
    if(TestResult::instance()->_testResult[TestCase::WIFI_Receive_Data])
        test += "true\n";
    else
        test += "false\n";



    //Ethernet
    test += "Res_Ethernet_Connection_Status=";
    if(TestResult::instance()->_testResult[TestCase::Ethernet_Connection_Status])
        test += "true\n";
    else
        test += "false\n";

    test += "Res_Ethernet_Get_IP=";
    if(TestResult::instance()->_testResult[TestCase::Ethernet_Get_IP])
        test += "true\n";
    else
        test += "false\n";

    test += "Res_Ethernet_Get_MAC=";
    if(TestResult::instance()->_testResult[TestCase::Ethernet_Get_MAC])
        test += "true\n";
    else
        test += "false\n";

    test += "Res_Ethernet_Send_Data=";
    if(TestResult::instance()->_testResult[TestCase::Ethernet_Send_Data])
        test += "true\n";
    else
        test += "false\n";

    test += "Res_Ethernet_Receive_Data=";
    if(TestResult::instance()->_testResult[TestCase::Ethernet_Receive_Data])
        test += "true\n";
    else
        test += "false\n";



    //4G
    test += "Res_GSM4G_Connection_Status=";
    if(TestResult::instance()->_testResult[TestCase::GSM4G_Connection_Status])
        test += "true\n";
    else
        test += "false\n";

    test += "Res_GSM4G_Get_IP=";
    if(TestResult::instance()->_testResult[TestCase::GSM4G_Get_IP])
        test += "true\n";
    else
        test += "false\n";

    test += "Res_GSM4G_Get_IMEI=";
    if(TestResult::instance()->_testResult[TestCase::GSM4G_Get_IMEI])
        test += "true\n";
    else
        test += "false\n";

    test += "Res_GSM4G_Send_Data=";
    if(TestResult::instance()->_testResult[TestCase::GSM4G_Send_Data])
        test += "true\n";
    else
        test += "false\n";

    test += "Res_GSM4G_Receive_Data=";
    if(TestResult::instance()->_testResult[TestCase::GSM4G_Receive_Data])
        test += "true\n";
    else
        test += "false\n";



    //QR
    test += "Res_QR=";
    if(TestResult::instance()->_testResult[TestCase::QR])
        test += "true\n";
    else
        test += "false\n";


    //Touch
    test += "Res_Touch=";
    if(TestResult::instance()->_testResult[TestCase::Touch])
        test += "true\n";
    else
        test += "false\n";







    //data
    test += "Data_SN=";
    if(TestResult::instance()->_testResult[TestCase::QR])
        test += TestResult::instance()->deviceID + "\n";
    else
        test += "noData\n";


    //Ethernet
    test += "Data_Ethernet_Connection_Status=";
    if(TestResult::instance()->_testResult[TestCase::Ethernet_Connection_Status])
        test += EthernetTest::instance()->connectionStatus.toStdString() + "\n";
    else
        test += "noData\n";

    test += "Data_Ethernet_Get_IP=";
    if(TestResult::instance()->_testResult[TestCase::Ethernet_Get_IP])
        test += EthernetTest::instance()->IP.toStdString() + "\n";
    else
        test += "noData\n";

    test += "Data_Ethernet_Get_MAC=";
    if(TestResult::instance()->_testResult[TestCase::Ethernet_Get_MAC])
        test += EthernetTest::instance()->MAC.toStdString() + "\n";
    else
        test += "noData\n";


    //WiFi
    test += "Data_WIFI_Connection_Status=";
    if(TestResult::instance()->_testResult[TestCase::WIFI_Connection_Status])
        test += WiFiTest::instance()->connectionStatus.toStdString() + "\n";
    else
        test += "noData\n";

    test += "Data_WIFI_Get_IP=";
    if(TestResult::instance()->_testResult[TestCase::WIFI_Get_IP])
        test += WiFiTest::instance()->IP.toStdString() + "\n";
    else
        test += "noData\n";

    test += "Data_WIFI_Get_MAC=";
    if(TestResult::instance()->_testResult[TestCase::WIFI_Get_MAC])
        test += WiFiTest::instance()->MAC.toStdString() + "\n";
    else
        test += "noData\n";


    //4G
    test += "Data_GSM4G_Connection_Status=";
    if(TestResult::instance()->_testResult[TestCase::GSM4G_Connection_Status])
        test += GSM4GTest::instance()->connectionStatus.toStdString() + "\n";
    else
        test += "noData\n";

    test += "Data_GSM4G_Get_IP=";
    if(TestResult::instance()->_testResult[TestCase::GSM4G_Get_IP])
        test += GSM4GTest::instance()->IP.toStdString() + "\n";
    else
        test += "noData\n";

    test += "Data_GSM4G_Get_IMEI=";
    if(TestResult::instance()->_testResult[TestCase::GSM4G_Get_IMEI])
        test += GSM4GTest::instance()->IMEI.toStdString() + "\n";
    else
        test += "noData\n";


    //GPS
    test += "Data_GPS_FixStatus=";
    if(TestResult::instance()->_testResult[TestCase::GPS_FixStatus])
        test += GPSTest::instance()->fixSatus.toStdString() + "\n";
    else
        test += "noData\n";

    test += "Data_GPS_Accuracy=";
    if(TestResult::instance()->_testResult[TestCase::GPS_Accuracy])
        test += GPSTest::instance()->accuracy.toStdString() + "\n";
    else
        test += "noData\n";

    test += "Data_GPS_NumberOfSat=";
    if(TestResult::instance()->_testResult[TestCase::GPS_NumberOfSat])
        test += GPSTest::instance()->numberOfSat.toStdString() + "\n";
    else
        test += "noData\n";

    test += "Data_GPS_TTFF=";
    if(TestResult::instance()->_testResult[TestCase::GPS_TTFF])
        test += QString::number(GPSTest::instance()->TTFF).toStdString() + "\n";
    else
        test += "noData\n";

    test += "Data_GPS_Latitude=";
    if(TestResult::instance()->_testResult[TestCase::GPS_Data_Ready])
        test += GPSTest::instance()->latitude.toStdString() + "\n";
    else
        test += "noData\n";

    test += "Data_GPS_Longitude=";
    if(TestResult::instance()->_testResult[TestCase::GPS_Data_Ready])
        test += GPSTest::instance()->longitude.toStdString() + "\n";
    else
        test += "noData\n";

    test += "Data_GPS_Altitude=";
    if(TestResult::instance()->_testResult[TestCase::GPS_Data_Ready])
        test += GPSTest::instance()->altitude.toStdString() + "\n";
    else
        test += "noData\n";

    test += "Data_GPS_Current_Time=";
    if(TestResult::instance()->_testResult[TestCase::GPS_Data_Ready])
        test += GPSTest::instance()->currentTime.toStdString() + "\n";
    else
        test += "noData\n";

    //Stability
    test += "Data_Ethernet_Stability=";
    test += QString::number(NetworkStabilityTest::instance()->ethernetNumberOfSuccess).toStdString() + "\n";

    test += "Data_WiFi_Stability=";
    test += QString::number(NetworkStabilityTest::instance()->wifiNumberOfSuccess).toStdString() + "\n";

    test += "Data_GSM4G_Stability=";
    test += QString::number(NetworkStabilityTest::instance()->gsm4GNumberOfSuccess).toStdString() + "\n";

    test += "Data_NumberOfTest_Stability=";
    test += QString::number(NetworkStabilityTest::instance()->numberOfTests).toStdString() + "\n";


    if(savedFile.is_open()) {
        savedFile << test;
        savedFile.close();
    }
    else{
        return -1;
    }


    if(resultFile.is_open()) {
        resultFile << test;
        resultFile.close();
    }
    else{
        return -1;
    }
    return 0;
}


int FileHandler::loadResult(){

    std::string resultFileName(TEST_FILE_PREFIX);
    resultFileName += TestResult::instance()->deviceID + ".SCV";

    std::ifstream resultFile;
    resultFile.open(resultFileName.c_str(), std::ios::in);

    if(!resultFile.is_open()) {
        return -1;
    }
    else {
        std::string line;
        while (std::getline(resultFile, line)) {
            if(line.find("#") != std::string::npos) {
                continue;
            }
            std::vector<std::string> str_array;
            str_array =  Utils::instance()->split(line,'=',str_array);
            if(str_array.size() == 0) {
                continue;
            }
            std::string value;
            for(std::vector<std::string>::iterator itr = str_array.end()-1 ; itr != str_array.begin(); itr--) {
                if((*itr).size() > 0) {
                    value = (*itr);
                    break;
                }
            }

            //GPS
            if(line.find("Res_GPS_FixStatus") != std::string::npos) {
                if(value == "true"){
                    TestResult::instance()->_testResult[TestCase::GPS_FixStatus] = true;
                }
                else if(value == "false"){
                    TestResult::instance()->_testResult[TestCase::GPS_FixStatus] = false;
                }
                else{
                    return LOAD_FILE_ERROR;
                }
            }

            if(line.find("Res_GPS_Accuracy") != std::string::npos) {
                if(value == "true"){
                    TestResult::instance()->_testResult[TestCase::GPS_Accuracy] = true;
                }
                else if(value == "false"){
                    TestResult::instance()->_testResult[TestCase::GPS_Accuracy] = false;
                }
                else{
                    return LOAD_FILE_ERROR;
                }
            }

            if(line.find("Res_GPS_NumberOfSat") != std::string::npos) {
                if(value == "true"){
                    TestResult::instance()->_testResult[TestCase::GPS_NumberOfSat] = true;
                }
                else if(value == "false"){
                    TestResult::instance()->_testResult[TestCase::GPS_NumberOfSat] = false;
                }
                else{
                    return LOAD_FILE_ERROR;
                }
            }

            if(line.find("Res_GPS_TTFF") != std::string::npos) {
                if(value == "true"){
                    TestResult::instance()->_testResult[TestCase::GPS_TTFF] = true;
                }
                else if(value == "false"){
                    TestResult::instance()->_testResult[TestCase::GPS_TTFF] = false;
                }
                else{
                    return LOAD_FILE_ERROR;
                }
            }

            if(line.find("Res_GPS_Data_Ready") != std::string::npos) {
                if(value == "true"){
                    TestResult::instance()->_testResult[TestCase::GPS_Data_Ready] = true;
                }
                else if(value == "false"){
                    TestResult::instance()->_testResult[TestCase::GPS_Data_Ready] = false;
                }
                else{
                    return LOAD_FILE_ERROR;
                }
            }




            //General
            if(line.find("Res_General_AudioPlay") != std::string::npos) {
                if(value == "true"){
                    TestResult::instance()->_testResult[TestCase::General_AudioPlay] = true;
                }
                else if(value == "false"){
                    TestResult::instance()->_testResult[TestCase::General_AudioPlay] = false;
                }
                else{
                    return LOAD_FILE_ERROR;
                }
            }

            if(line.find("Res_General_Brightness") != std::string::npos) {
                if(value == "true"){
                    TestResult::instance()->_testResult[TestCase::General_Brightness] = true;
                }
                else if(value == "false"){
                    TestResult::instance()->_testResult[TestCase::General_Brightness] = false;
                }
                else{
                    return LOAD_FILE_ERROR;
                }
            }

            if(line.find("Res_General_DO") != std::string::npos) {
                if(value == "true"){
                    TestResult::instance()->_testResult[TestCase::General_DO] = true;
                }
                else if(value == "false"){
                    TestResult::instance()->_testResult[TestCase::General_DO] = false;
                }
                else{
                    return LOAD_FILE_ERROR;
                }
            }

            if(line.find("Res_General_DI") != std::string::npos) {
                if(value == "true"){
                    TestResult::instance()->_testResult[TestCase::General_DI] = true;
                }
                else if(value == "false"){
                    TestResult::instance()->_testResult[TestCase::General_DI] = false;
                }
                else{
                    return LOAD_FILE_ERROR;
                }
            }


            //RS232
            if(line.find("Res_RS232") != std::string::npos) {
                if(value == "true"){
                    TestResult::instance()->_testResult[TestCase::RS232] = true;
                }
                else if(value == "false"){
                    TestResult::instance()->_testResult[TestCase::RS232] = false;
                }
                else{
                    return LOAD_FILE_ERROR;
                }
            }


            //RS232
            if(line.find("Res_RS485") != std::string::npos) {
                if(value == "true"){
                    TestResult::instance()->_testResult[TestCase::RS485] = true;
                }
                else if(value == "false"){
                    TestResult::instance()->_testResult[TestCase::RS485] = false;
                }
                else{
                    return LOAD_FILE_ERROR;
                }
            }



            //WIFI
            if(line.find("Res_WIFI_Connection_Status") != std::string::npos) {
                if(value == "true"){
                    TestResult::instance()->_testResult[TestCase::WIFI_Connection_Status] = true;
                }
                else if(value == "false"){
                    TestResult::instance()->_testResult[TestCase::WIFI_Connection_Status] = false;
                }
                else{
                    return LOAD_FILE_ERROR;
                }
            }

            if(line.find("Res_WIFI_Get_IP") != std::string::npos) {
                if(value == "true"){
                    TestResult::instance()->_testResult[TestCase::WIFI_Get_IP] = true;
                }
                else if(value == "false"){
                    TestResult::instance()->_testResult[TestCase::WIFI_Get_IP] = false;
                }
                else{
                    return LOAD_FILE_ERROR;
                }
            }

            if(line.find("Res_WIFI_Get_MAC") != std::string::npos) {
                if(value == "true"){
                    TestResult::instance()->_testResult[TestCase::WIFI_Get_MAC] = true;
                }
                else if(value == "false"){
                    TestResult::instance()->_testResult[TestCase::WIFI_Get_MAC] = false;
                }
                else{
                    return LOAD_FILE_ERROR;
                }
            }

            if(line.find("Res_WIFI_Send_Data") != std::string::npos) {
                if(value == "true"){
                    TestResult::instance()->_testResult[TestCase::WIFI_Send_Data] = true;
                }
                else if(value == "false"){
                    TestResult::instance()->_testResult[TestCase::WIFI_Send_Data] = false;
                }
                else{
                    return LOAD_FILE_ERROR;
                }
            }

            if(line.find("Res_WIFI_Receive_Data") != std::string::npos) {
                if(value == "true"){
                    TestResult::instance()->_testResult[TestCase::WIFI_Receive_Data] = true;
                }
                else if(value == "false"){
                    TestResult::instance()->_testResult[TestCase::WIFI_Receive_Data] = false;
                }
                else{
                    return LOAD_FILE_ERROR;
                }
            }






            //Ethernet
            if(line.find("Res_Ethernet_Connection_Status") != std::string::npos) {
                if(value == "true"){
                    TestResult::instance()->_testResult[TestCase::Ethernet_Connection_Status] = true;
                }
                else if(value == "false"){
                    TestResult::instance()->_testResult[TestCase::Ethernet_Connection_Status] = false;
                }
                else{
                    return LOAD_FILE_ERROR;
                }
            }

            if(line.find("Res_Ethernet_Get_IP") != std::string::npos) {
                if(value == "true"){
                    TestResult::instance()->_testResult[TestCase::Ethernet_Get_IP] = true;
                }
                else if(value == "false"){
                    TestResult::instance()->_testResult[TestCase::Ethernet_Get_IP] = false;
                }
                else{
                    return LOAD_FILE_ERROR;
                }
            }

            if(line.find("Res_Ethernet_Get_MAC") != std::string::npos) {
                if(value == "true"){
                    TestResult::instance()->_testResult[TestCase::Ethernet_Get_MAC] = true;
                }
                else if(value == "false"){
                    TestResult::instance()->_testResult[TestCase::Ethernet_Get_MAC] = false;
                }
                else{
                    return LOAD_FILE_ERROR;
                }
            }

            if(line.find("Res_Ethernet_Send_Data") != std::string::npos) {
                if(value == "true"){
                    TestResult::instance()->_testResult[TestCase::Ethernet_Send_Data] = true;
                }
                else if(value == "false"){
                    TestResult::instance()->_testResult[TestCase::Ethernet_Send_Data] = false;
                }
                else{
                    return LOAD_FILE_ERROR;
                }
            }

            if(line.find("Res_Ethernet_Receive_Data") != std::string::npos) {
                if(value == "true"){
                    TestResult::instance()->_testResult[TestCase::Ethernet_Receive_Data] = true;
                }
                else if(value == "false"){
                    TestResult::instance()->_testResult[TestCase::Ethernet_Receive_Data] = false;
                }
                else{
                    return LOAD_FILE_ERROR;
                }
            }






            //4G
            if(line.find("Res_GSM4G_Connection_Status") != std::string::npos) {
                if(value == "true"){
                    TestResult::instance()->_testResult[TestCase::GSM4G_Connection_Status] = true;
                }
                else if(value == "false"){
                    TestResult::instance()->_testResult[TestCase::GSM4G_Connection_Status] = false;
                }
                else{
                    return LOAD_FILE_ERROR;
                }
            }

            if(line.find("Res_GSM4G_Get_IP") != std::string::npos) {
                if(value == "true"){
                    TestResult::instance()->_testResult[TestCase::GSM4G_Get_IP] = true;
                }
                else if(value == "false"){
                    TestResult::instance()->_testResult[TestCase::GSM4G_Get_IP] = false;
                }
                else{
                    return LOAD_FILE_ERROR;
                }
            }

            if(line.find("Res_GSM4G_Get_IMEI") != std::string::npos) {
                if(value == "true"){
                    TestResult::instance()->_testResult[TestCase::GSM4G_Get_IMEI] = true;
                }
                else if(value == "false"){
                    TestResult::instance()->_testResult[TestCase::GSM4G_Get_IMEI] = false;
                }
                else{
                    return LOAD_FILE_ERROR;
                }
            }

            if(line.find("Res_GSM4G_Send_Data") != std::string::npos) {
                if(value == "true"){
                    TestResult::instance()->_testResult[TestCase::GSM4G_Send_Data] = true;
                }
                else if(value == "false"){
                    TestResult::instance()->_testResult[TestCase::GSM4G_Send_Data] = false;
                }
                else{
                    return LOAD_FILE_ERROR;
                }
            }

            if(line.find("Res_GSM4G_Receive_Data") != std::string::npos) {
                if(value == "true"){
                    TestResult::instance()->_testResult[TestCase::GSM4G_Receive_Data] = true;
                }
                else if(value == "false"){
                    TestResult::instance()->_testResult[TestCase::GSM4G_Receive_Data] = false;
                }
                else{
                    return LOAD_FILE_ERROR;
                }
            }






            //QR
            if(line.find("Res_QR") != std::string::npos) {
                if(value == "true"){
                    TestResult::instance()->_testResult[TestCase::QR] = true;
                }
                else if(value == "false"){
                    TestResult::instance()->_testResult[TestCase::QR] = false;
                }
                else{
                    return LOAD_FILE_ERROR;
                }
            }




            //Touch
            if(line.find("Res_Touch") != std::string::npos) {
                if(value == "true"){
                    TestResult::instance()->_testResult[TestCase::Touch] = true;
                }
                else if(value == "false"){
                    TestResult::instance()->_testResult[TestCase::Touch] = false;
                }
                else{
                    return LOAD_FILE_ERROR;
                }
            }
























            //Data
            if(line.find("Data_SN") != std::string::npos) {
                if(value != "" && value != "noData"){
                    TestResult::instance()->deviceID = value;
                }
                else{
                    TestResult::instance()->_testResult[TestCase::QR] = false;
                }
            }

            //ETH
            if(line.find("Data_Ethernet_Connection_Status") != std::string::npos) {
                if(value != "" && value != "noData"){
                    EthernetTest::instance()->connectionStatus = QString::fromStdString(value);
                }
                else{
                    TestResult::instance()->_testResult[TestCase::Ethernet_Connection_Status] = false;
                }
            }

            if(line.find("Data_Ethernet_Get_IP") != std::string::npos) {
                if(value != "" && value != "noData"){
                    EthernetTest::instance()->IP =  QString::fromStdString(value);
                }
                else{
                    TestResult::instance()->_testResult[TestCase::Ethernet_Get_IP] = false;
                }
            }

            if(line.find("Data_Ethernet_Get_MAC") != std::string::npos) {
                if(value != "" && value != "noData"){
                    EthernetTest::instance()->MAC =  QString::fromStdString(value);
                }
                else{
                    TestResult::instance()->_testResult[TestCase::Ethernet_Get_MAC] = false;
                }
            }

            //WIFI
            if(line.find("Data_WIFI_Connection_Status") != std::string::npos) {
                if(value != "" && value != "noData"){
                    WiFiTest::instance()->connectionStatus = QString::fromStdString(value);
                }
                else{
                    TestResult::instance()->_testResult[TestCase::WIFI_Connection_Status] = false;
                }
            }

            if(line.find("Data_WIFI_Get_IP") != std::string::npos) {
                if(value != "" && value != "noData"){
                    WiFiTest::instance()->IP = QString::fromStdString(value);
                }
                else{
                    TestResult::instance()->_testResult[TestCase::WIFI_Get_IP] = false;
                }
            }

            if(line.find("Data_WIFI_Get_MAC") != std::string::npos) {
                if(value != "" && value != "noData"){
                    WiFiTest::instance()->MAC = QString::fromStdString(value);
                }
                else{
                    TestResult::instance()->_testResult[TestCase::WIFI_Get_MAC] = false;
                }
            }

            //4G
            if(line.find("Data_GSM4G_Connection_Status") != std::string::npos) {
                if(value != "" && value != "noData"){
                    GSM4GTest::instance()->connectionStatus = QString::fromStdString(value);
                }
                else{
                    TestResult::instance()->_testResult[TestCase::GSM4G_Connection_Status] = false;
                }
            }

            if(line.find("Data_GSM4G_Get_IP") != std::string::npos) {
                if(value != "" && value != "noData"){
                    GSM4GTest::instance()->IP = QString::fromStdString(value);
                }
                else{
                    TestResult::instance()->_testResult[TestCase::GSM4G_Get_IP] = false;
                }
            }

            if(line.find("Data_GSM4G_Get_IMEI") != std::string::npos) {
                if(value != "" && value != "noData"){
                    GSM4GTest::instance()->IMEI = QString::fromStdString(value);
                }
                else{
                    TestResult::instance()->_testResult[TestCase::GSM4G_Get_IMEI] = false;
                }
            }

            //GPS
            if(line.find("Data_GPS_FixStatus") != std::string::npos) {
                if(value != "" && value != "noData"){
                    GPSTest::instance()->fixSatus = QString::fromStdString(value);
                }
                else{
                    TestResult::instance()->_testResult[TestCase::GPS_FixStatus] = false;
                }
            }

            if(line.find("Data_GPS_Accuracy") != std::string::npos) {
                if(value != "" && value != "noData"){
                    GPSTest::instance()->accuracy = QString::fromStdString(value);
                }
                else{
                    TestResult::instance()->_testResult[TestCase::GPS_Accuracy] = false;
                }
            }

            if(line.find("Data_GPS_NumberOfSat") != std::string::npos) {
                if(value != "" && value != "noData"){
                    GPSTest::instance()->numberOfSat = QString::fromStdString(value);
                }
                else{
                    TestResult::instance()->_testResult[TestCase::GPS_NumberOfSat] = false;
                }
            }

            if(line.find("Data_GPS_TTFF") != std::string::npos) {
                if(value != "" && value != "noData"){
                    GPSTest::instance()->TTFF = Utils::instance()->stoi(value);
                }
                else{
                    TestResult::instance()->_testResult[TestCase::GPS_TTFF] = false;
                }
            }

            if(line.find("Data_GPS_Latitude") != std::string::npos) {
                if(value != "" && value != "noData"){
                    GPSTest::instance()->latitude = QString::fromStdString(value);
                }
                else{
                    TestResult::instance()->_testResult[TestCase::GPS_Data_Ready] = false;
                }
            }

            if(line.find("Data_GPS_Longitude") != std::string::npos) {
                if(value != "" && value != "noData"){
                    GPSTest::instance()->longitude = QString::fromStdString(value);
                }
                else{
                    TestResult::instance()->_testResult[TestCase::GPS_Data_Ready] = false;
                }
            }

            if(line.find("Data_GPS_Altitude") != std::string::npos) {
                if(value != "" && value != "noData"){
                    GPSTest::instance()->altitude = QString::fromStdString(value);
                }
                else{
                    TestResult::instance()->_testResult[TestCase::GPS_Data_Ready] = false;
                }
            }

            if(line.find("Data_GPS_Current_Time") != std::string::npos) {
                if(value != "" && value != "noData"){
                    GPSTest::instance()->currentTime = QString::fromStdString(value);
                }
                else{
                    TestResult::instance()->_testResult[TestCase::GPS_Data_Ready] = false;
                }
            }

            //Stability
            if(line.find("Data_Ethernet_Stability") != std::string::npos) {
                if(value != "" && value != "noData"){
                    NetworkStabilityTest::instance()->ethernetNumberOfSuccess = Utils::instance()->stoi(value);
                }
            }

            if(line.find("Data_WiFi_Stability") != std::string::npos) {
                if(value != "" && value != "noData"){
                    NetworkStabilityTest::instance()->wifiNumberOfSuccess = Utils::instance()->stoi(value);
                }
            }

            if(line.find("Data_GSM4G_Stability") != std::string::npos) {
                if(value != "" && value != "noData"){
                    NetworkStabilityTest::instance()->gsm4GNumberOfSuccess = Utils::instance()->stoi(value);
                }
            }

            if(line.find("Data_NumberOfTest_Stability") != std::string::npos) {
                if(value != "" && value != "noData"){
                    NetworkStabilityTest::instance()->numberOfTests = Utils::instance()->stoi(value);
                }
            }






        }
    }
    return OK;

}

