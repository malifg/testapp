#include "testresult.h"

TestResult::TestResult()
{
    _testResult[TestCase::GPS_Accuracy] = false;
    _testResult[TestCase::GPS_NumberOfSat] = false;
    _testResult[TestCase::GPS_FixStatus] = false;
    _testResult[TestCase::GPS_TTFF] = false;

    _testResult[TestCase::General_AudioPlay] = false;
    _testResult[TestCase::General_Brightness] = false;
    _testResult[TestCase::General_DO] = false;
    _testResult[TestCase::General_DI] = false;


    _testResult[TestCase::RS232] = false;
    _testResult[TestCase::RS485] = false;


    _testResult[TestCase::WIFI_Connection_Status] = false;
    _testResult[TestCase::WIFI_Get_IP] = false;
    _testResult[TestCase::WIFI_Get_MAC] = false;
    _testResult[TestCase::WIFI_Send_Data] = false;
    _testResult[TestCase::WIFI_Receive_Data] = false;


    _testResult[TestCase::Ethernet_Connection_Status] = false;
    _testResult[TestCase::Ethernet_Get_IP] = false;
    _testResult[TestCase::Ethernet_Get_MAC] = false;
    _testResult[TestCase::Ethernet_Send_Data] = false;
    _testResult[TestCase::Ethernet_Receive_Data] = false;

    _testResult[TestCase::GSM4G_Connection_Status] = false;
    _testResult[TestCase::GSM4G_Get_IP] = false;
    _testResult[TestCase::GSM4G_Get_IMEI] = false;
    _testResult[TestCase::GSM4G_Send_Data] = false;
    _testResult[TestCase::GSM4G_Receive_Data] = false;


    _testResult[TestCase::QR] = false;
    _testResult[TestCase::Touch] = false;
}

void TestResult::reset(){
    _testResult[TestCase::GPS_Accuracy] = false;
    _testResult[TestCase::GPS_NumberOfSat] = false;
    _testResult[TestCase::GPS_FixStatus] = false;
    _testResult[TestCase::GPS_TTFF] = false;

    _testResult[TestCase::General_AudioPlay] = false;
    _testResult[TestCase::General_Brightness] = false;
    _testResult[TestCase::General_DO] = false;
    _testResult[TestCase::General_DI] = false;


    _testResult[TestCase::RS232] = false;
    _testResult[TestCase::RS485] = false;


    _testResult[TestCase::WIFI_Connection_Status] = false;
    _testResult[TestCase::WIFI_Get_IP] = false;
    _testResult[TestCase::WIFI_Get_MAC] = false;
    _testResult[TestCase::WIFI_Send_Data] = false;
    _testResult[TestCase::WIFI_Receive_Data] = false;


    _testResult[TestCase::Ethernet_Connection_Status] = false;
    _testResult[TestCase::Ethernet_Get_IP] = false;
    _testResult[TestCase::Ethernet_Get_MAC] = false;
    _testResult[TestCase::Ethernet_Send_Data] = false;
    _testResult[TestCase::Ethernet_Receive_Data] = false;

    _testResult[TestCase::GSM4G_Connection_Status] = false;
    _testResult[TestCase::GSM4G_Get_IP] = false;
    _testResult[TestCase::GSM4G_Get_IMEI] = false;
    _testResult[TestCase::GSM4G_Send_Data] = false;
    _testResult[TestCase::GSM4G_Receive_Data] = false;


    _testResult[TestCase::QR] = false;
    _testResult[TestCase::Touch] = false;
}
