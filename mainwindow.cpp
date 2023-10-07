#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Debug init
    Logger::Init();

    ui->gif_General_loading->setMovie(loadingGif_General);
    ui->gif_GPS_loading->setMovie(loadingGif_GPS);
    ui->gif_Ethernet_loading->setMovie(loadingGif_Ethernet);
    ui->gif_WiFi_loading->setMovie(loadingGif_WiFi);
    ui->gif_4g_loading->setMovie(loadingGif_4G);
    loadingGif_General->start();
    loadingGif_GPS->start();
    loadingGif_Ethernet->start();
    loadingGif_WiFi->start();
    loadingGif_4G->start();

    ui->gif_General_loading->setVisible(false);
    ui->gif_GPS_loading->setVisible(false);
    ui->gif_Ethernet_loading->setVisible(false);
    ui->gif_WiFi_loading->setVisible(false);
    ui->gif_4g_loading->setVisible(false);

    HardwareController::instance()->DO_setValue(GPIO_READER_POWER, true);


    NetworkStabilityTest::instance()->initialize();
    FTPHandler::instance()->initialize();
    RS232Test::instance()->initialize();
    RS485Test::instance()->initialize();
    GPSTest::instance()->initialize();
    QRTest::instance()->initialize();
    EthernetTest::instance()->initialize();
    WiFiTest::instance()->initialize();
    GSM4GTest::instance()->initialize();
    AudioTest::instance()->initialize();


    EthernetTest::instance()->Start();
    WiFiTest::instance()->Start();
    GSM4GTest::instance()->Start();
    GPSTest::instance()->Start();
    QRTest::instance()->Start();
    NetworkStabilityTest::instance()->Start();
    AudioTest::instance()->Start();
    RS232Test::instance()->Start();
    RS485Test::instance()->Start();


    FileHandler::instance()->loadResult();

    updateStatusTimer = new QTimer(this);
    connect(updateStatusTimer, SIGNAL(timeout()), this, SLOT(updateStatus()));
    updateStatusTimer->start(200);

    clockTimer = new QTimer(this);
    connect(clockTimer, SIGNAL(timeout()), this, SLOT(clockUpdate()));
    clockTimer->start(200);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::clockUpdate(){
    dateTime = QDateTime::currentDateTime();
    ui->txt_General_Time->setText(QString::number(dateTime.time().hour()) + ":" + QString::number(dateTime.time().minute()) + ":" + QString::number(dateTime.time().second()));
    ui->txt_General_Date->setText(QString::number(dateTime.date().day()) + "/" + QString::number(dateTime.date().month()) + "/" + QString::number(dateTime.date().year()));
}















void MainWindow::on_btn_General_StartTest_clicked()
{
    AudioTest::instance()->testStart = true;
    QRTest::instance()->testStart = true;
}


void MainWindow::on_slider_brightness_valueChanged(int value)
{
}


void MainWindow::on_btn_General_DOLow_clicked()
{
    HardwareController::instance()->DO_setValue(GPIO_DO_PIN, false);
}


void MainWindow::on_btn_General_DOHigh_clicked()
{
    HardwareController::instance()->DO_setValue(GPIO_DO_PIN, true);
}


void MainWindow::on_btn_General_DIRead_clicked()
{
    int DIRet = HardwareController::instance()->DI_getValue(GPIO_DI_PIN);
    if(DIRet < 0){
        ui->txt_General_DIValue->setText("HardwareError");
    }
    else{
        ui->txt_General_DIValue->setText(QString::number(DIRet));
    }
}


void MainWindow::on_btn_GPS_StartTest_clicked()
{
    GPSTest::instance()->testStart = true;
}


void MainWindow::on_btn_WiFi_StartTest_clicked()
{
    WiFiTest::instance()->testStart = true;
}


void MainWindow::on_btn_Ethernet_StartTest_clicked()
{
    EthernetTest::instance()->testStart = true;
}

void MainWindow::on_btn_4G_StartTest_clicked()
{
    GSM4GTest::instance()->testStart = true;
}

void MainWindow::on_btn_RS232_Start_clicked()
{

    RS232Test::instance()->closePort();
    RS232Test::instance()->initialize();

    usleep(200000);

    RS232Test::instance()->isTester = ui->checkBox_RS232_Tester->isChecked();
    RS232Test::instance()->testStart = true;
}

