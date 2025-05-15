#include "RME.h"

// Constructor: Initialize display and sensor objects
RME::RME() : display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET), oxygen(), co2() {}

RME::~RME() {}

// Initialize sensors and display
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
    display.clearDisplay();

    _oxygenOffset = readOxygenConcentration();
}

// Read oxygen concentration and update maximum value
float RME::readOxygenConcentration()
{
    _oxygenConcentration = oxygen.getOxygenData(COLLECT_NUMBER);
    if (_oxygenConcentration < _minOxygen)
    {
        _minOxygen = _oxygenConcentration;
    }
    return _oxygenConcentration;
}

// Read CO2 concentration and update maximum value
float RME::readCO2Concentration()
{
    _co2Concentration = co2.getCO2();
    if (_co2Concentration > _maxCO2)
    {
        _maxCO2 = _co2Concentration;
    }
    if (_co2Concentration < 0)
        return _co2Concentration = 0;
    return _co2Concentration;
}

// Calculate breathing rate using maximum VCO2 and VO2
float RME::calculateBreathingRate()
{
    _breathingRate = (_maxCO2 - CO2_CONECTRATION) / (OXYGEN_CONECTRATION - _minOxygen) ;
    
    _fatsRate = (1 - _breathingRate) / 0.3 * 100.0;
    _carbsRate = 100 - _fatsRate;
    
    // Reset maximum values for the next measurement cycle
    // _maxCO2 = 0;
    // _minOxygen = 100;
    
    return _breathingRate;
}

void RME::displayValues()
{
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);

    display.print(F("O2: "));
    display.print(_minOxygen);
    display.println(F(" %"));

    display.print(F("CO2: "));
    display.print(_maxCO2);
    display.println(F(" %"));

    display.print(F("RER: "));
    display.print(_breathingRate);
    display.println(F(" units"));

    if (0.7 <= _breathingRate && _breathingRate <= 1.0)
    {
        display.print(F("fat: "));
        display.print(_fatsRate);
        display.println(F(" %"));

        display.print(F("carbs: "));
        display.print(_carbsRate);
        display.println(F(" %"));
    }
    else if (_breathingRate < 0.7)
    {
        display.print(F("Retry breath"));
    }
    else if (_breathingRate > 1.0)
    {
        display.print(F("Wait a Minute"));
    }

    display.display();
}

void RME::SerialTest(SoftwareSerial *BTSerial)
{
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    int textWidth = 90;
    int x = (SCREEN_WIDTH - textWidth) / 2;
    display.setCursor(x, SCREEN_HEIGHT / 2);
    display.println(F("Sending Data..."));
    display.display();

    // BTSerial->print(F("RER: "));
    // BTSerial->print(_breathingRate);
    // BTSerial->println(F(" units"));

    if (0.7 <= _breathingRate && _breathingRate <= 1.0)
    {
        BTSerial->print(F("지방분해: "));
        BTSerial->print(_fatsRate);
        BTSerial->println(F(" %"));

        BTSerial->print(F("탄수화물분해: "));
        BTSerial->print(_carbsRate);
        BTSerial->println(F(" %"));

        BTSerial->print(F("에너지: "));
        BTSerial->print((1.24 * _breathingRate + 3.81) * 0.648);
        BTSerial->println(F(" kcal"));
         
        BTSerial->println(F("운동을 잘하고 있습니다"));
    }
    else if (_breathingRate < 0.7)
    {
        BTSerial->print(F("약한 운동중이십니다"));
    }
    else if (_breathingRate > 1.0)
    {
        BTSerial->print(F("엄청난 운동 중입니다"));
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

    _maxCO2 = 0;
    _minOxygen = 100;
    _oxygenOffset = readOxygenConcentration();

    delay(10);
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 28);
    display.println(F("Calibration Done"));
    display.display();
    delay(10);
}