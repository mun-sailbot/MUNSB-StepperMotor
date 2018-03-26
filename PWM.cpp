/*
Daniel Cook 2013
daniel@daniel-cook.net
*/

#include "PWM.h"

    PWM::PWM(){
        _dutyPercent = 0;
    }

    PWM::PWM(std::string path){
        _path = path;
        _dutyPercent = 0;
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
            fout.open(std::string(_path+"/request").c_str(), std::ios::out);

            fout << 1;

            fout.close();

            return true;
        }
        else
            return false;
    }

    bool PWM::release(){
        if(!isFree()){
            std::ofstream fout;
            fout.open(std::string(_path+"/request").c_str(), std::ios::out);

            fout << 0;

            fout.close();

            return true;
        }
        else
            return false;
    }

    void PWM::setDutyPercent(float percent){
        std::ofstream fout;
        fout.open(std::string(_path+"/duty_percent").c_str(), std::ios::out);

        fout << percent;
        _dutyPercent = percent;

        fout.close();
    }

    void PWM::setPeriodFreq(float freq){
        setDutyPercent(0);

        std::ofstream fout;
        fout.open(std::string(_path+"/period_freq").c_str(), std::ios::out);

        fout << freq;

        fout.close();
    }

    void PWM::setPeriodFreqWithDutyPercent(float freq, float percent){
        setPeriodFreq(freq);
        setDutyPercent(percent);
    }

    float PWM::getDutyPercent(){
        std::ifstream fin(std::string(_path+"/duty_percent").c_str(), std::ios::in);

        float ret;
        fin >> ret;

        fin.close();
        return ret;
    }

    float PWM::getPeriodFreq(){
        std::ifstream fin(std::string(_path+"/period_freq").c_str(), std::ios::in);

        float ret;
        fin >> ret;

        fin.close();
        return ret;
    }

    bool PWM::isFree(){
        std::ifstream fin;
        fin.open(std::string(_path+"/request").c_str(), std::ios::in);

        //std::string ret1, ret2, ret3;
        //fin >> ret1 >> ret2 >> ret3;
        char line[64];
        fin.getline(line, 64);
        std::string status = std::string(line);

        fin.close();

        //std::string status = ret1+ret2+ret3;

        if(status.find("free") != std::string::npos)
            return true;
        else
            return false;
    }

    int PWM::gpio_omap_mux_setup(const char *omap_pin0_name, const char *mode){
        int fd;
        char buf[80];
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
