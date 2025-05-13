#include "RME.h"

// RME (Respiration Monitor Environment) class implementation
// Manages oxygen and CO2 sensors, OLED display, and calculates respiratory parameters

// Constructor: Initialize display and sensor objects
RME::RME() : display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET), oxygen(), co2() {}

RME::~RME() {}

// Initialize sensors and display
// Verifies connection to O2 sensor and CO2 sensor
// Sets up initial calibration
void RME::init()
{
    Serial.begin(9600);
    while (!display.begin(SSD1306_SWITCHCAPVCC, LCD_IICAddress))
    {
        Serial.println(F("SSD1306 allocation failed"));
        delay(1000);
    }
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 28);

    while (!oxygen.begin(Oxygen_IICAddress))
    {
        display.println("O2 connection failed");
        display.display();
        delay(1000);
    }
    display.clearDisplay();

    while (!co2.begin())
    {
        display.println("CO2 connection failed");
        display.display();
        delay(1000);
    }
    co2.setBinaryGas(STC3X_BINARY_GAS_CO2_AIR_25);
    // co2.forcedRecalibration(-1, 0);
    display.clearDisplay();

    _oxygenOffset = readOxygenConcentration();
}

// Read oxygen concentration from sensor using multiple samples
float RME::readOxygenConcentration()
{
    _oxygenConcentration = oxygen.getOxygenData(COLLECT_NUMBER);
    return _oxygenConcentration;
}

// Read CO2 concentration from sensor
// Returns 0 if negative value detected
float RME::readCO2Concentration()
{
    _co2Concentration = co2.getCO2();
    if (_co2Concentration < 0)
        return _co2Concentration = 0;
    return _co2Concentration;
    // if (co2.measureGasConcentration())
    // {
    //     return co2.getCO2();
    // }
    // return -1; // 에러 발생 시 -1 반환
}

// Calculate Respiratory Exchange Ratio (RER)
// RER = CO2 produced / O2 consumed
// Also calculates fat and carbohydrate utilization rates
float RME::calculateBreathingRate()
{
    _breathingRate = (_co2Concentration - CO2_CONECTRATION) / (OXYGEN_CONECTRATION - _oxygenConcentration);
    _fatsRate = (1 - _breathingRate) / 0.3 * 100.0;
    _carbsRate = 100 - _fatsRate;
    return _breathingRate;
}

// Update OLED display with current measurements
// Shows O2, CO2, RER, fat and carb percentages
// Displays status messages based on RER value
void RME::displayValues()
{
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);

    display.print(F("O2: "));
    display.print(_oxygenConcentration);
    display.println(F(" %"));

    display.print(F("CO2: "));
    display.print(_co2Concentration);
    display.println(F(" %"));

    if (0.7 <= _breathingRate && _breathingRate <= 1.0)
    {
        display.print(F("RER: "));
        display.print(_breathingRate);
        display.println(F(" units"));

        display.print(F("fat: "));
        display.print(_fatsRate);
        display.println(F(" %"));

        display.print(F("carbs: "));
        display.print(_carbsRate);
        display.println(F(" %"));
    }
    else if (_breathingRate < 0.7)
    {
        display.print(F("RER: "));
        display.print(_breathingRate);
        display.println(F(" units"));
        display.print(F("More breath plz"));
    }
    else if (1.0 < _breathingRate)
    {
        display.print(F("RER: "));
        display.print(_breathingRate);
        display.println(F(" units"));
        display.print(F("Wait a Minute"));
    }

    display.display();
}

// Output test data to serial monitor
// Prints O2 consumption and CO2 production
void RME::SerialTest(SoftwareSerial *BTSerial)
{
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    int textWidth = 90;  // "Sending Data..." is 15 characters at 6 pixels each.
    int x = (SCREEN_WIDTH - textWidth) / 2;
    display.setCursor(x, SCREEN_HEIGHT / 2);
    display.println(F("Sending Data..."));
    display.display();

    BTSerial->print(F("O2: "));
    BTSerial->print(_oxygenConcentration);
    BTSerial->println(F(" %"));

    BTSerial->print(F("CO2: "));
    BTSerial->print(_co2Concentration);
    BTSerial->println(F(" %"));

    BTSerial->print(F("RER: "));
    BTSerial->print(_breathingRate);
    BTSerial->println(F(" units"));

    if (0.7 <= _breathingRate && _breathingRate <= 1.0)
    {
        BTSerial->print(F("fat: "));
        BTSerial->print(_fatsRate);
        BTSerial->println(F(" %"));

        BTSerial->print(F("carbs: "));
        BTSerial->print(_carbsRate);
        BTSerial->println(F(" %"));
    }
    else if (_breathingRate < 0.7)
    {
        BTSerial->print(F("Retry breath"));
    }
    else if (1.0 < _breathingRate)
    {
        BTSerial->print(F("Wait a Minute"));
    }
    delay(10);
}

void RME::clearDisplay()
{
    display.clearDisplay();
    display.display();
}

void RME::reCalibration()
{
    co2.forcedRecalibration(-1, 0);
    oxygen.calibrate(OXYGEN_CONECTRATION, 0);
    delay(10);
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 28);
    display.println(F("Calibration Done"));
    display.display();
    delay(10);
}