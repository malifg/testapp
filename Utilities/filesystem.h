#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include "Utilities/common.h"

typedef struct {
    std::string AvailableSpace, UsedSpace, TotalSpace;
}MemoryStr;
class FileSystem
{
public:
    static bool createDir(const char * address);
    static bool removeDir(const char * address);
    static bool dirExists(const char * address);
    static bool getFiles(const char * address,std::list<std::string> & retvalue);
    static bool open(const std::string &fileAddress, std::fstream *file, std::ios_base::openmode __mode = std::ios::out | std::ios::in | std::ios::app);
    static bool open(const char * fileAddress, std::fstream *file, std::ios_base::openmode __mode = std::ios::out | std::ios::in | std::ios::app);
    static void close(std::fstream &file);
    static bool exist(const char fileAddress[]);
    static bool write(std::fstream &file, const char *data, u_int32_t len);
    static bool write(const char fileAddress[], const char* data, u_int32_t len);
    static bool writeLine(std::fstream &file, const char *data, u_int32_t len);
    static bool writeLine(const char fileAddress[], const char *data, u_int32_t len);
    static bool readAll(std::fstream & file, std::string &buffer);
    static bool readAll(const char fileAddress[], std::string & buffer);
    static bool readAll(const char fileAddress[], std::list<unsigned char> &buffer);
    static bool readLine(std::fstream & file, std::string & buffer);
    static bool update(const char fileAddress[], const char *data, u_int32_t len);
    static bool update(const char fileAddress[],const std::list<std::string> &data);
    static bool removefile(const char * fileAddress);
    static MemoryStr getAvailableMemory();
    static long long getFileSize(const char *filename);
    static bool rename(const char *src, const char *dst);

private:
    static std::mutex mDirMutex;
    static std::mutex mFileMutex;
};

#endif // FILESYSTEM_H
