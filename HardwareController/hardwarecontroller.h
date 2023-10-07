#ifndef HARDWARECONTROLLER_H
#define HARDWARECONTROLLER_H

#include "Utilities/common.h"
#include "Utilities/singleton.h"
#include "Utilities/constants.h"
#include "Utilities/Logger.h"


#define SYSFS_GPIO_DIR          "/sys/class/gpio"
#define ADC_DIR                 "/sys/bus/iio/devices/iio:device0"
#define PWM_DIR                 "/sys/devices/platform/pwm"


class HardwareController : public Singleton<HardwareController>
{
private:
    int gpioExport(unsigned int gpio);
    int checkIfExported(unsigned int gpio);
    int gpioSetDir(unsigned int gpio, unsigned int out_flag);
    int gpioSetValue(unsigned int gpio, unsigned int value);
    int gpioGetValue(unsigned int gpio, unsigned int *value);


public:
    HardwareController();
    int DO_setValue(int pinNumber, bool value);
    int DI_getValue(int pinNumber);
    int gpioUnexport(unsigned int gpio);
    std::string executeCommand(std::string cmd);
    int setTtyAttribs(int fd, int baudrate);
};

#endif // HARDWARECONTROLLER_H
