#include "ftphandler.h"

FTPHandler::FTPHandler()
{
}

int FTPHandler::initialize(){
    wifiServerAddress = WIFI_SERVER_IP;
    wifiUsername = WIFI_FTP_USERNAME;
    wifiPassword = WIFI_FTP_PASSWORD;
    wifiServerPort = WIFI_SERVER_PORT;


    ethernetServerAddress = ETHERNET_SERVER_IP;
    ethernetUsername = ETHERNET_FTP_USERNAME;
    ethernetPassword = ETHERNET_FTP_PASSWORD;
    ethernetServerPort = ETHERNET_SERVER_PORT;


    gsm4GServerAddress = GSM_4G_SERVER_IP;
    gsm4GUsername = GSM_4G_FTP_USERNAME;
    gsm4GPassword = GSM_4G_FTP_PASSWORD;
    gsm4GServerPort = GSM_4G_SERVER_PORT;
}

int FTPHandler::wifiSendFile(std::string fileLocation, std::string destFolder){
    char wifiFTPSendCmd [2048];

    int filenamePointer = fileLocation.find_last_of('/');
    std::string directory = fileLocation.substr(0, filenamePointer + 1);
    std::string filename = fileLocation.substr(filenamePointer + 1, fileLocation.size() - filenamePointer - 1);

    sprintf(wifiFTPSendCmd, "FTPLOG=%s\nftp -inv <<! > $FTPLOG\npassive n\nopen %s %s\nuser %s %s\ncd %s\nlcd %s\nput %s\nclose\nquit\n!\nFTP_SUCCESS_MSG=\"226\"\nif fgrep \"$FTP_SUCCESS_MSG\" $FTPLOG ;then\nrm $FTPLOG\nelse\nexit -1\nfi\nexit 0\n",
            "/root/ftplogfile",
            wifiServerAddress.data(),
            wifiServerPort.data(),
            wifiUsername.data(),
            wifiPassword.data(),
            destFolder.data(),
            directory.data(),
            filename.data());


    /*With TLS
    sprintf(wifiFTPSendCmd, "FTPLOG=%s\nlftp  \" -c -w -v\nopen %s:%s\nset xfer:timeout 10\nset xfer:log true\nset ftp:ssl-auth TLS\nset ftp:ssl-force true\nset ftp:ssl-protect-list yes\nset ftp:ssl-protect-data yes\nset ftp:ssl-protect-fxp yes\nset ssl:verify-certificate no\nuser %s %s\ncd %s\nlcd %s\nput %s\nbye\n\" >> $FTPLOG\nFTP_SUCCESS_MSG=\"bytes transferred\"\nif fgrep \"$FTP_SUCCESS_MSG\" $FTPLOG ;then\nrm $FTPLOG\nelse\nexit -1\nfi\nrm $FTPLOG\nexit 0\n",
            "/root/ftplogfile",
            wifiServerAddress.data(),
            wifiServerPort.data(),
            wifiUsername.data(),
            wifiPassword.data(),
            destFolder.data(),
            directory.data(),
            filename.data());
    */

    int retWiFiSend = system(wifiFTPSendCmd);
    if(retWiFiSend == 0){
        return OK;
    }
    else{
        return FTP_WIFI_SEND_ERROR;
    }
}

int FTPHandler::ethernetSendFile(std::string fileLocation, std::string destFolder){
    char ethernetFTPSendCmd [2048];

    int filenamePointer = fileLocation.find_last_of('/');
    std::string directory = fileLocation.substr(0, filenamePointer + 1);
    std::string filename = fileLocation.substr(filenamePointer + 1, fileLocation.size() - filenamePointer - 1);

    sprintf(ethernetFTPSendCmd, "FTPLOG=%s\nftp -inv <<! > $FTPLOG\npassive n\nopen %s %s\nuser %s %s\ncd %s\nlcd %s\nput %s\nclose\nquit\n!\nFTP_SUCCESS_MSG=\"226\"\nif fgrep \"$FTP_SUCCESS_MSG\" $FTPLOG ;then\nrm $FTPLOG\nelse\nexit -1\nfi\nexit 0\n",
            "/root/ftplogfile",
            ethernetServerAddress.data(),
            ethernetServerPort.data(),
            ethernetUsername.data(),
            ethernetPassword.data(),
            destFolder.data(),
            directory.data(),
            filename.data());

    /*With TLS
    sprintf(ethernetFTPSendCmd, "FTPLOG=%s\nlftp  \" -c -w -v\nopen %s:%s\nset xfer:timeout 10\nset xfer:log true\nset ftp:ssl-auth TLS\nset ftp:ssl-force true\nset ftp:ssl-protect-list yes\nset ftp:ssl-protect-data yes\nset ftp:ssl-protect-fxp yes\nset ssl:verify-certificate no\nuser %s %s\ncd %s\nlcd %s\nput %s\nbye\n\" >> $FTPLOG\nFTP_SUCCESS_MSG=\"bytes transferred\"\nif fgrep \"$FTP_SUCCESS_MSG\" $FTPLOG ;then\nrm $FTPLOG\nelse\nexit -1\nfi\nrm $FTPLOG\nexit 0\n",
            "/root/ftplogfile",
            ethernetServerAddress.data(),
            ethernetServerPort.data(),
            ethernetUsername.data(),
            ethernetPassword.data(),
            destFolder.data(),
            directory.data(),
            filename.data());
    */


    int retEthernetSend = system(ethernetFTPSendCmd);
    if(retEthernetSend == 0){

        return OK;
    }
    else{
        return FTP_ETHERNET_SEND_ERROR;
    }
}


