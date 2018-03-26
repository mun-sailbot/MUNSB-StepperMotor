
#ifndef __GPIO_H
#define __GPIO_H
#define SYSFS_GPIO_DIR "/sys/class/gpio"
#define POLL_TIMEOUT (3 * 1000) /* 3 seconds */
#define MAX_BUF 80
#define SYSFS_OMAP_MUX_DIR "/sys/devices/platform/ocp/ocp\\:"
#define OMAP_SUFFIX "_pinmux/state"

#include "Common.h"

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
        GPIO();
        GPIO(std::string path);

        void exportPin(std::string pin);
        void unexportPin(std::string pin);

        void setPinDirection(std::string pin, std::string dir);
        void setPinValue(std::string pin, unsigned int value);

        unsigned int getPinValue(std::string pin);
        int gpio_omap_mux_setup(const char *omap_pin0_name, const char *mode);
    };


#endif
