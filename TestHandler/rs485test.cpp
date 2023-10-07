#include "rs485test.h"

RS485Test::RS485Test()
{
}

int RS485Test::initialize()
{
    char *ttyName = PORT_RS485;

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

void RS485Test::closePort()
{
    if (mHandle >=0)
    {
        close(mHandle);
        mHandle = -1;
    }
}


void RS485Test::run()
{
    Logger::LOG(__FILE__, __FUNCTION__, __LINE__, LOG_TYPE::DEBUG, "RS232 poll started");
    tcflush(mHandle, TCIOFLUSH);
    while (testStart == true)
    {
        if(isTester == true)
        {
            Logger::LOG(__FILE__, __FUNCTION__, __LINE__, LOG_TYPE::DEBUG, "IN RS232 Tester");
        }
        else
        {
            Logger::LOG(__FILE__, __FUNCTION__, __LINE__, LOG_TYPE::DEBUG, "IN RS232 receiver");
            const char writeBuf[2] = {'1', '1'};
            if(write(mHandle,writeBuf, 2) < 2)
            {
                Logger::LOG(__FILE__, __FUNCTION__, __LINE__, LOG_TYPE::DEBUG, "Failed to send Recevier response bytes for RS232 Interface");
                break;
            }
        }

        fd_set set;
        struct timeval timeout;
        timeout.tv_sec = 2;
        timeout.tv_usec = 0;
        FD_ZERO(&set);  /* clear the set */
        FD_SET(mHandle, &set); /* add our file descriptor to the set */

        if(select(mHandle + 1, &set, nullptr, nullptr, &timeout) >0)
        {
            if (FD_ISSET(mHandle, &set))
            {
                unsigned char cbuf[50];
    //            std::string recievedData;
                int len = read(mHandle, cbuf, 50);
                std::cout << "Read Bytes: " << len << std::endl;

                if (len > 3)
                {
                    if(isTester == true && cbuf[0] == '1' && cbuf[1] == '1')
                    {
                        TestResult::instance()->_testResult[TestCase::RS232] = true;
                    }
                    else if(isTester == false && cbuf[0] == '2' && cbuf[1] == '2')
                    {
                        TestResult::instance()->_testResult[TestCase::RS232] = true;
                    }
                }

                if(isTester == true )
                {
                    const char writeBuf[2] = {'2', '2'};
                    if(write(mHandle,writeBuf, 2) < 2)
                    {
                        Logger::LOG(__FILE__, __FUNCTION__, __LINE__, LOG_TYPE::DEBUG, "Failed to send Tester bytes for RS232 Interface");
                        break;
                    }
                }
            }
        }
        else
        {
            std::cout<< "select failed\r\n";
        }
        usleep(100000);
    }
    testStart = false;
}
