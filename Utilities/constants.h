#ifndef CONSTANTS_H
#define CONSTANTS_H

//Parameters
#define MAX_BUF                                         64
#define GPS_BUS_TRY_COUNT                               100
#define GPS_TIMEOUT                                     300
#define WIFI_SERVER_IP                                  "116.12.175.162"
#define WIFI_SERVER_PORT                                "21"
#define WIFI_FTP_USERNAME                               "SCV500_Test"
#define WIFI_FTP_PASSWORD                               "SCSoft_1234"
#define ETHERNET_SERVER_IP                              "116.12.175.162"
#define ETHERNET_SERVER_PORT                            "21"
#define ETHERNET_FTP_USERNAME                           "SCV500_Test"
#define ETHERNET_FTP_PASSWORD                           "SCSoft_1234"
#define GSM_4G_SERVER_IP                                "116.12.175.162"
#define GSM_4G_SERVER_PORT                              "21"
#define GSM_4G_FTP_USERNAME                             "SCV500_Test"
#define GSM_4G_FTP_PASSWORD                             "SCSoft_1234"
#define GSM_4G_APN                                      "psmtneorm"
#define GSM_4G_USERNAME                                 ""
#define GSM_4G_PASSWORD                                 ""
#define GSM_4G_PIN                                      ""
#define WIFI_SSID                                       "SCSOFT_SCV_TEST"//"Arayeh_Shatel_Wifi"
#define WIFI_PASSWORD                                   "SCSOFT_PASSWORD"//"Arayeh@wifi@1234_"
#define GPS_MAX_ACCURACY                                3
#define GPS_MIN_NUMBER_OF_SAT                           5
#define GPS_MIN_TTFF1                                   60
#define GPS_MIN_TTFF2                                   150


//Ports
#define PORT_GPS                                        "/dev/ttyAMA3"
#define PORT_QR                                         "/dev/ttyAMA4"
#define PORT_RS232                                      "/dev/ttyUSB0"
#define PORT_RS485                                      "/dev/ttyUSB1"
#define GPIO_QR_TRIG_PIN                                63
#define GPIO_DO_PIN                                     62
#define GPIO_DI_PIN                                     75
#define GPIO_GPS_RESET_PIN                              126
#define GPIO_READER_POWER                               95

// APP version
#define APP_VERSION                                     "010000"

//Folders
#define APP_DIRECTORY                                   "/root/SCV_testApp_V2_0_0"
#define LOG_DIR                                         "/root/SCV_testApp_V2_0_0"
#define TEST_FILE_LOCATION                              "/root/SCV_testApp_V2_0_0/Result"
#define TEST_FILE_PREFIX                                "/root/SCV_testApp_V2_0_0/Result/SCSOFT_TEST_RESULT_"
#define NETWORK_TEST_LOCATION                           "/root/SCV_testApp_V2_0_0/NetworkTest"
#define REMOTE_WIFI_TEST_FILE_1                         "/SCV500_WIFI.pdf"
#define REMOTE_ETHERNET_TEST_FILE_1                     "/SCV500_ETH.pdf"
#define REMOTE_GSM_4G_TEST_FILE_1                       "/SCV500_4G.pdf"
#define REMOTE_WIFI_TEST_FILE_2                         "/wifi_test.txt"
#define REMOTE_ETHERNET_TEST_FILE_2                     "/ethernet_test.txt"
#define REMOTE_GSM_4G_TEST_FILE_2                       "/gsm4G_test.txt"
#define LOCAL_WIFI_TEST_FILE                            "wifi_test.txt"
#define LOCAL_ETHERNET_TEST_FILE                        "ethernet_test.txt"
#define LOCAL_GSM_4G_TEST_FILE                          "gsm4G_test.txt"
#define NETWORK_TEST_FILE                               "/root/SCV_testApp_V2_0_0/NetworkTest/SCV500_Guide.pdf"
#define REMOTE_SHORT_TEST_RESULT_DIRECTORY              "/ShortTest"
#define REMOTE_LONG_TEST_RESULT_DIRECTORY               "/LongTest"


//ERRORS
#define OK                                              0
#define PARAMETER_ERROR                                 1
#define PORT_OPEN_ERROR                                 2
#define FTP_WIFI_SEND_ERROR                             3
#define FTP_ETHERNET_SEND_ERROR                         4
#define FTP_GSM_4G_SEND_ERROR                           5
#define FTP_WIFI_RECEIVE_ERROR                          6
#define FTP_ETHERNET_RECEIVE_ERROR                      7
#define FTP_GSM_4G_RECEIVE_ERROR                        8
#define LOAD_FILE_ERROR                                 9



#define GPS_PORT_OPEN_ERROR                             1001
#define GPS_DATA_TYPE_ERROR                             1002
#define GPS_TAG_NOT_FOUND                               1003
#define GPS_NOT_FIXED                                   1004

#define RS232_PORT_OPEN_ERROR                           2001

#define RS485_PORT_OPEN_ERROR                           3001

#define WIFI_DOES_NOT_CONNECT                           4001
#define WIFI_DOES_NOT_FOUND                             4002
#define WIFI_IP_ERROR                                   4003
#define WIFI_SEND_DATA_ERROR                            4004
#define WIFI_RECEIVE_DATA_ERROR                         4005

#define ETHERNET_DOES_NOT_CONNECT                       5001
#define ETHERNET_DOES_NOT_FOUND                         5002
#define ETHERNET_IP_ERROR                               5003
#define ETHERNET_SEND_DATA_ERROR                        5004
#define ETHERNET_RECEIVE_DATA_ERROR                     5005

#define GSM_4G_DOES_NOT_CONNECT                         6001
#define GSM_4G_DOES_NOT_FOUND                           6002
#define GSM_4G_IP_ERROR                                 6003
#define GSM_4G_CONNECT_ERROR                            6004
#define GSM_4G_DISCONNECT_ERROR                         6005
#define GSM_4G_SET_APN_ERROR                            6006
#define GSM_4G_SEND_DATA_ERROR                          6007
#define GSM_4G_RECEIVE_DATA_ERROR                       6008
#define GSM_4G_DOES_UNAVAILABLE                         6009
#define GSM_4G_DOES_UNMANAGED                           6010



#endif // CONSTANTS_H
