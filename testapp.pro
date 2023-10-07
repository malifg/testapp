#-------------------------------------------------
#
# Project created by QtCreator 2020-08-22T04:53:59
#
#-------------------------------------------------

QT       += core gui

QMAKE_CXXFLAGS += -std=c++11
QMAKE_CXXFLAGS_WARN_ON += -Wno-reorder

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SCV_testApp_V2_0_0
TEMPLATE = app

target.path = /root/SCV_testApp_V2_0_0
INSTALLS += target


SOURCES += main.cpp\
        mainwindow.cpp \
    Utilities/utils.cpp \
    HardwareController/hardwarecontroller.cpp \
    testresult.cpp \
    TestHandler/gpstest.cpp \
    TestHandler/rs232test.cpp \
    TestHandler/rs485test.cpp \
    TestHandler/audiotest.cpp \
    TestHandler/wifitest.cpp \
    NetworkManager/ftphandler.cpp \
    TestHandler/ethernettest.cpp \
    FileManager/filehandler.cpp \
    TestHandler/gsm4gtest.cpp \
    TestHandler/qrtest.cpp \
    NetworkManager/networkstabilitytest.cpp \
    Utilities/Logger.cpp \
    Utilities/filesystem.cpp

HEADERS  += mainwindow.h \
    Utilities/utils.h \
    Utilities/threading.h \
    Utilities/singleton.h \
    Utilities/enumerations.h \
    Utilities/constants.h \
    Utilities/common.h \
    HardwareController/hardwarecontroller.h \
    testresult.h \
    TestHandler/gpstest.h \
    TestHandler/rs232test.h \
    TestHandler/rs485test.h \
    TestHandler/audiotest.h \
    TestHandler/wifitest.h \
    NetworkManager/ftphandler.h \
    TestHandler/ethernettest.h \
    filehandler.h \
    FileManager/filehandler.h \
    TestHandler/gsm4gtest.h \
    TestHandler/qrtest.h \
    NetworkManager/networkstabilitytest.h \
    Utilities/Logger.h \
    Utilities/filesystem.h

FORMS    += mainwindow.ui

RESOURCES += \
    res/res.qrc
