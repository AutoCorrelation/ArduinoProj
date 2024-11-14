#include "RME.h"

RME rme;

void setup()
{
    // Serial.begin(9600);
    rme.init();
}

void loop()
{
    float oxygenConcentration = rme.readOxygenConcentration();
    float co2Concentration = rme.readCO2Concentration();
    float breathingRate = rme.calculateBreathingRate();
    rme.displayValues();
    rme.SerialTest();
    delay(75); // 1초 대기
}