void MainWindow::on_btn_RS232_Stop_clicked()
{
    RS232Test::instance()->closePort();
    RS232Test::instance()->testStart = false;
}

void MainWindow::on_btn_RS485_Start_clicked()
{
    RS485Test::instance()->closePort();
    RS485Test::instance()->initialize();

    usleep(200000);



    RS485Test::instance()->isTester = ui->checkBox_RS485_Tester->isChecked();
    RS485Test::instance()->testStart = true;
}

void MainWindow::on_btn_RS485_Stop_clicked()
{
    //RS485Test::instance()->_portRS485.close();
    RS485Test::instance()->testStart = false;
}


void MainWindow::on_btn_Touch_1_clicked()
{
    touchButton1 = 1;
    ui->btn_Touch_1->setEnabled(false);
    if(touchButton1 == 1 && touchButton2 == 1 && touchButton3 == 1 && touchButton4 == 1){
        TestResult::instance()->_testResult[TestCase::Touch] = true;
    }
}

void MainWindow::on_btn_Touch_2_clicked()
{
    touchButton2 = 1;
    ui->btn_Touch_2->setEnabled(false);
    if(touchButton1 == 1 && touchButton2 == 1 && touchButton3 == 1 && touchButton4 == 1){
        TestResult::instance()->_testResult[TestCase::Touch] = true;
    }
}

void MainWindow::on_btn_Touch_3_clicked()
{
    touchButton3 = 1;
    ui->btn_Touch_3->setEnabled(false);
    if(touchButton1 == 1 && touchButton2 == 1 && touchButton3 == 1 && touchButton4 == 1){
        TestResult::instance()->_testResult[TestCase::Touch] = true;
    }
}

void MainWindow::on_btn_Touch_4_clicked()
{
    touchButton4 = 1;
    ui->btn_Touch_4->setEnabled(false);
    if(touchButton1 == 1 && touchButton2 == 1 && touchButton3 == 1 && touchButton4 == 1){
        TestResult::instance()->_testResult[TestCase::Touch] = true;
    }
}


void MainWindow::on_btn_Stability_clicked()
{
    if(TestResult::instance()->deviceID != ""){
        NetworkStabilityTest::instance()->testStart = true;
        ui->txt_uploadResult->setText("Test Started.");
        ui->btn_Stability->setEnabled(false);
        ui->btn_Stability_Stop->setEnabled(true);
    }
    else{
        ui->txt_uploadResult->setText("Scan QR first.");
    }
}


void MainWindow::on_btn_Stability_Stop_clicked()
{
    NetworkStabilityTest::instance()->testStart = false;
    ui->txt_uploadResult->setText("Test Stoped.");
    ui->btn_Stability->setEnabled(true);
    ui->btn_Stability_Stop->setEnabled(false);
}



void MainWindow::on_btn_upload_clicked()
{
    ui->btn_upload->setEnabled(false);
    ui->txt_uploadResult->setText("");
    if(TestResult::instance()->deviceID != ""){

        EthernetTest::instance()->connect();
        WiFiTest::instance()->connect();
        GSM4GTest::instance()->connect();


        sleep(5);


        FTPHandler::instance()->wifiSendFile(TEST_FILE_PREFIX + TestResult::instance()->deviceID + ".SCV", REMOTE_SHORT_TEST_RESULT_DIRECTORY);
        FTPHandler::instance()->ethernetSendFile(TEST_FILE_PREFIX + TestResult::instance()->deviceID + ".SCV", REMOTE_SHORT_TEST_RESULT_DIRECTORY);
        FTPHandler::instance()->gsm4GSendFile(TEST_FILE_PREFIX + TestResult::instance()->deviceID + ".SCV", REMOTE_SHORT_TEST_RESULT_DIRECTORY);
        ui->txt_uploadResult->setText("upload completes");
    }
    else{
        ui->txt_uploadResult->setText("Scan QR first.");
    }

    ui->btn_upload->setEnabled(true);
}























void MainWindow::on_pic_General_AudioTest_clicked()
{
    if(TestResult::instance()->_testResult[TestCase::General_AudioPlay] == false){
        ui->pic_General_AudioTest->setIcon(QIcon(":/Images/ok.png"));
        TestResult::instance()->_testResult[TestCase::General_AudioPlay] = true;
    }
    else {
        ui->pic_General_AudioTest->setIcon(QIcon(":/Images/error.png"));
        TestResult::instance()->_testResult[TestCase::General_AudioPlay] = false;
    }
}

