#include "RotaryEncoder.h"
#include "RME.h"
#include "MotorController.h"
#include "Menu.h"

RME rme;
RotaryEncoder rotaryEncoder;
MotorController motorController;
Menu menu(rme.getDisplay());   // Pass the display object to the Menu class
SoftwareSerial BTSerial(6, 7); // RX, TX

void setup()
{
    Serial.begin(9600);
    BTSerial.begin(9600);
    rme.init();
    rotaryEncoder.RotaryEncoderInit();
    motorController.init();
}

void loop()
{
    int count = menu.updateMenu(rotaryEncoder.getRotationCount());
    float oxygenConcentration = rme.readOxygenConcentration();
    float co2Concentration = rme.readCO2Concentration();
    float breathingRate = rme.calculateBreathingRate();

    if (rotaryEncoder.isButtonPressed())
    {
        switch (count)
        {
        case 0:
            motorController.run(); // 30s
            motorController.stop();
            delay(1000);
            break;
        case 1:
            rme.SerialTest(&BTSerial); // Send data to Bluetooth
            delay(1000);
            rme.displayValues(); // Display values on OLED
            delay(2000);
            break;

        case 2:
            rme.reCalibration(); // Recalibrate sensors (not often needed)
            delay(1000);
            break;
        }
        rotaryEncoder.resetRotationCount();
        rme.clearDisplay();
    }
}
// TODO: debug System.