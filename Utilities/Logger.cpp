#include "Logger.h"


std::mutex Logger::_mutex;
std::string Logger::currFileName;
std::thread Logger::mthread;
QList<QString> Logger::queue;


const long sizeLimit =15 * 1024 * 1024;


void Logger::Init(){
    queue.clear();
    if(FileSystem::dirExists(LOG_DIR)==false){
        std::cout << "Log dir not exists!" << std::endl;
        if(FileSystem::createDir(LOG_DIR)==true)
            std::cout << "Log dir Created" << std::endl;
    }
    currFileName = getNewFileName();
    LOG(__FILE__,__FUNCTION__,__LINE__,LOG_TYPE::RELEASE,"-------------------------- Application StartUp --------------------------------");
    mthread = std::thread (&Logger::run);

}


void Logger::copyLogs(const char * dst){
    std::lock_guard<std::mutex> lk (_mutex);
    while(queue.size()){
        auto tmp = queue.front();
        queue.pop_front();
        if(tmp != ""){
            std::cout << tmp.toStdString();
            fileLogger((char *)tmp.toStdString().c_str(),tmp.length());
        }
    }
    system("sync");
    std::string cmd = std::string("cp " LOG_DIR "* ") + std::string(dst);
    system(cmd.c_str());
    system("sync");
}

inline void Logger::LOG(const char* file, const char * function,u_int32_t line, enum LOG_TYPE logType, const char* format, ...){
    if (logType & (FILELOGGER_FILTER))
    {
	    _mutex.lock();
	    time_t t = time(NULL);
	    struct tm tm = *localtime(&t);
        va_list 	args;
        va_start(args, format);
        try{
            static  char buffer[DEBUG_BUFFER_SIZE + 1] 	= {0};
            static char temp[DEBUG_BUFFER_SIZE + 1] 	= {0};
            QString tmp;
            vsnprintf(temp , DEBUG_BUFFER_SIZE, format, args);
            va_end(args);
            sprintf(buffer, "%04d.%02d.%02d - %02d:%02d:%02d | %s | %s | %d | %s\r\n",
                    tm.tm_year + 1900, tm.tm_mon+1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec,
                    file, function, line, temp);
            tmp = buffer;
            queue.push_back(tmp);
            tmp.clear();
        }
        catch(...){
            printf("\n\n\nFATAL ERROR ON LOGGER\n");
        }
        _mutex.unlock();
    }

}

void Logger::run(){
    QString tmp;
    while(true){
        _mutex.lock();
        if(queue.size()){
            tmp.clear();
            tmp = queue.front();
            queue.pop_front();
            _mutex.unlock();
            if(tmp != ""){
            std::cout << tmp.toStdString() << std::endl;
            fileLogger((char *)tmp.toStdString().c_str(),tmp.length());
            }
        }
        else{
            _mutex.unlock();
        }
    }
}

inline std::string Logger::getLogType(LOG_TYPE type){
    switch ((int)type){
        case RELEASE: return "RELEASE";
        case TRACE: return "TRACE";
        case DEBUG: return "DEBUG";
        case FATAL: return "FATAL";
    }
    return "";
}
inline void Logger::fileLogger(char * buffer, int len){
    FileSystem::write(currFileName.c_str(),buffer,len);
    isSizeLimitReached();
}

inline void Logger::ttyLogger(char * buffer, int len){
	std::ofstream log_stream{"/dev/ttyS0"};
	if(log_stream.is_open())log_stream << buffer;
	log_stream.close();
}

inline void Logger::isSizeLimitReached(){
    auto file_size = FileSystem::getFileSize(currFileName.c_str());
    if (file_size > sizeLimit)
        currFileName = getNewFileName();
}

inline std::string Logger::getNewFileName(){
    std::string filePath ="";

    std::list<std::string> names;
    if(FileSystem::getFiles(LOG_DIR,names)){
        int fileCounter = 0;
        for(std::string filename: names){
            if(!(filename.substr(0, 8) == "LogFile-"))
                continue;
            std::string delim = "LogFile-";
            int delimIndex =filename.find(delim);
            std::string numberStr = filename.substr(delimIndex + delim.length(),filename.length());
            int number =0;
            std::stringstream geek(numberStr);
            geek >> number;
            if (fileCounter < number)
                fileCounter = number;
        }
        filePath = LOG_DIR "LogFile-" + std::to_string(fileCounter);
        if (FileSystem::exist(filePath.c_str()))
        {
            auto file_size = FileSystem::getFileSize(filePath.c_str());
            if (file_size > sizeLimit){
                fileCounter++;
                if (fileCounter >=5){
                    fileCounter--;
                    removeOldLogs(names);
                }
                filePath = LOG_DIR "LogFile-" + std::to_string(fileCounter);
            }
        }
    }
    return filePath;
}

inline void Logger::removeOldLogs(const std::list<std::string> &names){
    for(std::string filename: names)
    {
        std::string filePath;
        if(!(filename.substr(0, 8) == "LogFile-")){
            filePath = LOG_DIR;
            filePath+=filename;
            printf("removing file:%s",filename.c_str());
            FileSystem::removefile(filePath.c_str());
            continue;
        }
        std::string delim = "LogFile-";
        int delimIndex =filename.find(delim);
        std::string numberStr = filename.substr(delimIndex + delim.length(),filename.length());
        try {
            int number = std::stoi(numberStr);
            filePath = LOG_DIR + delim + std::to_string(number);
            if (number == 0){
                FileSystem::removefile(filePath.c_str());
            }
            else{
                std::string dst = LOG_DIR "LogFile-" + std::to_string(number - 1);
                FileSystem::rename(filePath.c_str(),dst.c_str());
            }
        }
        catch(...) {}
    }
}
