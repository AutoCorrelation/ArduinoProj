#include "DCMotorDriver.h"
#include <Arduino.h> // Arduino-specific functions like pinMode, analogWrite

void DCMotorDriver::initialize() {
    pinMode(motorPin, OUTPUT); // Set motor pin as output
    analogWrite(motorPin, 0);  // Initialize motor speed to 0
}

void DCMotorDriver::update() {
    // Example: Add logic to update motor state if needed
    // For now, this is a placeholder
}

void DCMotorDriver::setSpeed(int speed) {
    // Constrain speed to valid PWM range (0-255)
    speed = constrain(speed, 0, 255);
    analogWrite(motorPin, speed); // Set motor speed
}