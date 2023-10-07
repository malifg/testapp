#include "qrtest.h"

QRTest::QRTest()
{
}

int QRTest::initialize(){
    testStart = false;


    char *ttyName = PORT_QR;

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

    usleep(200000);

    return OK;
}

void QRTest::run(){
    while (true)
    {
        if(testStart)
        {
            HardwareController::instance()->DO_setValue(GPIO_QR_TRIG_PIN, 0);

            QByteArray readBuf;

            fd_set set;
            struct timeval timeout;
            timeout.tv_sec = 0;
            timeout.tv_usec = 50000;
            FD_ZERO(&set);  /* clear the set */
            FD_SET(mHandle, &set); /* add our file descriptor to the set */


            char buffer[16] = {0};
            int pos = 0;
            int tryCount = 0;

            while( tryCount < 16 )
            {
                if(select(mHandle + 1, &set, nullptr, nullptr, &timeout) >0)
                {
                    read(mHandle, buffer + pos, 1);           // Note you should be checking the result
                    if( buffer[pos] == '\n' )
                        break;
                    readBuf.append(buffer[pos]);
                    pos++;
                }
                tryCount++;
            }
            QString QRDataString = readBuf;

            if(QRDataString.size() > 12)
            {
                if(QRDataString.left(4) == "BV2-")
                {
                    TestResult::instance()->deviceID = QRDataString.toStdString();
                    TestResult::instance()->_testResult[TestCase::QR] = true;
                    testStart = false;
                }
            }

            usleep(100000);
            HardwareController::instance()->DO_setValue(GPIO_QR_TRIG_PIN, 1);

        }
    }
}

