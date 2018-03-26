/*
Daniel Cook 2013
daniel@daniel-cook.net
*/

#ifndef __PWM_H
#define __PWM_H
#define MAX_BUF 80
#define SYSFS_OMAP_MUX_DIR "/sys/devices/platform/ocp/ocp\\:"
#define OMAP_SUFFIX "_pinmux/state"
#define PWM_DIR "/sys/class/pwm/"


#include "Common.h"

    class PWM{
        private:
        std::string _path;
        std::string _pin;
        unsigned int _dutyPercent;

        public:
        PWM();
        PWM(PINS pin);

        void run();
        void stop();

        bool request();
        bool release();

        void setDutyCycle(int duty);
        void setPeriod(int period);

        float getDutyCycle();
        float getPeriod();

        bool isFree();
        int gpio_omap_mux_setup(const char *omap_pin0_name);
    };

#endif