void MainWindow::on_pic_General_Brightness_clicked()
{
    if(TestResult::instance()->_testResult[TestCase::General_Brightness] == false){
        ui->pic_General_Brightness->setIcon(QIcon(":/Images/ok.png"));
        TestResult::instance()->_testResult[TestCase::General_Brightness] = true;
    }
    else {
        ui->pic_General_Brightness->setIcon(QIcon(":/Images/error.png"));
        TestResult::instance()->_testResult[TestCase::General_Brightness] = false;
    }
}

void MainWindow::on_pic_General_DO_clicked()
{
    if(TestResult::instance()->_testResult[TestCase::General_DO] == false){
        ui->pic_General_DO->setIcon(QIcon(":/Images/ok.png"));
        TestResult::instance()->_testResult[TestCase::General_DO] = true;
    }
    else {
        ui->pic_General_DO->setIcon(QIcon(":/Images/error.png"));
        TestResult::instance()->_testResult[TestCase::General_DO] = false;
    }
}

void MainWindow::on_pic_General_DI_clicked()
{
    if(TestResult::instance()->_testResult[TestCase::General_DI] == false){
        ui->pic_General_DI->setIcon(QIcon(":/Images/ok.png"));
        TestResult::instance()->_testResult[TestCase::General_DI] = true;
    }
    else {
        ui->pic_General_DI->setIcon(QIcon(":/Images/error.png"));
        TestResult::instance()->_testResult[TestCase::General_DI] = false;
    }
}


void MainWindow::on_btn_reset_clicked()
{
    HardwareController::instance()->executeCommand("rm " TEST_FILE_LOCATION "/*");
    TestResult::instance()->reset();

    EthernetTest::instance()->connectionStatus = "";
    EthernetTest::instance()->IP = "";
    EthernetTest::instance()->MAC = "";

    WiFiTest::instance()->connectionStatus = "";
    WiFiTest::instance()->IP = "";
    WiFiTest::instance()->MAC = "";

    GSM4GTest::instance()->connectionStatus = "";
    GSM4GTest::instance()->IP = "";
    GSM4GTest::instance()->IMEI = "";

    GPSTest::instance()->fixSatus = "";
    GPSTest::instance()->accuracy = "";
    GPSTest::instance()->numberOfSat = "";
    GPSTest::instance()->TTFF = 0;
    GPSTest::instance()->latitude = "";
    GPSTest::instance()->longitude = "";
    GPSTest::instance()->altitude = "";
    GPSTest::instance()->currentTime = "";

    TestResult::instance()->deviceID = "";

    NetworkStabilityTest::instance()->numberOfTests = 0;
    NetworkStabilityTest::instance()->wifiNumberOfSuccess = 0;
    NetworkStabilityTest::instance()->gsm4GNumberOfSuccess = 0;
    NetworkStabilityTest::instance()->ethernetNumberOfSuccess = 0;



    QRTest::instance()->testStart = false;
    EthernetTest::instance()->testStart = false;
    WiFiTest::instance()->testStart = false;
    GSM4GTest::instance()->testStart = false;
    GPSTest::instance()->testStart = false;

}
















