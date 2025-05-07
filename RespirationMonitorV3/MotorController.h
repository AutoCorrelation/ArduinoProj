#ifndef MOTORCONTROLLER_H
#define MOTORCONTROLLER_H

#include <Arduino.h>

class MotorController {
public:
    // define the motor pins (could be parameters in a constructor as well)
    const int motorA1 = 10;
    const int motorA2 = 11;
    const int motorB1 = 12;
    const int motorB2 = 13;

    MotorController();
    void init();
    void run();
    void stop();
};

#endif