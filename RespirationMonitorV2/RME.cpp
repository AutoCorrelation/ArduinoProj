#include "RME.h"

RME::RME() : display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET), oxygen(), co2() {}

RME::~RME() {}

void RME::init()
{
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

}

float RME::readOxygenConcentration()
{
    _oxygenConcentration = oxygen.getOxygenData(COLLECT_NUMBER);
    return _oxygenConcentration;
}

float RME::readCO2Concentration()
{
    _co2Concentration = co2.getCO2();
    return _co2Concentration;
    // if (co2.measureGasConcentration())
    // {
    //     return co2.getCO2();
    // }
    // return -1; // 에러 발생 시 -1 반환
}

float RME::calculateBreathingRate()
{
    _breathingRate = _oxygenConcentration / _co2Concentration;
    return _breathingRate;
}

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

    display.print(F("Breathing Rate: "));
    display.print(_breathingRate);
    display.println(F(" units"));

    display.display();
}