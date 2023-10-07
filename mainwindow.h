#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "Utilities/common.h"
#include "Utilities/constants.h"
#include "Utilities/utils.h"
#include "Utilities/threading.h"
#include "Utilities/Logger.h"
#include "testresult.h"
#include "TestHandler/gpstest.h"
#include "TestHandler/rs232test.h"
#include "TestHandler/rs485test.h"
#include "TestHandler/audiotest.h"
#include "TestHandler/wifitest.h"
#include "TestHandler/gsm4gtest.h"
#include "TestHandler/ethernettest.h"
#include "TestHandler/qrtest.h"
#include "NetworkManager/ftphandler.h"
#include "NetworkManager/networkstabilitytest.h"
#include "FileManager/filehandler.h"



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QDateTime       dateTime;
    QTimer          *clockTimer;
    QTimer          *updateStatusTimer;

    int             touchButton1;
    int             touchButton2;
    int             touchButton3;
    int             touchButton4;

    int             rs232PrintLogCount = 0;

    QMovie *loadingGif_General = new QMovie(":/Images/loading.gif");
    QMovie *loadingGif_GPS = new QMovie(":/Images/loading.gif");
    QMovie *loadingGif_Ethernet = new QMovie(":/Images/loading.gif");
    QMovie *loadingGif_WiFi = new QMovie(":/Images/loading.gif");
    QMovie *loadingGif_4G = new QMovie(":/Images/loading.gif");
    QMovie *loadingGif_RS232_RS485 = new QMovie(":/Images/loading.gif");


private slots:
    void on_btn_General_StartTest_clicked();

    void on_btn_GPS_StartTest_clicked();

    void on_pic_General_AudioTest_clicked();


    void on_btn_WiFi_StartTest_clicked();

    void updateStatus();
    void clockUpdate();

    void on_slider_brightness_valueChanged(int value);

    void on_pic_General_Brightness_clicked();

    void on_pic_General_DO_clicked();

    void on_pic_General_DI_clicked();

    void on_btn_Ethernet_StartTest_clicked();

    void on_btn_4G_StartTest_clicked();

    void on_btn_General_DOLow_clicked();

    void on_btn_General_DOHigh_clicked();

    void on_btn_General_DIRead_clicked();


    void on_btn_RS232_Start_clicked();

    void on_btn_RS232_Stop_clicked();

    void on_btn_RS485_Start_clicked();

    void on_btn_RS485_Stop_clicked();

    void on_btn_Touch_1_clicked();

    void on_btn_Touch_2_clicked();

    void on_btn_Touch_3_clicked();

    void on_btn_Touch_4_clicked();

    void on_btn_Stability_clicked();

    void on_btn_upload_clicked();

    void on_btn_reset_clicked();

    void on_btn_Stability_Stop_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
