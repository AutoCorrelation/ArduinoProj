#include "RotaryEncoderSwitch.h"
#include <Arduino.h> // Include Arduino functions like digitalRead

// Example pin definitions
const int encoderPinA = 2;
const int encoderPinB = 3;
const int buttonPin = 4;

volatile int position = 0; // Track encoder position
volatile bool buttonState = false;

void handleEncoderInterrupt() {
    // Example interrupt handler for rotary encoder
    if (digitalRead(encoderPinA) == digitalRead(encoderPinB)) {
        position++;
    } else {
        position--;
    }
}

void handleButtonInterrupt() {
    // Example interrupt handler for button press
    buttonState = !buttonState;
}

void RotaryEncoderSwitch::initialize() {
    pinMode(encoderPinA, INPUT_PULLUP);
    pinMode(encoderPinB, INPUT_PULLUP);
    pinMode(buttonPin, INPUT_PULLUP);

    attachInterrupt(digitalPinToInterrupt(encoderPinA), handleEncoderInterrupt, CHANGE);
    attachInterrupt(digitalPinToInterrupt(buttonPin), handleButtonInterrupt, FALLING);
}

void RotaryEncoderSwitch::update() {
    // Placeholder for periodic updates, if needed
}

int RotaryEncoderSwitch::getPosition() {
    return position;
}

bool RotaryEncoderSwitch::isButtonPressed() {
    return buttonState;
}