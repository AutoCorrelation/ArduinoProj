#include "RotaryEncoder.h"

RotaryEncoder::RotaryEncoder()
{
    // Constructor implementation (if needed)
}

RotaryEncoder::~RotaryEncoder()
{
    // Destructor implementation (if needed)
}

void RotaryEncoder::init()
{
    pinMode(ENCODER_PIN_A, INPUT);
    pinMode(ENCODER_PIN_B, INPUT);
    pinMode(ENCODER_BUTTON_PIN, INPUT);

    

}