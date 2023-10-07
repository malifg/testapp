#include "SCS_CVEND.h"

#include <unistd.h>
#include <termios.h>
#include <fcntl.h>

#include<iostream>

CVENDTest::CVENDTest()
{
    recievedData = "";
    mHandle = -1;
    mThreadCondition = false;
    mTestResultsHandler = TestResultsHandler::instance();
}

CVENDTest::~CVENDTest()
{
    stop();
    if (mHandle >=0)
    {
        close(mHandle);
        mHandle = -1;
    }
}

void CVENDTest::start(Request_type req)
{
    if (mThreadCondition == true)
    {
        return;
    }

    if(mThread.joinable())
    {
        mThread.join();
    }

    mThreadCondition.store(true);
    mThread = std::thread(&CVENDTest::run, this, req);
}

void CVENDTest::stop()
{
    if (mThreadCondition == false)
    {
        return;
    }

    mThreadCondition.store(false);

    if(mThread.joinable())
    {
        mThread.join();
    }
}

bool CVENDTest::isWorking() const
{
    return mThreadCondition.load();
}

int CVENDTest::initialize()
{
    char ttyName[11 + 1] = {0};
    if (mHandle >=0)
    {
        close(mHandle);
        mHandle = -1;
    }
    if (getPortName(SMART_CARD_READER_PORT_NAME, ttyName) !=SUCCESS)
    {
        return -1;
    }
    mHandle = open(ttyName, O_RDWR);

    speed_t speed = 0;

    speed = B230400;

    struct termios tty;

    if (tcgetattr(mHandle, &tty) < 0)
    {
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

    if(mTestResultsHandler->getTagStr(mTestResultsHandler->Tags.Res_CVEND_MAC, mac) == false)
    {
        mac = "00:00:00:00:00:00";
    }
    return OK;
}


std::string CVENDTest::getReceivedData() const
{
    return recievedData;
}

void CVENDTest::run(Request_type req)
{

    unsigned char cbuf[200];

    if (req == Request_type::Send_Data_req)
    {
        fd_set set;
        struct timeval timeout = {0, 100000};
        const uint8_t writeBuf[7] = {0x07,0x00,0x00,0x04,0x02,0x12,0xc1};

        FD_ZERO(&set);  /* clear the set */
        FD_SET(mHandle, &set); /* add our file descriptor to the set */
        memset(cbuf,0,sizeof(cbuf));
        if (write(mHandle,writeBuf,sizeof(writeBuf))== sizeof(writeBuf))
        {
            recievedData = "";
            sleep(1);
            if(select(mHandle + 1, &set, nullptr, nullptr, &timeout) >0)
            {
                int len = read(mHandle,cbuf,sizeof(cbuf));
                if(len > 0 )
                {
                    char buf [len * 3 + 1];
                    for(int i = 0 ; i < len ; i++)
                    {
                        sprintf(&buf[i * 3],"%02x ",cbuf[i]);
                    }
                    recievedData = std::string(buf);
                }
                if (len >= 46)
                {
                    mTestResultsHandler->updateTagBool(mTestResultsHandler->Tags.Res_CVEND, true);
                }
            }
        }
    }
    else if(req == Request_type::Send_Mac_req)
    {
        fd_set set;
        struct timeval timeout = {0, 100000};
        const uint8_t writeBuf[4] = {0x04, 0xff, 0x43, 0x30};

        FD_ZERO(&set);  /* clear the set */
        FD_SET(mHandle, &set); /* add our file descriptor to the set */

        memset(cbuf,0,sizeof(cbuf));

        if (write(mHandle,writeBuf,sizeof(writeBuf))== sizeof(writeBuf))
        {
            recievedData = "";
            sleep(1);

            if(select(mHandle + 1, &set, nullptr, nullptr, &timeout) >0)
            {
                int len = read(mHandle,cbuf,sizeof(cbuf));
                if(len > 0 )
                {
                    char buf [len * 3 + 1];
                    for(int i = 0 ; i < len ; i++)
                    {
                        sprintf(&buf[i * 3],"%02x ",cbuf[i]);
                    }
                    recievedData = std::string(buf);
                }

                if(len == 128)
                {
                    char buf [6 * 3 + 1];

                    sprintf(buf, "%s", &cbuf[2]);
                    mTestResultsHandler->updateTagStr(mTestResultsHandler->Tags.Res_CVEND_ID, std::string(buf));

                    sprintf(buf,"%02X:%02X:%02X:%02X:%02X:%02X",cbuf[120],cbuf[121],cbuf[122],cbuf[123],cbuf[124],cbuf[125]);
                    //        sprintf(mac,"%02x:%02x:%02x:%02x:%02x:%02x",cbuf[120],cbuf[121],cbuf[122],cbuf[123],cbuf[124],cbuf[125]);
                    mac = std::string(buf);
                    mTestResultsHandler->updateTagStr(mTestResultsHandler->Tags.Res_CVEND_MAC, mac);
                }
            }
        }
    }
    else if (req == Request_type::Send_Ping_req)
    {
        bool iRet = pingCVENDNMAP();
        mTestResultsHandler->updateTagBool(mTestResultsHandler->Tags.Res_CVEND_PING,iRet);
    }

    mThreadCondition = false;
}

bool CVENDTest::pingCVENDNMAP()
{
    Utils::executeCommand("apt-get install nmap -y --fix-missing");
    std::string baseIP  = Utils::executeCommand("ifconfig eth0 | grep \"inet addr:\" | awk ' {print $2}' | cut -d\":\" -f 2 | cut -d \".\" -f 1,2,3 -z");
    std::string cmd = "nmap -sP " + baseIP + ".0/24 | grep " + mac;

    if(Utils::executeCommand(cmd).find(mac) != std::string::npos)
    {
        return true;
    }

    return false;

}

bool CVENDTest::pingCVEND()
{
//    int max = 0;
//    int min = 0;
    macFound = false;
    std::vector<std::thread*> thr;
    std::string baseIP  = Utils::executeCommand("ifconfig eth0 | grep \"inet addr:\" | awk ' {print $2}' | cut -d\":\" -f 2 | cut -d \".\" -f 1,2,3 -z");
    baseIP+= ".";
    std::cout << baseIP << std::endl;
//    for ( int i = 1 ; max < 254 ; i++)
//    {
//        min = (i - 1) * 40;
//        max = 40 * i;
//        thr.push_back(new std::thread(&CVENDTest::doPing,this, baseIP , mac , (min ? min : 1) , (max > 254 ? 254 : max)));
                thr.push_back(new std::thread(&CVENDTest::doPing,this, baseIP , mac , 1, 254));
        std::this_thread::sleep_for(std::chrono::seconds(1));
//    }

    for(std::vector<std::thread*>::iterator t = thr.begin();t < thr.end() ; t++)
    {
        if(((std::thread *)*t)->joinable())
            ((std::thread *)*t)->join();
        delete *t;
    }

    if (macFound)
    {
        std::string cmd = "ping -I eth0 " + deviceIP +" -c 1";
        if(system(cmd.c_str()) == 0)
        {
            return true;
        }
    }

    return false;
}

inline void CVENDTest::doPing(std::string baseIP, std::string mac, int min, int max)
{
    for (int i = min ; i < max ; i++)
    {
        if (macFound == true )
        {
            break;
        }
        std::string cmd = "ping -I eth0 " + baseIP + std::to_string(i) + " -c 5 > /dev/null";
        system(cmd.c_str());
        std::string res = Utils::executeCommand("arp -na | grep \"" + mac + "\" | awk '/?/ {print $2}' | cut -d\"(\" -f 2 | cut -d\")\" -f 1 -z");
        if (res.length() > 7)
        {
            macFound = true;
            deviceIP = res;
        }
        sleep(1);
    }
}
