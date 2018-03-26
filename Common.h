
#ifndef __COMMON_H
#define __COMMON_H

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <fcntl.h>
#include <termios.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdint.h>

    const std::string GPIO_DEFAULT_PATH = "/sys/class/gpio";

    const std::string PWM_P9_42 = "/sys/class/pwm/pwmchip0/pwm0";

    const std::string PWM_P9_22 = "/sys/class/pwm/pwmchip1/pwm0";
    //const std::string PWM_P9_31 = "/sys/class/pwm/pwmchip1/pwm0";

    const std::string PWM_P9_21 = "/sys/class/pwm/pwmchip1/pwm1";
    //const std::string PWM_P9_29 = "/sys/class/pwm/pwmchip1/pwm1";

    const std::string PWM_P9_14 = "/sys/class/pwm/pwmchip3/pwm0";
    const std::string PWM_P8_36 = "/sys/class/pwm/pwmchip3/pwm0";

    const std::string PWM_P9_16 = "/sys/class/pwm/pwmchip3/pwm1";
    const std::string PWM_P8_34 = "/sys/class/pwm/pwmchip3/pwm1";

    //const std::string PWM_P9_28 = "/sys/class/pwm/pwmchip5/pwm0";

    const std::string PWM_P8_19 = "/sys/class/pwm/pwmchip6/pwm0";
    const std::string PWM_P8_45 = "/sys/class/pwm/pwmchip6/pwm0";

    const std::string PWM_P8_13 = "/sys/class/pwm/pwmchip6/pwm1";
    const std::string PWM_P8_46 = "/sys/class/pwm/pwmchip6/pwm1";

    typedef enum{
        UART1,
        UART2,
        UART4,
        UART5
    } UART_PORT;

    typedef enum{
        P9_42,
        P9_22,
        P9_21,
        P9_14,
        P8_36,
        P9_16,
        P8_34,
        P8_19,
        P8_45,
        P8_13,
        P8_46
    } PINS;

    const std::string I2C_1 = "/dev/i2c-1";
    const std::string I2C_3 = "/dev/i2c-3";

    const std::string AIN_0 = "/sys/devices/platform/tsc/ain1";
    const std::string AIN_1 = "/sys/devices/platform/tsc/ain2";
    const std::string AIN_2 = "/sys/devices/platform/tsc/ain3";
    const std::string AIN_3 = "/sys/devices/platform/tsc/ain4";
    const std::string AIN_4 = "/sys/devices/platform/tsc/ain5";
    const std::string AIN_5 = "/sys/devices/platform/tsc/ain6";

    const short int UART_USE_PIN = 0x8000;
    const short int UART_SLOW = 0x0040;
    const short int UART_INPUT = 0x0020;

#endif
