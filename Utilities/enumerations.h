#ifndef ENUMERATIONS_H
#define ENUMERATIONS_H

namespace TestCase
{
    enum
    {
        GPS_FixStatus,
        GPS_Accuracy,
        GPS_NumberOfSat,
        GPS_TTFF,
        GPS_Data_Ready,

        General_AudioPlay,
        General_Brightness,
        General_DO,
        General_DI,

        RS232,

        RS485,

        WIFI_Connection_Status,
        WIFI_Get_IP,
        WIFI_Get_MAC,
        WIFI_Send_Data,
        WIFI_Receive_Data,

        Ethernet_Connection_Status,
        Ethernet_Get_IP,
        Ethernet_Get_MAC,
        Ethernet_Send_Data,
        Ethernet_Receive_Data,

        GSM4G_Connection_Status,
        GSM4G_Get_IP,
        GSM4G_Get_IMEI,
        GSM4G_Send_Data,
        GSM4G_Receive_Data,


        QR,

        Touch,


        TestCount,
    };
}



#endif // ENUMERATIONS_H