void MainWindow::updateStatus()
{
    int numberOfPass = 0;
    //General
    if(TestResult::instance()->_testResult[TestCase::General_AudioPlay] == false){
        ui->pic_General_AudioTest->setIcon(QIcon(":/Images/error.png"));
    }
    else{
        numberOfPass++;
        ui->pic_General_AudioTest->setIcon(QIcon(":/Images/ok.png"));
    }

    if(TestResult::instance()->_testResult[TestCase::General_DI] == false){
        ui->pic_General_DI->setIcon(QIcon(":/Images/error.png"));
    }
    else{
        numberOfPass++;
        ui->pic_General_DI->setIcon(QIcon(":/Images/ok.png"));
    }

    if(TestResult::instance()->_testResult[TestCase::General_DO] == false){
        ui->pic_General_DO->setIcon(QIcon(":/Images/error.png"));
    }
    else{
        numberOfPass++;
        ui->pic_General_DO->setIcon(QIcon(":/Images/ok.png"));
    }

    if(TestResult::instance()->_testResult[TestCase::General_Brightness] == false){
        ui->pic_General_Brightness->setIcon(QIcon(":/Images/error.png"));
    }
    else{
        numberOfPass++;
        ui->pic_General_Brightness->setIcon(QIcon(":/Images/ok.png"));
    }

    if(AudioTest::instance()->testStart && QRTest::instance()->testStart){
        ui->gif_General_loading->setVisible(true);
        ui->btn_General_StartTest->setEnabled(false);
    }
    else{
        ui->gif_General_loading->setVisible(false);
        ui->btn_General_StartTest->setEnabled(true);
    }


    //GPS
    if(TestResult::instance()->_testResult[TestCase::GPS_FixStatus] == false){
        ui->pic_GPS_FixStatus->setIcon(QIcon(":/Images/error.png"));
    }
    else{
        numberOfPass++;
        ui->pic_GPS_FixStatus->setIcon(QIcon(":/Images/ok.png"));
    }

    if(TestResult::instance()->_testResult[TestCase::GPS_Accuracy] == false){
        ui->pic_GPS_Accuracy->setIcon(QIcon(":/Images/error.png"));
    }
    else{
        numberOfPass++;
        ui->pic_GPS_Accuracy->setIcon(QIcon(":/Images/ok.png"));
    }

    if(TestResult::instance()->_testResult[TestCase::GPS_NumberOfSat] == false){
        ui->pic_GPS_NumberOfSat->setIcon(QIcon(":/Images/error.png"));
    }
    else{
        numberOfPass++;
        ui->pic_GPS_NumberOfSat->setIcon(QIcon(":/Images/ok.png"));
    }

    if(TestResult::instance()->_testResult[TestCase::GPS_TTFF] == false){
        ui->pic_GPS_TTFF->setIcon(QIcon(":/Images/error.png"));
    }
    else{
        numberOfPass++;
        ui->pic_GPS_TTFF->setIcon(QIcon(":/Images/ok.png"));
    }

    if(TestResult::instance()->_testResult[TestCase::GPS_Data_Ready] == false){
        ui->pic_GPS_Data->setIcon(QIcon(":/Images/error.png"));
    }
    else{
        numberOfPass++;
        ui->pic_GPS_Data->setIcon(QIcon(":/Images/ok.png"));
    }

    ui->txt_GPS_FixStatus->setText(GPSTest::instance()->fixSatus);
    ui->txt_GPS_Latitude->setText(GPSTest::instance()->latitude);
    ui->txt_GPS_Longitude->setText(GPSTest::instance()->longitude);
    ui->txt_GPS_Altitude->setText(GPSTest::instance()->altitude);
    ui->txt_GPS_NumberOfSat->setText(GPSTest::instance()->numberOfSat);
    ui->txt_GPS_Accuracy->setText(GPSTest::instance()->accuracy);
    ui->txt_GPS_TTFF->setText(QString::number(GPSTest::instance()->TTFF));
    ui->txt_GPS_Time->setText(GPSTest::instance()->currentTime);

    if(GPSTest::instance()->testStart){
        ui->gif_GPS_loading->setVisible(true);
        ui->btn_GPS_StartTest->setEnabled(false);
    }
    else{
        ui->gif_GPS_loading->setVisible(false);
        ui->btn_GPS_StartTest->setEnabled(true);
    }


    //RS232
    if(TestResult::instance()->_testResult[TestCase::RS232] == false){
        ui->pic_RS232->setIcon(QIcon(":/Images/error.png"));
    }
    else{
        numberOfPass++;
        ui->pic_RS232->setIcon(QIcon(":/Images/ok.png"));
    }

    if(RS232Test::instance()->testStart == true)
    {
        ui->btn_RS232_Start->setEnabled(false);
        ui->btn_RS232_Stop->setEnabled(true);
    }
    else
    {
        ui->btn_RS232_Start->setEnabled(true);
        ui->btn_RS232_Stop->setEnabled(false);
    }


    //RS485
    if(TestResult::instance()->_testResult[TestCase::RS485] == false){
        ui->pic_RS485->setIcon(QIcon(":/Images/error.png"));
    }
    else{
        numberOfPass++;
        ui->pic_RS485->setIcon(QIcon(":/Images/ok.png"));
    }

    if(RS485Test::instance()->testStart == true)
    {
        ui->btn_RS485_Start->setEnabled(false);
        ui->btn_RS485_Stop->setEnabled(true);
    }
    else
    {
        ui->btn_RS485_Start->setEnabled(true);
        ui->btn_RS485_Stop->setEnabled(false);
    }


    //QR
    if(TestResult::instance()->_testResult[TestCase::QR] == false){
        ui->pic_QR->setIcon(QIcon(":/Images/error.png"));
    }
    else{
        numberOfPass++;
        ui->pic_QR->setIcon(QIcon(":/Images/ok.png"));
    }
    ui->txt_General_SN->setText(TestResult::instance()->deviceID.c_str());




    //WIFI
    if(TestResult::instance()->_testResult[TestCase::WIFI_Connection_Status] == false){
        ui->pic_WiFi_ConnectionStatus->setIcon(QIcon(":/Images/error.png"));
    }
    else{
        numberOfPass++;
        ui->pic_WiFi_ConnectionStatus->setIcon(QIcon(":/Images/ok.png"));
    }

    if(TestResult::instance()->_testResult[TestCase::WIFI_Get_IP] == false){
        ui->pic_WiFi_IPAddress->setIcon(QIcon(":/Images/error.png"));
    }
    else{
        numberOfPass++;
        ui->pic_WiFi_IPAddress->setIcon(QIcon(":/Images/ok.png"));
    }

    if(TestResult::instance()->_testResult[TestCase::WIFI_Get_MAC] == false){
        ui->pic_WiFi_MACAddress->setIcon(QIcon(":/Images/error.png"));
    }
    else{
        numberOfPass++;
        ui->pic_WiFi_MACAddress->setIcon(QIcon(":/Images/ok.png"));
    }

    if(TestResult::instance()->_testResult[TestCase::WIFI_Send_Data] == false){
        ui->pic_WiFi_SendData->setIcon(QIcon(":/Images/error.png"));
    }
    else{
        numberOfPass++;
        ui->pic_WiFi_SendData->setIcon(QIcon(":/Images/ok.png"));
    }

    if(TestResult::instance()->_testResult[TestCase::WIFI_Receive_Data] == false){
        ui->pic_WiFi_ReceiveData->setIcon(QIcon(":/Images/error.png"));
    }
    else{
        numberOfPass++;
        ui->pic_WiFi_ReceiveData->setIcon(QIcon(":/Images/ok.png"));
    }

    ui->txt_WiFi_ConnectionStatus->setText(WiFiTest::instance()->connectionStatus);
    ui->txt_WiFi_IPAddress->setText(WiFiTest::instance()->IP);
    ui->txt_WiFi_MACAddress->setText(WiFiTest::instance()->MAC);

    if(WiFiTest::instance()->testStart){
        ui->gif_WiFi_loading->setVisible(true);
    }
    else{
        ui->gif_WiFi_loading->setVisible(false);
    }


    //Ethernet
    if(TestResult::instance()->_testResult[TestCase::Ethernet_Connection_Status] == false){
        ui->pic_Ethernet_ConnectionStatus->setIcon(QIcon(":/Images/error.png"));
    }
    else{
        numberOfPass++;
        ui->pic_Ethernet_ConnectionStatus->setIcon(QIcon(":/Images/ok.png"));
    }

    if(TestResult::instance()->_testResult[TestCase::Ethernet_Get_IP] == false){
        ui->pic_Ethernet_IPAddress->setIcon(QIcon(":/Images/error.png"));
    }
    else{
        numberOfPass++;
        ui->pic_Ethernet_IPAddress->setIcon(QIcon(":/Images/ok.png"));
    }

    if(TestResult::instance()->_testResult[TestCase::Ethernet_Get_MAC] == false){
        ui->pic_Ethernet_MACAddress->setIcon(QIcon(":/Images/error.png"));
    }
    else{
        numberOfPass++;
        ui->pic_Ethernet_MACAddress->setIcon(QIcon(":/Images/ok.png"));
    }

    if(TestResult::instance()->_testResult[TestCase::Ethernet_Send_Data] == false){
        ui->pic_Ethernet_SendData->setIcon(QIcon(":/Images/error.png"));
    }
    else{
        numberOfPass++;
        ui->pic_Ethernet_SendData->setIcon(QIcon(":/Images/ok.png"));
    }

    if(TestResult::instance()->_testResult[TestCase::Ethernet_Receive_Data] == false){
        ui->pic_Ethernet_ReceiveData->setIcon(QIcon(":/Images/error.png"));
    }
    else{
        numberOfPass++;
        ui->pic_Ethernet_ReceiveData->setIcon(QIcon(":/Images/ok.png"));
    }

    ui->txt_Ethernet_ConnectionStatus->setText(EthernetTest::instance()->connectionStatus);
    ui->txt_Ethernet_IPAddress->setText(EthernetTest::instance()->IP);
    ui->txt_Ethernet_MACAddress->setText(EthernetTest::instance()->MAC);

    if(EthernetTest::instance()->testStart){
        ui->gif_Ethernet_loading->setVisible(true);
    }
    else{
        ui->gif_Ethernet_loading->setVisible(false);
    }




    //4G
    if(TestResult::instance()->_testResult[TestCase::GSM4G_Connection_Status] == false){
        ui->pic_4G_ConnectionStatus->setIcon(QIcon(":/Images/error.png"));
    }
    else{
        numberOfPass++;
        ui->pic_4G_ConnectionStatus->setIcon(QIcon(":/Images/ok.png"));
    }

    if(TestResult::instance()->_testResult[TestCase::GSM4G_Get_IP] == false){
        ui->pic_4G_IPAddress->setIcon(QIcon(":/Images/error.png"));
    }
    else{
        numberOfPass++;
        ui->pic_4G_IPAddress->setIcon(QIcon(":/Images/ok.png"));
    }

    if(TestResult::instance()->_testResult[TestCase::GSM4G_Get_IMEI] == false){
        ui->pic_4G_IMEI->setIcon(QIcon(":/Images/error.png"));
    }
    else{
        numberOfPass++;
        ui->pic_4G_IMEI->setIcon(QIcon(":/Images/ok.png"));
    }

    if(TestResult::instance()->_testResult[TestCase::GSM4G_Send_Data] == false){
        ui->pic_4G_SendData->setIcon(QIcon(":/Images/error.png"));
    }
    else{
        numberOfPass++;
        ui->pic_4G_SendData->setIcon(QIcon(":/Images/ok.png"));
    }

    if(TestResult::instance()->_testResult[TestCase::GSM4G_Receive_Data] == false){
        ui->pic_4G_ReceiveData->setIcon(QIcon(":/Images/error.png"));
    }
    else{
        numberOfPass++;
        ui->pic_4G_ReceiveData->setIcon(QIcon(":/Images/ok.png"));
    }

    ui->txt_4G_ConnectionStatus->setText(GSM4GTest::instance()->connectionStatus);
    ui->txt_4G_IPAddress->setText(GSM4GTest::instance()->IP);
    ui->txt_4G_IMEI->setText(GSM4GTest::instance()->IMEI);

    if(GSM4GTest::instance()->testStart){
        ui->gif_4g_loading->setVisible(true);
    }
    else{
        ui->gif_4g_loading->setVisible(false);
    }

    if(GSM4GTest::instance()->testStart || EthernetTest::instance()->testStart || WiFiTest::instance()->testStart){
        ui->btn_Ethernet_StartTest->setEnabled(false);
        ui->btn_WiFi_StartTest->setEnabled(false);
        ui->btn_4G_StartTest->setEnabled(false);
    }
    else{
        ui->btn_Ethernet_StartTest->setEnabled(true);
        ui->btn_WiFi_StartTest->setEnabled(true);
        ui->btn_4G_StartTest->setEnabled(true);
    }

    //Touch
    if(TestResult::instance()->_testResult[TestCase::Touch] == false){
        ui->pic_Touch->setIcon(QIcon(":/Images/error.png"));
    }
    else{
        numberOfPass++;
        ui->pic_Touch->setIcon(QIcon(":/Images/ok.png"));
    }

    //Stability
    ui->txt_Ethernet_stability->setText(QString::number(NetworkStabilityTest::instance()->ethernetNumberOfSuccess) + " passed out of " + QString::number(NetworkStabilityTest::instance()->numberOfTests));
    ui->txt_WiFi_stability->setText(QString::number(NetworkStabilityTest::instance()->wifiNumberOfSuccess) + " passed out of " + QString::number(NetworkStabilityTest::instance()->numberOfTests));
    ui->txt_GSM4G_stability->setText(QString::number(NetworkStabilityTest::instance()->gsm4GNumberOfSuccess) + " passed out of " + QString::number(NetworkStabilityTest::instance()->numberOfTests));
    ui->progressBar_Stability->setValue(NetworkStabilityTest::instance()->numberOfTests);




    ui->txt_testResult->setText(QString::number(numberOfPass) + " passed out of 28");


    FileHandler::instance()->saveResult();
}



