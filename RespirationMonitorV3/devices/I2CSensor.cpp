#include "I2CSensor.h"
#include <Wire.h> // Include Arduino I2C library

void I2CSensor::initialize() {
    Serial.begin(9600);
    Wire.begin();

    if(!oxygen.begin(Oxygen_IICAddress)) {
        Serial.println("Oxygen I2C device Address Error!");
        while (1);
    }

    if(!co2.begin()) {
        Serial.println("CO2 I2C device Address Error!");
        while (1);
    }


}

void I2CSensor::update() {
    // Placeholder for periodic updates, if needed
}

float I2CSensor::readValue() {
    Wire.beginTransmission(sensorAddress);
    Wire.write(0x00); // Example: Command to request data
    Wire.endTransmission();

    Wire.requestFrom(sensorAddress, 2); // Request 2 bytes from the sensor
    if (Wire.available() == 2) {
        int highByte = Wire.read();
        int lowByte = Wire.read();
        int rawValue = (highByte << 8) | lowByte;
        return rawValue / 100.0; // Example: Convert raw value to meaningful data
    }

    return 0.0; // Return 0.0 if no data is available
}