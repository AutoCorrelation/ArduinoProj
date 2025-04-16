#ifndef _RME_H_
#define _RME_H_

// Include necessary libraries
#include <Arduino.h>
#include <Wire.h>
#include "config/Config.h"
#include "Display.h"
#include "lib/DFRobot_OxygenSensor.h"
#include "lib/SparkFun_STC3x_Arduino_Library.h"

// RME (Respiration Monitoring Equipment) class
class RME
{
private:
              // OLED display object
    DFRobot_OxygenSensor oxygen;       // Oxygen sensor object
    STC3x co2;                         // CO2 sensor object
    float _oxygenConcentration;        // Stores oxygen concentration value
    float _co2Concentration;           // Stores CO2 concentration value
    float _breathingRate;              // Stores calculated breathing rate
    float _oxygenOffset;               // Calibration offset for oxygen sensor
    float _carbsRate;                  // Carbohydrate metabolism rate
    float _fatsRate;                   // Fat metabolism rate
public:
    RME();                            // Constructor
    ~RME();                           // Destructor
    void init();                      // Initialize sensors and display
    float readOxygenConcentration();  // Read oxygen concentration from sensor
    float readCO2Concentration();     // Read CO2 concentration from sensor
    float calculateBreathingRate();   // Calculate breathing rate from sensor data
    void displayValues();             // Display values on OLED screen
    void SerialTest();               // Test function for serial output
};
#endif