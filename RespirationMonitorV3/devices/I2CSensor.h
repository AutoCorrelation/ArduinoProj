#ifndef I2C_SENSOR_H
#define I2C_SENSOR_H

#include "AbstractDevice.h"
#include "lib/DFRobot_OxygenSensor.h"
#include "lib/SparkFun_STC3x_Arduino_Library.h"
#include "lib/Adafruit_GFX.h"
#include "lib/Adafruit_SSD1306.h"

class I2CSensor : public AbstractDevice {
private:
    Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET); // OLED display object
    DFRobot_OxygenSensor oxygen; // Oxygen sensor object
    STC3x co2; // CO2 sensor object
    float _oxygenConcentration;        // Stores oxygen concentration value
    float _co2Concentration;           // Stores CO2 concentration value
    float _breathingRate;              // Stores calculated breathing rate
    float _oxygenOffset;               // Calibration offset for oxygen sensor
    float _carbsRate;                  // Carbohydrate metabolism rate
    float _fatsRate;                   // Fat metabolism rate
public:
    void initialize() override;
    void update() override;
    float readValue();
};

#endif