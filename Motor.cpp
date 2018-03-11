//
//  Motor.cpp
//  Motor
//
//  Created by Bryan Melanson on 2018-03-11.
//  Copyright © 2018 Bryan Melanson. All rights reserved.
//

#include "Motor.hpp"

Motor::Motor(int gpio_DIR, int gpio_STEP, int gpio_PWM) {

    clockwise = true;
    stepsPerRevolution = 200;
    stepSize = 1.8;
    
    this->gpio_DIR = gpio_DIR;
    this->gpio_STEP = gpio_STEP;
    this->gpio_PWM = gpio_PWM;
    
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
