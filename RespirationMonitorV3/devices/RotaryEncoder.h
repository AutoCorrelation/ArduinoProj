#ifndef _ROTARY_ENCODER_H_
#define _ROTARY_ENCODER_H_

#include <Arduino.h>
#include "config/Config.h"

class RotaryEncoder
{
private:
    int _counter = 0;
public:
    RotaryEncoder(); // Constructor
    ~RotaryEncoder(); // Destructor

    void init();
    void shifting(); // Interrupt function for encoder rotation
    void selecting(); // Interrupt function for button press



};
#endif
