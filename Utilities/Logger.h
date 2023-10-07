#ifndef LOGGER_H
#define LOGGER_H
#include "Utilities/common.h"
#include "Utilities/filesystem.h"
#include "Utilities/constants.h"

#define DEBUGF              0
#define DEBUG_BUFFER_SIZE   2048

#define FILELOGGER_FILTER ( LOG_TYPE::FATAL | LOG_TYPE::TRACE | LOG_TYPE::RELEASE | LOG_TYPE::DEBUG)

enum LOG_TYPE
{
    RELEASE = 0x01,
    TRACE = 0x02,
    DEBUG = 0x04,
    FATAL = 0x08
};

class Logger{
public:
    static void Init();
    static void LOG(const char* file, const char * function,u_int32_t line, enum LOG_TYPE logType, const char* format, ...);
    static void copyLogs(const char * dst);
    static inline std::string getLogType(LOG_TYPE type);
private :
    static void run();
    static void fileLogger(char * buffer, int len);
    static void ttyLogger(char * buffer, int len);
    static std::string getNewFileName();
    static void isSizeLimitReached();
    static void removeOldLogs(const std::list<std::string> &names);
    static std::mutex _mutex;
    static std::string currFileName;
    static std::thread mthread;
    static QList<QString> queue;
};

#endif // LOGGER_H
