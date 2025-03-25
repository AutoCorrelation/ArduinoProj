#ifndef DC_MOTOR_DRIVER_H
#define DC_MOTOR_DRIVER_H

#include "AbstractDevice.h"

class DCMotorDriver : public AbstractDevice {
public:
    void initialize() override;
    void update() override;
    void setSpeed(int speed);
};

#endif