//
//  Motor.cpp
//  Motor
//
//  Created by Bryan Melanson on 2018-03-11.
//  Copyright © 2018 Bryan Melanson. All rights reserved.
//

#include "Motor.hpp"
#include <iostream>
#include <unistd.h>
using namespace std;

Motor::Motor(std::string gpio_DIR, std::string gpio_STEP, std::string gpio_PWM) {

    clockwise = true;
    stepsPerRevolution = 200;
    stepSize = 1.8;

    this->gpio_PWM  = gpio_PWM.c_str();
	this->gpio_STEP = gpio_STEP.c_str();
	this->gpio_DIR  = gpio_DIR.c_str();
    
    gpio.gpio_omap_mux_setup(gpio_PWM.c_str(), "pwm");
    
    gpio.gpio_omap_mux_setup(gpio_STEP.c_str(), "gpio");
    
    gpio.gpio_omap_mux_setup(gpio_DIR.c_str(), "gpio");
    
    gpio.exportPin(this->gpio_PWM);
	
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
        if(clockwise) gpio.setPinValue(this->gpio_DIR, LOW);
        else gpio.setPinValue(this->gpio_DIR, HIGH);
        for(int i=0; i<numberOfSteps; i++){
            gpio.setPinValue(this->gpio_STEP, LOW);
            gpio.setPinValue(this->gpio_STEP, HIGH);
        }
    }
    else { // going in reverse (numberOfSteps is negative)
        if(clockwise) gpio.setPinValue(this->gpio_DIR, HIGH);
        else gpio.setPinValue(this->gpio_DIR, LOW);
        for(int i=numberOfSteps; i<=0; i++){
            gpio.setPinValue(this->gpio_STEP, LOW);
            gpio.setPinValue(this->gpio_STEP, HIGH);
        }
    }
}

bool Motor::setStartPosition()
{
    return true;
}
