/*
Daniel Cook 2013
daniel@daniel-cook.net
*/

#include "PWM.h"

    PWM(std::string path){
        _path = path;
        _dutyPercent = 0;
    }

    void run(){
        std::ofstream fout;
        fout.open(std::string(_path+"/enable").c_str(), std::ios::out);

        fout << 1;

        fout.close();

        if(!_dutyPercent)
            std::cout << "Warning: duty_percent = 0" << std::endl;
    }

    void stop(){
        std::ofstream fout;
        fout.open(std::string(_path+"/enable").c_str(), std::ios::out);

        fout << 0;

        fout.close();
    }

    bool request(){
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

    bool release(){
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

    void setDutyPercent(float percent){
        std::ofstream fout;
        fout.open(std::string(_path+"/duty_percent").c_str(), std::ios::out);

        fout << percent;
        _dutyPercent = percent;

        fout.close();
    }

    void setPeriodFreq(float freq){
        setDutyPercent(0);

        std::ofstream fout;
        fout.open(std::string(_path+"/period_freq").c_str(), std::ios::out);

        fout << freq;

        fout.close();
    }

    void setPeriodFreqWithDutyPercent(float freq, float percent){
        setPeriodFreq(freq);
        setDutyPercent(percent);
    }

    float getDutyPercent(){
        std::ifstream fin(std::string(_path+"/duty_percent").c_str(), std::ios::in);

        float ret;
        fin >> ret;

        fin.close();
        return ret;
    }

    float getPeriodFreq(){
        std::ifstream fin(std::string(_path+"/period_freq").c_str(), std::ios::in);

        float ret;
        fin >> ret;

        fin.close();
        return ret;
    }

    bool isFree(){
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
