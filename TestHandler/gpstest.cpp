#include "gpstest.h"

GPSTest::GPSTest()
{
}

int GPSTest::initialize(){
    fixSatus = "Not Fix";
    testStart = false;
    timeval time1;
    gettimeofday(&time1, NULL);
    startTime = (time1.tv_sec * 1000) + (time1.tv_usec / 1000);

    HardwareController::instance()->DO_setValue(GPIO_GPS_RESET_PIN, true);
    usleep(500000);
    HardwareController::instance()->DO_setValue(GPIO_GPS_RESET_PIN, false);
    usleep(500000);

    char *ttyName = PORT_GPS;

    if (mHandle >=0)
    {
        close(mHandle);
        mHandle = -1;
    }

    mHandle = open(ttyName, O_RDWR);
    if(mHandle < 0)
    {
        Logger::LOG(__FILE__, __FUNCTION__, __LINE__, LOG_TYPE::DEBUG, "Failed to open %s port", ttyName);
        return -1;
    }

    speed_t speed = B9600;

    struct termios tty;

    if (tcgetattr(mHandle, &tty) < 0)
    {
        Logger::LOG(__FILE__, __FUNCTION__, __LINE__, LOG_TYPE::DEBUG, "Failed to open %s port", ttyName);
        return errno;
    }

    cfsetospeed(&tty, speed);
    cfsetispeed(&tty, speed);

    tty.c_cflag |= (CLOCAL | CREAD);    /* ignore modem controls */
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;                 /* 8-bit characters */
    tty.c_cflag &= ~PARENB;             /* no parity bit */
    tty.c_cflag &= ~CSTOPB;             /* only need 1 stop bit */
    tty.c_cflag &= ~CRTSCTS;            /* no hardware flowcontrol */

    /* setup for non-canonical mode */
    tty.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL | IXON);
    tty.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
    tty.c_oflag &= ~OPOST;

    /* fetch bytes as they become available */
    tty.c_cc[VMIN] = 1;
    tty.c_cc[VTIME] = 1;

    if (tcsetattr(mHandle, TCSANOW, &tty) != 0)
    {
        return errno;
    }

    return OK;

}

void GPSTest::run()
{
    while(true)
    {
        if(testStart)
        {
            checkData();
            usleep(1000000);
            for(int i = 0; i < GPS_TIMEOUT; i++)
            {
                if(TestResult::instance()->_testResult[TestCase::GPS_FixStatus] == false ||
                   TestResult::instance()->_testResult[TestCase::GPS_TTFF] == false ||
                   TestResult::instance()->_testResult[TestCase::GPS_Accuracy] == false ||
                   TestResult::instance()->_testResult[TestCase::GPS_Data_Ready] == false ||
                   TestResult::instance()->_testResult[TestCase::GPS_NumberOfSat] == false)
                {
                    checkData();
                    usleep(1000000);
                }
            }
            testStart = false;
        }
    }
}


int GPSTest::checkData()
{
    timeval time1;
    gettimeofday(&time1, NULL);
    endTime = (time1.tv_sec * 1000) + (time1.tv_usec / 1000);
    TTFF = (int) (endTime - startTime) / 1000;
    for(int i = 0; i < GPS_BUS_TRY_COUNT; i++)
    {
        QByteArray readBuf;

        fd_set set;
        struct timeval timeout;
        timeout.tv_sec = 2;
        timeout.tv_usec = 0;
        FD_ZERO(&set);  /* clear the set */
        FD_SET(mHandle, &set); /* add our file descriptor to the set */


        char buffer[256] = {0};
        int pos = 0;

        while( pos < 255 )
        {
            if(select(mHandle + 1, &set, nullptr, nullptr, &timeout) >0)
            {
                read(mHandle, buffer + pos, 1);           // Note you should be checking the result
                if( buffer[pos] == '\n' )
                    break;
                readBuf.append(buffer[pos]);
                pos++;
            }
        }

        if(readBuf.size() > 0)
        {
            QString test = readBuf;
            if (readBuf.contains("$GNGSA") || readBuf.contains("$GPGSA"))
            {
                QList<QByteArray> GPGSADataFields = readBuf.split(',');
                switch (GPGSADataFields[2][0]) {
                case '1':
                    fixSatus = "Not Fix";
                    break;
                case '2':
                    fixSatus = "2D";
                    break;
                case '3':
                    TestResult::instance()->_testResult[TestCase::GPS_FixStatus] = true;
                    if(TTFF < GPS_MIN_TTFF2){
                        TestResult::instance()->_testResult[TestCase::GPS_TTFF] = true;
                    }
                    fixSatus = "3D";
                    break;
                default:
                    fixSatus = "Not Fix";
                    break;
                }
                return OK;
            }
            if (readBuf.contains("$GPGGA") || readBuf.contains("$GNGGA"))
            {
                QList<QByteArray> GPGGADataFields = readBuf.split(',');

                if(GPGGADataFields[2].size() < 4){
                    return GPS_NOT_FIXED;
                }

                currentTime = "";
                currentTime += GPGGADataFields[1][0];
                currentTime += GPGGADataFields[1][1];
                currentTime += ":";
                currentTime += GPGGADataFields[1][2];
                currentTime += GPGGADataFields[1][3];
                currentTime += ":";
                currentTime += GPGGADataFields[1][4];
                currentTime += GPGGADataFields[1][5];


                latitude = "";
                latitude += GPGGADataFields[2];
                latitude += " ";
                latitude += GPGGADataFields[3];

                longitude = "";
                longitude += GPGGADataFields[4];
                longitude += " ";
                longitude += GPGGADataFields[5];

                altitude = "";
                altitude += GPGGADataFields[9];
                altitude += " ";
                altitude += GPGGADataFields[10];

                numberOfSat = "";
                numberOfSat += GPGGADataFields[7];
                if(GPGGADataFields[7].toInt() >= GPS_MIN_NUMBER_OF_SAT){
                    TestResult::instance()->_testResult[TestCase::GPS_NumberOfSat] = true;
                }

                accuracy = "";
                accuracy += GPGGADataFields[8];
                if(GPGGADataFields[8].toDouble() < GPS_MAX_ACCURACY){
                    TestResult::instance()->_testResult[TestCase::GPS_Accuracy] = true;
                }
                accuracy += " ";
                accuracy += "m";

                TestResult::instance()->_testResult[TestCase::GPS_Data_Ready] = true;

                return OK;
            }
            if (readBuf.contains("$GPRMC") || readBuf.contains("$GNRMC"))
            {
                QList<QByteArray> GPGGADataFields = readBuf.split(',');

            }
        }
        usleep(10000);
    }
    return GPS_TAG_NOT_FOUND;
}
