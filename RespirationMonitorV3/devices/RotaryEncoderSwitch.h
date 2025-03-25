#ifndef ROTARY_ENCODER_SWITCH_H
#define ROTARY_ENCODER_SWITCH_H

#include "AbstractDevice.h"

class RotaryEncoderSwitch : public AbstractDevice {
public:
    void initialize() override;
    void update() override;
    int getPosition();
    bool isButtonPressed();
};

#endif