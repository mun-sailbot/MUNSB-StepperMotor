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

    void GPIO::setPinValue(std::string pin, unsigned int value){
        std::ofstream fout;
        std::stringstream ss;
        ss << _path+"/gpio" << pin << "/value";
        fout.open(ss.str().c_str(), std::ios::out);

        fout << value;

        fout.close();
    }

unsigned int GPIO::getPinValue(std::string pin){
        std::ifstream fin;
        std::stringstream ss;
        ss << _path+"/gpio" << pin << "/value";
        fin.open(ss.str().c_str(), std::ios::in);

        unsigned int val;
        fin >> val;

        fin.close();

        return val;
    }

    int GPIO::gpio_omap_mux_setup(const char *omap_pin0_name){
        int fd;
        const char *mode = "gpio";
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

