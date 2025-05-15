#ifndef _RME_H_
#define _RME_H_

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DFRobot_OxygenSensor.h>
#include <SparkFun_STC3x_Arduino_Library.h>
#include <SoftwareSerial.h>
#include "Config.h" // Include configuration file

// RME (Respiration Monitoring Equipment) class
class RME
{
private:
    Adafruit_SSD1306 display;          // OLED display object
    DFRobot_OxygenSensor oxygen;       // Oxygen sensor object
    STC3x co2;                         // CO2 sensor object
    float _oxygenConcentration;        // Stores oxygen concentration value
    float _co2Concentration;           // Stores CO2 concentration value
    float _breathingRate;              // Stores calculated breathing rate
    float _oxygenOffset;               // Calibration offset for oxygen sensor
    float _carbsRate;                  // Carbohydrate metabolism rate
    float _fatsRate;                   // Fat metabolism rate

    // Maximum values for measurements
    float _minOxygen = 100;
    float _maxCO2 = 0;

public:
    RME();                            // Constructor
    ~RME();                           // Destructor
    void init();                      // Initialize sensors and display
    float readOxygenConcentration();  // Read oxygen concentration from sensor
    float readCO2Concentration();     // Read CO2 concentration from sensor
    float calculateBreathingRate();   // Calculate breathing rate from sensor data using VCO2/VO2
    void displayValues();             // Display values on OLED screen
    void SerialTest(SoftwareSerial *btserial); // Test function for serial output
    void clearDisplay();              // Clear OLED display
    Adafruit_SSD1306 *getDisplay() {return &display;} // OLED display object
    void reCalibration();             // Recalibrate sensors
};

#endif