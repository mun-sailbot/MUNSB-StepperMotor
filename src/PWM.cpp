#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <poll.h>
#include "PWM.h"

    PWM::PWM(){
        _dutycycle = 0;
    }

    PWM::PWM(PINS pin){
        _dutyPercent = 0;
        _pin = pin;
        switch (pin) {
            case P9_42:
                _path = PWM_P9_42;
                _sub = "pwm0";
                gpio_omap_mux_setup("P9_42");
                break;
            case P9_22:
                _path = PWM_P9_22;
                _sub = "pwm0";
                gpio_omap_mux_setup("P9_22");
                break;
            case P9_21:
                _path = PWM_P9_21;
                _sub = "pwm1";
                gpio_omap_mux_setup("P9_21");
                break;
            case P9_14:
                _path = PWM_P9_14;
                _sub = "pwm0";
                gpio_omap_mux_setup("P9_14");
                break;
            case P8_36:
                _path = PWM_P8_36;
                _sub = "pwm0";
                gpio_omap_mux_setup("P8_36");
                break;
            case P9_16:
                _path = PWM_P9_16;
                _sub = "pwm1";
                gpio_omap_mux_setup("P9_16");
                break;
            case P8_34:
                _path = PWM_P8_34;
                _sub = "pwm1";
                gpio_omap_mux_setup("P8_34");
                break;
            case P8_19:
                _path = PWM_P8_19;
                _sub = "pwm0";
                gpio_omap_mux_setup("P8_19");
                break;
            case P8_45:
                _path = PWM_P8_45;
                _sub = "pwm0";
                gpio_omap_mux_setup("P8_45");
                break;
            case P8_13:
                _path = PWM_P8_13;
                _sub = "pwm1";
                gpio_omap_mux_setup("P8_13");
                break;
            case P8_46:
                _path = PWM_P8_46;
                _sub = "pwm1";
                gpio_omap_mux_setup("P8_46");
                break;
            default:
                break;
        }
        request();
    }

    void PWM::run(){
        std::ofstream fout;
        fout.open(std::string(this->getPath()+"/"+this->getSub()+"/enable").c_str(), std::ios::out);
        fout << 1;
        fout.close();

        if(!_dutycycle)
            std::cout << "Warning: duty cycle = 0" << std::endl;
    }

    void PWM::stop(){
        std::ofstream fout;
        fout.open(std::string(this->getPath()+"/"+this->getSub()+"/enable").c_str(), std::ios::out);

        fout << 0;

        fout.close();
    }

    // pwm0 or pwm1?
    bool PWM::request(){
            std::ofstream fout;
            fout.open(std::string(this->getPath()+"/export").c_str(), std::ios::out);

            if (this->getSub() == "pwm0"){
                fout << 0;
            }
            else {
                fout << 1;
            }
            
            fout.close();
    }

    bool PWM::release(){
        if(!isFree()){
            std::ofstream fout;
            fout.open(std::string(this->getPath()+"/unexport").c_str(), std::ios::out);

            fout << 0;

            fout.close();

            return true;
        }
        else
            return false;
    }

    void PWM::setDutyCycle(int duty){
        std::ofstream fout;
        fout.open(std::string(this->getPath()+"/"+this->getSub()+"/duty_cycle").c_str(), std::ios::out);

        fout << duty;
        _dutycycle = duty;

        fout.close();
    }

    void PWM::setPeriod(int period){
        std::ofstream fout;
        fout.open(std::string(this->getPath()+"/"+this->getSub()+"/period").c_str(), std::ios::out);

        fout << period;

        fout.close();
    }

    float PWM::getDutyCycle(){
        std::ifstream fin(std::string(this->getPath()+"/"+this->getSub()+"/duty_cycle").c_str(), std::ios::in);

        float ret;
        fin >> ret;

        fin.close();
        return ret;
    }

    float PWM::getPeriod(){
        std::ifstream fin(std::string(this->getPath()+"/"+this->getSub()+"/period").c_str(), std::ios::in);

        float ret;
        fin >> ret;

        fin.close();
        return ret;
    }

    bool PWM::isFree(){
        std::ifstream fin;
        fin.open(std::string(this->getPath()+"/export").c_str(), std::ios::in);

        char line[64];
        fin.getline(line, 64);
        std::string status = std::string(line);

        fin.close();

        if(status.find("free") != std::string::npos)
            return true;
        else
            return false;
    }

    std::string PWM::getPath(){
        return this->_path;
    }

    std::string PWM::getSub(){
        return this->_sub;
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
    
