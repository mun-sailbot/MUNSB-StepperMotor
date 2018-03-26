/*
 *    List of Beaglebone pins for the motor drivers:
 *
 *    Rudder: I1      - Pin 14, GPIO_40/Pwm
 *            Step - Pin 19, GPIO_13
 *            Dir  - Pin 17, GPIO_04
 *            Hall Effect - Pin 27, GPIO_125
 *
 *      Mast: I1      - Pin 42, GPIO_20/Pwm
 *            Step - Pin 25, GPIO_117
 *            Dir  - Pin 41, GPIO_20
 *            Hall Effect - Pin 23, GPIO 49
 */

#ifndef Motor_hpp
#define Motor_hpp

#include "GPIO.h"
#include "PWM.h"
#include <string>
#include <stdio.h>

const std::string RUDDER_PWM = "GPIO_111";
const std::string RUDDER_STEP = "GPIO_05";
const std::string RUDDER_DIR = "GPIO_04";
const std::string RUDDER_HALL = "GPIO_125";
const std::string MAST_PWM = "GPIO_110";
const std::string MAST_STEP = "GPIO_117";
const std::string MAST_DIR = "GPIO_20";
const std::string MAST_HALL = "GPIO_49";

class Motor
{
    
private:
    
    GPIO gpio;
    PWM pwm;

    std::string gpio_PWM, gpio_DIR, gpio_STEP;
    int degrees;   // the number of degrees to turn (positive degrees = clockwise)
    int position;  //the position in degrees from the starting point
    int direction; // 1 for clockwise, 0 for counter clockwise
    bool clockwise;
    
protected:
    float speed;
    int stepsPerRevolution;
    int stepSize;
    
public:
    
    Motor(std::string gpio_DIR, std::string gpio_STEP, PINS gpio_PWM);
    
    
    int getStepsPerRevolution() { return stepsPerRevolution; };
    
   
    void step(int numberOfsteps);
    
   
    void reverseDirection() { clockwise = !clockwise; }
    
   
    void rotate(int degrees);
    
    
    bool setStartPosition();
    
    
};
#endif /* Motor_hpp */
