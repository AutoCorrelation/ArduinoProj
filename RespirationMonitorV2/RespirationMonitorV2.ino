// Main program for Respiration Monitor
// Measures O2 consumption and CO2 production to calculate RER
// Updates display every 75ms with current measurements

#include "RME.h"

// Create RME instance to manage sensors and display
RME rme;

// Initialize hardware
void setup()
{
    rme.init();
}

// Main program loop
// Continuously read sensors, calculate RER, and update display
void loop()
{   
    float oxygenConcentration = rme.readOxygenConcentration();
    float co2Concentration = rme.readCO2Concentration();
    float breathingRate = rme.calculateBreathingRate();
    rme.displayValues();
    rme.SerialTest();
    delay(75); // 0.075s
}
