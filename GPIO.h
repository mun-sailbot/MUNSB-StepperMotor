
#ifndef __GPIO_H
#define __GPIO_H
#define SYSFS_GPIO_DIR "/sys/class/gpio"
#define POLL_TIMEOUT (3 * 1000) /* 3 seconds */
#define MAX_BUF 80
#define SYSFS_OMAP_MUX_DIR "/sys/devices/platform/ocp/ocp\:"
#define OMAP_SUFFIX "_pinmux/state"

#include "Common.h"


namespace BeagleUtil
{

enum PIN_DIRECTION{
	INPUT_PIN=0,
	OUTPUT_PIN=1
};

enum PIN_VALUE{
	LOW=0,
	HIGH=1
};

    class GPIO{
        private:
        std::string _path;

        public:
        GPIO(std::string path);

        void exportPin(unsigned int pin);
        void unexportPin(unsigned int pin);

        void setPinDirection(unsigned int pin, std::string dir);
        void setPinValue(unsigned int pin, unsigned int value);

        unsigned int getPinValue(unsigned int pin);
    };

}

#endif