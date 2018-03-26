/*
Daniel Cook 2013
daniel@daniel-cook.net
*/

#ifndef __PWM_H
#define __PWM_H
#define MAX_BUF 80
#define SYSFS_OMAP_MUX_DIR "/sys/devices/platform/ocp/ocp\\:"
#define OMAP_SUFFIX "_pinmux/state"

#include "Common.h"

    class PWM{
        private:
        std::string _path;
        unsigned int _dutyPercent;

        public:
        PWM();
        PWM(std::string path);

        void run();
        void stop();

        bool request();
        bool release();

        void setDutyPercent(float percent);
        void setPeriodFreq(float freq);
        void setPeriodFreqWithDutyPercent(float freq, float percent);

        float getDutyPercent();
        float getPeriodFreq();

        bool isFree();
        int gpio_omap_mux_setup(const char *omap_pin0_name, const char *mode);
    };

#endif
