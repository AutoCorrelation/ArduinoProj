#include "I2CSensor.h"

void I2CSensor::initialize()
{
    Serial.begin(9600);

    while (!display.begin(SSD1306_SWITCHCAPVCC, LCD_IICAddress))
    {
        Serial.println("Display I2C device Address Error!");
        while (1);
    }

    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 28);

    if (!oxygen.begin(Oxygen_IICAddress))
    {
        display.println("Oxygen I2C device Address Error!");
        display.display();
        while (1);
    }

    if (!co2.begin())
    {
        display.println("CO2 I2C device Address Error!");
        display.display();
        while (1);
    }
}

void I2CSensor::update()
{
    // Placeholder for periodic updates, if needed
}

float I2CSensor::readValue()
{
    Wire.beginTransmission(sensorAddress);
    Wire.write(0x00); // Example: Command to request data
    Wire.endTransmission();

    Wire.requestFrom(sensorAddress, 2); // Request 2 bytes from the sensor
    if (Wire.available() == 2)
    {
        int highByte = Wire.read();
        int lowByte = Wire.read();
        int rawValue = (highByte << 8) | lowByte;
        return rawValue / 100.0; // Example: Convert raw value to meaningful data
    }

    return 0.0; // Return 0.0 if no data is available
}