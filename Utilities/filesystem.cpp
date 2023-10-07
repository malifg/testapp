#include "filesystem.h"

//using namespace std;
std::mutex FileSystem::mDirMutex;
std::mutex FileSystem::mFileMutex;

bool FileSystem::createDir(const char * address){
    if(dirExists(address))
        return true;
    std::unique_lock<std::mutex> lk (mDirMutex);
    try{
        if(mkdir(address,S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH)==0) return true;
    }
    catch(...){}
    return false;
}

bool FileSystem::removeDir(const char * address){
    if(!dirExists(address))
        return true;
    std::unique_lock<std::mutex> lk (mDirMutex);
    std::string cmd = "rm -r " + std::string(address);
    system(cmd.c_str());
    return true;
}

bool FileSystem::dirExists(const char * address){
    std::unique_lock<std::mutex> lk (mDirMutex);
    struct stat info;
    try{
        if( stat( address, &info ) == 0 )
            if( info.st_mode & S_IFDIR )  // S_ISDIR() doesn't exist on my windows
                return true;
    }
    catch(...){}
    return false;
}

bool FileSystem::getFiles(const char *address, std::list<std::string> &retvalue){
    retvalue.clear();
    DIR *dir=NULL;
    if (dirExists(address)){ 
        if ((dir = opendir (address)) != NULL) {
            struct dirent *ent;
            /* print all the files and directories within directory */
            while ((ent = readdir (dir)) != NULL) {
                if (ent->d_name == "." || ent->d_name == "..")
                    continue;
                retvalue.push_back(ent->d_name);
            }
            closedir (dir);
            return true;
        }
        else {
            /* could not open directory */
            if(dir)
                closedir(dir);
            perror ("can not open directory to read it's files");
            return false;
        }
    }
    if(dir)
        closedir(dir);
    return false;
}

bool FileSystem::open(const std::string &fileAddress, std::fstream *file, std::ios_base::openmode __mode){
    return FileSystem::open(fileAddress.c_str(),file,__mode);
}

bool FileSystem::open(const char * fileAddress, std::fstream *file, std::ios_base::openmode __mode)
{
    file->open(fileAddress,__mode);
    if(file->is_open()){
        return true;
    }
    printf("Failed to open '%s'.\n",fileAddress);
    return false;
}
void FileSystem::close(std::fstream & file){
    if(file.is_open())
        file.close();
}

bool FileSystem::exist(const char fileAddress[]){
    if(access( fileAddress, F_OK ) == -1)
        return false;
    return true;
}

bool FileSystem::write(std::fstream &file, const char *data, u_int32_t len){
    if(file.is_open()){
        file.write(data,len);
        //file.flush();
        return true;
    }
    return false;
}

bool FileSystem::write(const char fileAddress[], const char *data, u_int32_t len){
    std::ofstream file;
    file.open(fileAddress, std::ios::app | std::ios::out);
    if(file.is_open()){
        file.write(data,len);
        file.close();
        return true;
    }
    file.close();
    return false;
}
bool FileSystem::writeLine(std::fstream &file, const char *data, u_int32_t len){
    if(file.is_open()){
        file.write(data,len);
        file.write("\r\n",2);
        return true;
    }
    return false;
}

bool FileSystem::writeLine(const char fileAddress[], const char *data, u_int32_t len){
    std::ofstream file;
    file.open(fileAddress, std::ios::app | std::ios::out);
    if(file.is_open()){
        file.write(data,len);
        file.write("\r\n",2);
        file.close();
        return true;
    }
    file.close();
    return false;
}