int FTPHandler::gsm4GSendFile(std::string fileLocation, std::string destFolder){
    char gsm4GFTPSendCmd [2048];

    int filenamePointer = fileLocation.find_last_of('/');
    std::string directory = fileLocation.substr(0, filenamePointer + 1);
    std::string filename = fileLocation.substr(filenamePointer + 1, fileLocation.size() - filenamePointer - 1);


    sprintf(gsm4GFTPSendCmd, "FTPLOG=%s\nftp -inv <<! > $FTPLOG\npassive n\nopen %s %s\nuser %s %s\ncd %s\nlcd %s\nput %s\nclose\nquit\n!\nFTP_SUCCESS_MSG=\"226\"\nif fgrep \"$FTP_SUCCESS_MSG\" $FTPLOG ;then\nrm $FTPLOG\nelse\nexit -1\nfi\nexit 0\n",
            "/root/ftplogfile",
            gsm4GServerAddress.data(),
            gsm4GServerPort.data(),
            gsm4GUsername.data(),
            gsm4GPassword.data(),
            destFolder.data(),
            directory.data(),
            filename.data());


    /*With TLS
    sprintf(gsm4GFTPSendCmd, "FTPLOG=%s\nlftp  \" -c -w -v\nopen %s:%s\nset xfer:timeout 10\nset xfer:log true\nset ftp:ssl-auth TLS\nset ftp:ssl-force true\nset ftp:ssl-protect-list yes\nset ftp:ssl-protect-data yes\nset ftp:ssl-protect-fxp yes\nset ssl:verify-certificate no\nuser %s %s\ncd %s\nlcd %s\nput %s\nbye\n\" >> $FTPLOG\nFTP_SUCCESS_MSG=\"bytes transferred\"\nif fgrep \"$FTP_SUCCESS_MSG\" $FTPLOG ;then\nrm $FTPLOG\nelse\nexit -1\nfi\nrm $FTPLOG\nexit 0\n",
            "/root/ftplogfile",
            gsm4GServerAddress.data(),
            gsm4GServerPort.data(),
            gsm4GUsername.data(),
            gsm4GPassword.data(),
            destFolder.data(),
            directory.data(),
            filename.data());
    */

    int retGsm4GSend = system(gsm4GFTPSendCmd);
    if(retGsm4GSend == 0){
        return OK;
    }
    else{
        return FTP_GSM_4G_SEND_ERROR;
    }
}


int FTPHandler::wifiReceiveFile(std::string fileLocation, std::string destFolder){
    char wifiFTPReceiveCmd [2048];

    sprintf(wifiFTPReceiveCmd, "cd %s && wget ftp://%s:%s@%s:%s%s",
            destFolder.data(),
            wifiUsername.data(),
            wifiPassword.data(),
            wifiServerAddress.data(),
            wifiServerPort.data(),
            fileLocation.data());

    /*With TLS
    sprintf(wifiFTPReceiveCmd, "cd %s && wget --secure-protocol=auto --no-check-certificate ftps://%s:%s@%s:%s%s",
            destFolder.data(),
            wifiUsername.data(),
            wifiPassword.data(),
            wifiServerAddress.data(),
            wifiServerPort.data(),
            fileLocation.data());
    */

    int retWiFiReceive = system(wifiFTPReceiveCmd);
    if(retWiFiReceive == 0){
        return OK;
    }
    else{
        return FTP_WIFI_RECEIVE_ERROR;
    }
}

int FTPHandler::ethernetReceiveFile(std::string fileLocation, std::string destFolder){
    char ethernetFTPReceiveCmd [2048];

    sprintf(ethernetFTPReceiveCmd, "cd %s && wget ftp://%s:%s@%s:%s%s",
            destFolder.data(),
            ethernetUsername.data(),
            ethernetPassword.data(),
            ethernetServerAddress.data(),
            ethernetServerPort.data(),
            fileLocation.data());

    /*With TLS
    sprintf(ethernetFTPReceiveCmd, "cd %s && wget --secure-protocol=auto --no-check-certificate ftps://%s:%s@%s:%s%s",
            destFolder.data(),
            ethernetUsername.data(),
            ethernetPassword.data(),
            ethernetServerAddress.data(),
            ethernetServerPort.data(),
            fileLocation.data());
    */


    int retEthernetReceive = system(ethernetFTPReceiveCmd);
    if(retEthernetReceive == 0){
        return OK;
    }
    else{
        return FTP_ETHERNET_RECEIVE_ERROR;
    }
}

int FTPHandler::gsm4GReceiveFile(std::string fileLocation, std::string destFolder){
    char gsm4GFTPReceiveCmd [2048];

    sprintf(gsm4GFTPReceiveCmd, "cd %s && wget ftp://%s:%s@%s:%s%s",
            destFolder.data(),
            gsm4GUsername.data(),
            gsm4GPassword.data(),
            gsm4GServerAddress.data(),
            gsm4GServerPort.data(),
            fileLocation.data());

    /*With TLS
    sprintf(gsm4GFTPReceiveCmd, "cd %s && wget --secure-protocol=auto --no-check-certificate ftps://%s:%s@%s:%s%s",
            destFolder.data(),
            gsm4GUsername.data(),
            gsm4GPassword.data(),
            gsm4GServerAddress.data(),
            gsm4GServerPort.data(),
            fileLocation.data());

    */

    int retGsm4GReceive = system(gsm4GFTPReceiveCmd);
    if(retGsm4GReceive == 0){
        return OK;
    }
    else{
        return FTP_GSM_4G_RECEIVE_ERROR;
    }
}
