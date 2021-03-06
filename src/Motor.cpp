#include "Motor.h"
#include <iostream>
#include <unistd.h>
#include "Common.h"

using namespace std;

Motor::Motor(std::string gpio_DIR, std::string gpio_STEP, PINS gpio_PWM) {

    clockwise = true;
    stepsPerRevolution = 200;
    stepSize = 1.8;
    
    PWM pwm(gpio_PWM);  // sets up PWM pin
    
	this->gpio_STEP = gpio_STEP;
	this->gpio_DIR  = gpio_DIR;
    
    gpio.gpio_omap_mux_setup(gpio_STEP);
    
    gpio.gpio_omap_mux_setup(gpio_DIR);
    
    pwm.setPeriod(100000);
    pwm.setDutyCycle(19600);
	gpio.exportPin(this->gpio_STEP);
	gpio.setPinDirection(this->gpio_STEP, "out");
	gpio.exportPin(this->gpio_DIR);
	gpio.setPinDirection(this->gpio_DIR, "out");

}

void Motor::rotate(int degrees){
    float degreesPerStep = 360.0f/getStepsPerRevolution();
    int numberOfSteps = degrees/degreesPerStep;
    step(numberOfSteps);
}

void Motor::step(int numberOfSteps){
    if(numberOfSteps>=0) {
        if(clockwise) gpio.setPinValue(this->gpio_DIR, "0");
        else gpio.setPinValue(this->gpio_DIR, "1");
        for(int i=0; i<numberOfSteps; i++){
            gpio.setPinValue(this->gpio_STEP, "0");
            gpio.setPinValue(this->gpio_STEP, "1");
        }
    }
    else { // going in reverse (numberOfSteps is negative)
        if(clockwise) gpio.setPinValue(this->gpio_DIR, "1");
        else gpio.setPinValue(this->gpio_DIR, "0");
        for(int i=numberOfSteps; i<=0; i++){
            gpio.setPinValue(this->gpio_STEP, "0");
            gpio.setPinValue(this->gpio_STEP, "1");
        }
    }
}

bool Motor::setStartPosition()
{
    return true;
}
