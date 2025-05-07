#include "RotaryEncoder.h"
#include "RME.h"
#include "MotorController.h"

RME rme;
RotaryEncoder rotaryEncoder;
MotorController motorController;

void setup()
{
    Serial.begin(9600);
    rme.init();
    rotaryEncoder.RotaryEncoderInit();
    motorController.init();
}

void loop()
{
    float oxygenConcentration = rme.readOxygenConcentration();
    float co2Concentration = rme.readCO2Concentration();
    float breathingRate = rme.calculateBreathingRate();

    Serial.println(rotaryEncoder.getRotationCount());

    if (rotaryEncoder.isButtonPressed())
    {
        Serial.println("Button Pressed!");
        rotaryEncoder.resetRotationCount();
        motorController.run();
        motorController.stop();
    }
}
// TODO: menu Class Testing