bool FileSystem::readAll(std::fstream &file, std::string & buffer){
    buffer.clear();
    if(file.is_open()){
        if(file.eof()){
            std::cout << "EOF\n";
            file.clear();
        }
        file.seekg(0, std::ios::beg);
        file.seekg(0, std::ios::end);
        buffer.reserve(file.tellg());
        file.seekg(0, std::ios::beg);

        buffer.assign((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        if(file.good())
            return true;
    }
    return false;
}

bool FileSystem::readAll(const char fileAddress[], std::list<unsigned char> &buffer){
    buffer.clear();
    std::ifstream file;
    file.open(fileAddress, std::ios::in);
    if(file.is_open()){
        file.seekg(0, std::ios::end);
        size_t length = file.tellg();
        file.seekg(0, std::ios::beg);
        while (length--) {
            char  ch;
            file.read(&ch,1);
            buffer.push_back(ch);
        }
        if(file.good())
        {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

bool FileSystem::readAll(const char fileAddress[],std::string & buffer){
    buffer.clear();
    std::ifstream file;
    file.open(fileAddress, std::ios::in);
    if(file.is_open()){
        file.seekg(0, std::ios::end);
        buffer.reserve(file.tellg());
        file.seekg(0, std::ios::beg);

        buffer.assign((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        if(file.good())
        {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

bool FileSystem::readLine(std::fstream & file, std::string & buffer){
    buffer.clear();
    if (file.is_open()){
        if(!file.eof())
            getline (file,buffer);
        if(file.good())
            return true;
    }
    return false;
}
bool FileSystem::update(const char fileAddress[],const char *data, u_int32_t len){
    std::fstream file;
    file.open(fileAddress, std::ios::trunc | std::ios::out);
    if(file.is_open()){
        file.write(data,len);
        file.close();
        return true;
    }
    file.close();
    return false;
}
bool FileSystem::update(const char fileAddress[],const std::list<std::string> &data){
    std::fstream file;
    file.open(fileAddress, std::ios::trunc | std::ios::out);
    if(file.is_open()){
        for(std::string str:data)
            file.write(str.c_str(),str.length());
        file.close();
        return true;
    }
    file.close();
    return false;
}

bool FileSystem::removefile(const char * fileAddress)
{
    if(exist(fileAddress)){
        std::string cmd = "rm " + std::string(fileAddress);
        system(cmd.c_str());
        system("sync");
        return true;
    }
    return true;
}
MemoryStr FileSystem::getAvailableMemory(){
    char charbuf[100];
    MemoryStr retval;
    const unsigned int MB = (1024 * 1024);
    try{
        struct statvfs buffer;
        int ret = statvfs("/", &buffer);
        if (!ret) {
            const double total = (double)(buffer.f_blocks / MB)* buffer.f_frsize ;
            const double available = (double)(buffer.f_bfree * buffer.f_frsize) /MB;
            const double used = total - available;
            const double usedPercentage = (double)(used / total) * (double)100;
    //            printf("Total: %f --> %.0fMB\n", total, total);
    //            printf("Available: %f --> %.0fMB\n", available, available);
    //            printf("Used: %f --> %.1fMB\n", used, used);
    //            printf("Used Percentage: %f --> %.0f\n", usedPercentage, usedPercentage);
            sprintf(charbuf,"%.0fMB",total);
            retval.TotalSpace = std::string(charbuf);
            sprintf(charbuf,"%.0fMB",available);
            retval.AvailableSpace = std::string(charbuf);
            sprintf(charbuf,"%.1fMB | %.0f %%",used,usedPercentage);
            retval.UsedSpace = std::string(charbuf);
    }
    }
    catch(...){}
    return retval;
}
long long FileSystem::getFileSize(const char * filename){
    std::ifstream myfile (filename, std::ios::binary);
    try{
        std::streampos begin,end;

        begin = myfile.tellg();
        myfile.seekg (0, std::ios::end);
        end = myfile.tellg();
        myfile.close();
        //cout << "size is: " << (end-begin) << " bytes.\n";
        return end - begin;
    }
    catch(...){}
    myfile.close();
    return -1;
}
bool FileSystem::rename(const char *src,const char * dst){
    char buffer [1024];
    if(exist(src)){
        sprintf(buffer, "mv %s %s", src,dst);
        if (system(buffer) == 0)
            return true;
    }
    return false;
}
