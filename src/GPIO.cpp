#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <poll.h>
#include "GPIO.h"

using namespace std;

    GPIO::GPIO() {
        
    }

    GPIO::GPIO(std::string path){
        _path = path;
    }

    void GPIO::exportPin(std::string pin){
        std::ofstream fout;
        fout.open(std::string(_path+"/export").c_str(), std::ios::out);

        fout << pin;

        fout.close();
    }

    void GPIO::unexportPin(std::string pin){
        std::ofstream fout;
        fout.open(std::string(_path+"/unexport").c_str(), std::ios::out);

        fout << pin;

        fout.close();
    }

    void GPIO::setPinDirection(std::string pin, std::string dir){
        std::ofstream fout;
        std::stringstream ss;
        ss << _path+"/gpio" << pin << "/direction";
        fout.open(ss.str().c_str(), std::ios::out);

        fout << dir;

        fout.close();
    }

    void GPIO::setPinValue(std::string pin, std::string value){
        std::ofstream fout;
        std::stringstream ss;
        ss << _path+"/gpio" << pin << "/value";
        fout.open(ss.str().c_str(), std::ios::out);

        fout << value;

        fout.close();
    }

std::string GPIO::getPinValue(std::string pin){
        std::ifstream fin;
        std::stringstream ss;
        ss << _path+"/gpio" << pin << "/value";
        fin.open(ss.str().c_str(), std::ios::in);

        std::string val;
        fin >> val;

        fin.close();

        return val;
    }

    int GPIO::gpio_omap_mux_setup(std::string omap_pin_name){
        int fd;
        const char* mode = "gpio";
        std::string prefix = "/sys/devices/platform/ocp/ocp:";
        std::string suffix = "_pinmux/state";
        
	std::string c = prefix + omap_pin_name + suffix;
        const char* s = c.c_str();
        fd = open(s, O_WRONLY);
        if (fd < 0){
            perror("failed to open OMAP_MUX");
                    return fd;
        }
        write(fd, mode, strlen(mode) + 1);
        close(fd);
        return 0;
    }

