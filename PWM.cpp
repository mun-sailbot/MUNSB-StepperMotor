#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <poll.h>
#include "PWM.h"

    PWM::PWM(){
        _dutyPercent = 0;
    }

    PWM::PWM(PINS pin){
        _dutyPercent = 0;
        _pin = pin;
        switch (pin) {
            case P9_42:
                _path = PWM_P9_42;
                gpio_omap_mux_setup("/sys/devices/platform/ocp/ocp\\:P9_42_pinmux/state");
                break;
            case P9_22:
                _path = PWM_P9_22;
                gpio_omap_mux_setup("/sys/devices/platform/ocp/ocp\\:P9_22_pinmux/state");
                break;
            case P9_21:
                _path = PWM_P9_21;
                gpio_omap_mux_setup("/sys/devices/platform/ocp/ocp\\:P9_21_pinmux/state");
                break;
            case P9_14:
                _path = PWM_P9_14;
                gpio_omap_mux_setup("/sys/devices/platform/ocp/ocp\\:P9_14_pinmux/state");
                break;
            case P8_36:
                _path = PWM_P8_36;
                gpio_omap_mux_setup("/sys/devices/platform/ocp/ocp\\:P8_36_pinmux/state");
                break;
            case P9_16:
                _path = PWM_P9_16;
                gpio_omap_mux_setup("/sys/devices/platform/ocp/ocp\\:P9_16_pinmux/state");
                break;
            case P8_34:
                _path = PWM_P8_34;
                gpio_omap_mux_setup("/sys/devices/platform/ocp/ocp\\:P8_34_pinmux/state");
                break;
            case P8_19:
                _path = PWM_P8_19;
                gpio_omap_mux_setup("/sys/devices/platform/ocp/ocp\\:P8_19_pinmux/state");
                break;
            case P8_45:
                _path = PWM_P8_45;
                gpio_omap_mux_setup("/sys/devices/platform/ocp/ocp\\:P8_45_pinmux/state");
                break;
            case P8_13:
                _path = PWM_P8_13;
                gpio_omap_mux_setup("/sys/devices/platform/ocp/ocp\\:P8_13_pinmux/state");
                break;
            case P8_46:
                _path = PWM_P8_46;
                gpio_omap_mux_setup("/sys/devices/platform/ocp/ocp\\:P8_46_pinmux/state");
                break;
            default:
                break;
        }
        request();
    }

    void PWM::run(){
        std::ofstream fout;
        fout.open(std::string(_path+"/enable").c_str(), std::ios::out);

        fout << 1;

        fout.close();

        if(!_dutyPercent)
            std::cout << "Warning: duty_percent = 0" << std::endl;
    }

    void PWM::stop(){
        std::ofstream fout;
        fout.open(std::string(_path+"/enable").c_str(), std::ios::out);

        fout << 0;

        fout.close();
    }

    bool PWM::request(){
        if(isFree()){
            std::ofstream fout;
            fout.open(std::string(_path+"/export").c_str(), std::ios::out);

            fout << 0;
            
            fout.close();

            return true;
        }
        else
            return false;
    }

    bool PWM::release(){
        if(!isFree()){
            std::ofstream fout;
            fout.open(std::string(_path+"/export").c_str(), std::ios::out);

            fout << 0;

            fout.close();

            return true;
        }
        else
            return false;
    }

    void PWM::setDutyCycle(int duty){
        std::ofstream fout;
        fout.open(std::string(_path+"/duty_cycle").c_str(), std::ios::out);

        fout << duty;
        _dutyPercent = duty;

        fout.close();
    }

    void PWM::setPeriod(int period){
        std::ofstream fout;
        fout.open(std::string(_path+"/period").c_str(), std::ios::out);

        fout << period;

        fout.close();
    }

    float PWM::getDutyCycle(){
        std::ifstream fin(std::string(_path+"/duty_cycle").c_str(), std::ios::in);

        float ret;
        fin >> ret;

        fin.close();
        return ret;
    }

    float PWM::getPeriod(){
        std::ifstream fin(std::string(_path+"/period").c_str(), std::ios::in);

        float ret;
        fin >> ret;

        fin.close();
        return ret;
    }

    bool PWM::isFree(){
        std::ifstream fin;
        fin.open(std::string(_path+"/export").c_str(), std::ios::in);

        char line[64];
        fin.getline(line, 64);
        std::string status = std::string(line);

        fin.close();

        if(status.find("free") != std::string::npos)
            return true;
        else
            return false;
    }

    int PWM::gpio_omap_mux_setup(const char* omap_pin_name){
        int fd;
        const char *mode = "pwm";
        const char* prefix = "/sys/devices/platform/ocp/ocp:";
        const char* suffix = "_pinmux/state";
        const char* p = new char [strlen(prefix)+strlen(omap_pin_name)+strlen(suffix)+5];
        const char* s = new char [strlen(prefix)+strlen(omap_pin_name)+strlen(suffix)+5];
        strcat(const_cast<char*>(p),prefix);
        strcat(const_cast<char*>(p),omap_pin_name);
        strcat(const_cast<char*>(p),suffix);
        strcpy(const_cast<char*>(s),p);
        cout << s << endl;
        fd = open(s, O_WRONLY);
        if (fd < 0){
            perror("failed to open OMAP_MUX");
                    return fd;
        }
        write(fd, mode, strlen(mode) + 1);
        close(fd);
        return 0;
    }
    