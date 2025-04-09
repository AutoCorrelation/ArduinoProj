#ifndef I2C_SENSOR_H
#define I2C_SENSOR_H

#include "AbstractDevice.h"
#include <DFRobot_OxygenSensor.h>
#include <SparkFun_STC3x_Arduino_Library.h>
#include <Adafruit_GFX.h>     // Adafruit graphics library
#include <Adafruit_SSD1306.h>

class I2CSensor : public AbstractDevice {
public:
    void initialize() override;
    void update() override;
    float readValue();
};

#endif