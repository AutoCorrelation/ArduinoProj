#ifndef I2C_SENSOR_H
#define I2C_SENSOR_H

#include "AbstractDevice.h"

class I2CSensor : public AbstractDevice {
public:
    void initialize() override;
    void update() override;
    float readValue();
};

#endif