#ifndef _ROTARYENCODER_H_
#define _ROTARYENCODER_H_

#include "Config.h"
#include <Arduino.h>

class RotaryEncoder
{
    private:
        int _count = 0;
        bool _buttonPressed = false;
        int _pinA = 0;
        int _pinB = 0;

        void RotationISR();
        void buttonPressed();
    public:
        RotaryEncoder();
        void RotaryEncoderInit();
        void resetRotationCount();
        int getRotationCount();
        bool isButtonPressed();

        // Static instance pointer for ISR context
        static RotaryEncoder* instance;

        // Static ISR wrappers
        static void isrRotationWrapper();
        static void buttonPressedWrapper();
};

#endif