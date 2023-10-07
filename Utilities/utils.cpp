#include "utils.h"

Utils::Utils()
{
}

unsigned long long Utils::getEpochTime()
{
    long ms; // Milliseconds
    time_t s;  // Seconds
    unsigned long long epoch = 0;
    struct timespec spec;

    clock_gettime(CLOCK_REALTIME, &spec);

    s  = spec.tv_sec;
    ms = round(spec.tv_nsec / 1.0e6); // Convert nanoseconds to milliseconds
    if (ms > 999) {
        s++;
        ms = 0;
    }

    epoch = (intmax_t)s;
    epoch = epoch*1000 + ms;
    return epoch;
}

std::string Utils::getDate()
{
    time_t now = time(0);

    // convert now to string form
    tm* currentTime = localtime(&now);

    int year = currentTime->tm_year + 1900;
    int month = currentTime->tm_mon + 1;
    int day = currentTime->tm_mday;

    char res[8];
    sprintf(res, "%04d%02d%02d", year, month, day);

    return res;
}
std::string Utils::getTime()
{
    time_t now = time(0);

    // convert now to string form
    tm* currentTime = localtime(&now);

    int hour = currentTime->tm_hour;
    int min = currentTime->tm_min;
    int sec = currentTime->tm_sec;

    char res[8];
    sprintf(res, "%02d%02d%02d", hour, min, sec);

    return res;
}


std::string Utils::convertEpochToStr(unsigned long long epoch_time ,std::string format) {
    char MY_TIME[50] = {0};
    struct tm *tmp ;

    //localtime() uses the time pointed by t ,
    // to fill a tm structure with the
    // values that represent the
    // corresponding local time.

    long int t_time = epoch_time/1000;

    tmp = localtime((const long int*) &t_time);

    // using strftime to display time
    strftime(MY_TIME, sizeof(MY_TIME), format.c_str(), tmp);
    std::string ret_str(MY_TIME);
    return ret_str;
}

int Utils::stoi(std::string str)
{
    int i;
    sscanf(str.c_str(), "%d", &i);
    return i;
}

char* Utils::itoa(unsigned char inputInt)
{
    int a = inputInt % 16;
    int b = inputInt / 16;

    char outBuf[2];

    switch(a)
    {
    case 0:
        outBuf[0] = '0';
        break;

    case 1:
        outBuf[0] = '1';
        break;

    case 2:
        outBuf[0] = '2';
        break;

    case 3:
        outBuf[0] = '3';
        break;

    case 4:
        outBuf[0] = '4';
        break;

    case 5:
        outBuf[0] = '5';
        break;

    case 6:
        outBuf[0] = '6';
        break;

    case 7:
        outBuf[0] = '7';
        break;

    case 8:
        outBuf[0] = '8';
        break;

    case 9:
        outBuf[0] = '9';
        break;

    case 10:
        outBuf[0] = 'A';
        break;

    case 11:
        outBuf[0] = 'B';
        break;

    case 12:
        outBuf[0] = 'C';
        break;

    case 13:
        outBuf[0] = 'D';
        break;

    case 14:
        outBuf[0] = 'E';
        break;

    case 15:
        outBuf[0] = 'F';
        break;

    }

    switch(b)
    {
    case 0:
        outBuf[1] = '0';
        break;

    case 1:
        outBuf[1] = '1';
        break;

    case 2:
        outBuf[1] = '2';
        break;

    case 3:
        outBuf[1] = '3';
        break;

    case 4:
        outBuf[1] = '4';
        break;

    case 5:
        outBuf[1] = '5';
        break;

    case 6:
        outBuf[1] = '6';
        break;

    case 7:
        outBuf[1] = '7';
        break;

    case 8:
        outBuf[1] = '8';
        break;

    case 9:
        outBuf[1] = '9';
        break;

    case 10:
        outBuf[1] = 'A';
        break;

    case 11:
        outBuf[1] = 'B';
        break;

    case 12:
        outBuf[1] = 'C';
        break;

    case 13:
        outBuf[1] = 'D';
        break;

    case 14:
        outBuf[1] = 'E';
        break;

    case 15:
        outBuf[1] = 'F';
        break;

    }

    return outBuf;
}


char* Utils::int2ByteArray(int input){
    char buf[4];
    for(int i = 0; i < 4; i++)
    {
        buf[i] = input % 256;
        input /= 256;
    }

    return buf;
}

std::vector<std::string> &Utils::split(const std::string &s, char delim,std::vector<std::string> &elems)
{
    std::stringstream ss(s);
    std::string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return  elems;
}

char* Utils::string2ByteArray(char* input, int size){
    char buf[200];
    int temp1, temp2;
    for(int i = 0; i < size / 2; i++)
    {
        temp1 = 0;
        temp2 = 0;
        temp1 = input[2 * i] - 48;
        temp2 = input[2 * i + 1] - 48;
        if(temp1 > 9){
            temp1 -= 7;
            if(temp1 > 9){
                temp1 -= 32;
            }
        }
        if(temp2 > 9){
            temp2 -= 7;
            if(temp1 > 9){
                temp1 -= 32;
            }
        }
        buf[i] = temp1 * 16 + temp2;
    }


    return buf;
}

char* Utils::string2ByteArray(const char* input, int size){
    char buf[200];
    int temp1, temp2;
    for(int i = 0; i < size / 2; i++)
    {
        temp1 = 0;
        temp2 = 0;
        temp1 = input[2 * i] - 48;
        temp2 = input[2 * i + 1] - 48;
        if(temp1 > 9){
            temp1 -= 7;
            if(temp1 > 9){
                temp1 -= 32;
            }
        }
        if(temp2 > 9){
            temp2 -= 7;
            if(temp1 > 9){
                temp1 -= 32;
            }
        }
        buf[i] = temp1 * 16 + temp2;
    }


    return buf;
}


unsigned char Utils::CRC8(const unsigned char *data, unsigned char len)
{
    unsigned char crc = 0x00;

    while (len--)
    {
        unsigned char extract = *data++;

        for (unsigned char tempI = 8; tempI; tempI--)
        {
            unsigned char sum = (crc ^ extract) & 0x01;
            crc >>= 1;

            if (sum)
            {
                crc ^= 0x8C;
            }

            extract >>= 1;
        }
    }

  return crc;
}
