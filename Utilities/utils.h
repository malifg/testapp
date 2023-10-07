#ifndef UTILS_H
#define UTILS_H

#include "Utilities/common.h"
#include "Utilities/singleton.h"

class Utils : public Singleton<Utils>
{
private:


public:
    Utils();
    unsigned long long getEpochTime();
    std::string getDate();
    std::string getTime();
    std::string convertEpochToStr(unsigned long long epoch_time ,std::string format);
    int stoi(std::string str);
    char* itoa(unsigned char inputInt);
    char* int2ByteArray(int input);
    std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);
    char* string2ByteArray(char* input, int size);
    char* string2ByteArray(const char* input, int size);
    unsigned char CRC8(const unsigned char *data, unsigned char len);
    void setTime(int year, int month, int day, int hour, int min, int sec);
};

#endif // UTILS_H
