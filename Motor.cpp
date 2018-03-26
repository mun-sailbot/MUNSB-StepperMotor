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

Motor::Motor(int gpio_DIR, int gpio_STEP, int gpio_PWM) {

    clockwise = true;
    stepsPerRevolution = 200;
    stepSize = 1.8;

    this->gpio_PWM  = gpio_PWM;
	this->gpio_STEP = gpio_STEP;
	this->gpio_DIR  = gpio_DIR;

    BeagleUtil::GPIO gpio("/sys/class/gpio/");
    
    exportPin(this->gpio_PWM);
	setPinDirection(this->gpio_PWM, OUTPUT_PIN);
	exportPin(this->gpio_STEP);
	setPinDirection(this->gpio_STEP, OUTPUT_PIN);
	exportPin(this->gpio_DIR);
	setPinDirection(this->gpio_DIR, OUTPUT_PIN);

}

void Motor::rotate(int degrees){
    float degreesPerStep = 360.0f/getStepsPerRevolution();
    int numberOfSteps = degrees/degreesPerStep;
    step(numberOfSteps);
}

void Motor::step(int numberOfSteps)
{
    
}

bool Motor::setStartPosition()
{
    return true;
}
