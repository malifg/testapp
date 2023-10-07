#include "hardwarecontroller.h"

HardwareController::HardwareController()
{
}

int HardwareController::gpioExport(unsigned int gpio)
{
    int fd, len;
    char buf[MAX_BUF];

    fd = open(SYSFS_GPIO_DIR "/export", O_WRONLY);
    if (fd < 0) {
        perror("gpio/export");
        return fd;
    }

    len = snprintf(buf, sizeof(buf), "%d", gpio);
    write(fd, buf, len);
    close(fd);

    return 0;
}


int HardwareController::gpioUnexport(unsigned int gpio)
{
    int fd, len;
    char buf[MAX_BUF];

    fd = open(SYSFS_GPIO_DIR "/unexport", O_WRONLY);
    if (fd < 0) {
        perror("gpio/export");
        return fd;
    }

    len = snprintf(buf, sizeof(buf), "%d", gpio);
    write(fd, buf, len);
    close(fd);
    return 0;
}

int HardwareController::checkIfExported(unsigned int gpio)
{

    int fd/*, len*/;
    char buf[MAX_BUF];

    snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR  "/gpio%d/direction", gpio);

    fd = open(buf, O_WRONLY);
    if (fd < 0) {
        close(fd);
        return fd;
    }
    else
    {
        close(fd);
        return 0;
    }
}

int HardwareController::gpioSetDir(unsigned int gpio, unsigned int out_flag)
{
    int fd/*, len*/;
    char buf[MAX_BUF];

    snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR  "/gpio%d/direction", gpio);

    fd = open(buf, O_WRONLY);
    if (fd < 0) {
        perror("gpio/direction");
        return fd;
    }

    if (out_flag)
        write(fd, "out", 4);
    else
        write(fd, "in", 3);

    close(fd);
    return 0;
}



int HardwareController::gpioSetValue(unsigned int gpio, unsigned int value)
{
    int fd/*, len*/;
    char buf[MAX_BUF];

    snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/value", gpio);

    fd = open(buf, O_WRONLY);
    if (fd < 0) {
        perror("gpio/set-value");
        return fd;
    }

    if (value)
        write(fd, "1", 2);
    else
        write(fd, "0", 2);

    close(fd);
    return 0;
}



int HardwareController::gpioGetValue(unsigned int gpio, unsigned int *value)
{
    int fd/*, len*/;
    char buf[MAX_BUF];
    char ch;

    snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/value", gpio);

    fd = open(buf, O_RDONLY);
    if (fd < 0) {
        perror("gpio/get-value");
        return fd;
    }

    read(fd, &ch, 1);

    if (ch != '0') {
        *value = 1;
    } else {
        *value = 0;
    }

    close(fd);
    return 0;
}


int HardwareController::DO_setValue(int pinNumber, bool value)
{
    if(checkIfExported(pinNumber))
    {
        gpioExport(pinNumber);
    }
    if(!gpioSetDir(pinNumber, 1))
    {
      if(value == true)
      {
        if(!gpioSetValue(pinNumber, 1))
            return 0;
        else
            return -1;
      }
      else
      {
        if(!gpioSetValue(pinNumber, 0))
            return 0;
        else
            return -1;
      }
    }
    else
      return -1;

    return 0;
}

int HardwareController::DI_getValue(int pinNumber)
{
    unsigned int get_val;
    if(checkIfExported(pinNumber))
    {
        gpioExport(pinNumber);
    }
    if(!gpioSetDir(pinNumber, 0))
    {
        if(!gpioGetValue(pinNumber, &get_val))
        {
            if (get_val < 0)
                return -1;
            else
                return get_val;
        }
        else
            return -1;
    }
}





std::string HardwareController::executeCommand(std::string cmd){
    system((cmd + " > temp.txt").c_str());

    std::ifstream ifs("temp.txt");
    std::string ret{ std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>() };
    ifs.close(); // must close the inout stream so the file can be cleaned up
    if (std::remove("temp.txt") != 0) {
        perror("Error deleting temporary file");
    }
    return ret;
}







