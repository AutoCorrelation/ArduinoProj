#ifndef _RME_H_
#define _RME_H_

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DFRobot_OxygenSensor.h>
#include <SparkFun_STC3x_Arduino_Library.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET 4
#define Oxygen_IICAddress ADDRESS_3
#define COLLECT_NUMBER 2 // collect number, the collection range is 1-100.
#define LCD_IICAddress 0x3C

class RME
{
private:
    Adafruit_SSD1306 display;
    DFRobot_OxygenSensor oxygen;
    STC3x co2;
    float _oxygenConcentration;
    float _co2Concentration;
    float _breathingRate;
    float _oxygenOffset;
    float _carbsRate;
    float _fatsRate;
public:
    RME();
    ~RME();
    void init();
    float readOxygenConcentration();
    float readCO2Concentration();
    float calculateBreathingRate();
    void displayValues();
    void SerialTest();
};
#endif