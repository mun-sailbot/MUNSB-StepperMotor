
#include "GPIO.h"

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

    int GPIO::gpio_omap_mux_setup(const char *omap_pin0_name, const char *mode){
        int fd;
        char buf[MAX_BUF];
        snprintf(buf, sizeof(buf), SYSFS_OMAP_MUX_DIR "%s" "%s", omap_pin0_name, OMAP_SUFFIX);
        fd = open(buf, O_WRONLY);
        if (fd < 0) {
            perror("failed to open OMAP_MUX");
            return fd;
        }
        write(fd, mode, strlen(mode) + 1);
        close(fd);
        return 0;
    }

