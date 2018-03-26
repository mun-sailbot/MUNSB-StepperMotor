
#include <iostream>
#include <string>
#include <unistd.h>
#include "GPIO.h"
#include "PWM.h"
#include "Common.h"
#include "Motor.hpp"
using namespace std;


void stepperMotorTest(){
    // GPIO Dir, GPIO Step, GPIO PWM
    
    Motor motor1("P9_41", "P9_25", P9_42);    // Mast
    Motor motor2("P9_17", "P9_19", P9_14);    // Rudder
    
    cout << "*** Start of Motor Test" << endl;
    cout << "*** Rotating - Forward 360 degrees" << endl;
    motor1.rotate(360);
    sleep(1);
    
    cout << "*** Rotating - Reverse 360 degrees" << endl;
    motor1.reverseDirection();
    motor1.rotate(360);
    sleep(1);
    
    cout << "*** Rotating - Forward 360 degrees" << endl;
    motor1.reverseDirection();
    motor1.rotate(360);
    sleep(1);
    
    cout << "*** Rotating - Reverse 360 degrees" << endl;
    motor1.rotate(-360);

}


int main(int argc, char *argv[]){
    
    stepperMotorTest();
    
    return 0;
}


