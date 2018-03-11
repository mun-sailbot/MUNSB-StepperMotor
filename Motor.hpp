/*
 *    List of Beaglebone pins for the motor drivers:
 *
 *    Rudder: I1      - Pin 29, GPIO_111/Pwm
 *            Step - Pin 18, GPIO_05
 *            Dir  - Pin 17, GPIO_04
 *            Hall Effect - Pin 27, GPIO_125
 *
 *      Mast: I1      - Pin 31, GPIO_110/Pwm
 *            Step - Pin 25, GPIO_117
 *            Dir  - Pin 40, GPIO_20
 *            Hall Effect - Pin 23, GPIO 49
 */

#ifndef Motor_hpp
#define Motor_hpp

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
    
    int gpio_DIR, gpio_PWM, gpio_STEP;
    int degrees;   // the number of degrees to turn (positive degrees = clockwise)
    int position;  //the position in degrees from the starting point
    int direction; // 1 for clockwise, 0 for counter clockwise
    bool clockwise;
    
protected:
    float speed;
    int stepsPerRevolution;
    int stepSize;
    
public:
    
    Motor(int gpio_DIR, int gpio_STEP, int gpio_PWM);   // constructor
    
    int getStepsPerRevolution() { return stepsPerRevolution; };
    
    /*!
     *    rotates a specific number of steps
     *
     *     sends a single pulse/step to the motor driver
     *
     *    @param           numberOfsteps    number of steps to rotate
     *                                        positive value = clockwise
     *                                        negative value = counterclockwise
     *
     *    @modifies       position           will add degrees turned (1.8 degrees/step)
     *
     */
    void step(int numberOfsteps);
    
    /*
     *    converts the clockwise flag to false
     *    reversing the direction of rotation
     *
     *    @modifies       clockwise    reverses direction
     *
     */
    void reverseDirection() { clockwise = !clockwise; }
    
    /*!
     *    rotates a specific number of degrees
     *
     *    converts this to number of steps (1.8 degrees/step)
     *    then sends a single pulse/step to the motor driver.
     *
     *    @param          degrees        positive value = clockwise
     *                                    negative value = counterclockwise
     *    @modifies       position    adds number of degrees rotated
     *
     *
     */
    void rotate(int degrees);
    
    
    /*!
     *    resets stepper motor to home
     *
     *    rotates the motor clockwise until it activates
     *    the hall effect sensor then adjusts to position
     *    zero from there if needed.
     *
     *    @modifies    int position
     *
     *    @returns    true if home position is established
     *
     */
    bool setStartPosition();
    
    
};
#endif /* Motor_hpp */
