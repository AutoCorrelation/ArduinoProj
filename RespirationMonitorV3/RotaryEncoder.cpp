#include "RotaryEncoder.h"

// Define the static instance pointer
RotaryEncoder* RotaryEncoder::instance = nullptr;

RotaryEncoder::RotaryEncoder() {
    instance = this;
    RotaryEncoderInit();
}

void RotaryEncoder::RotaryEncoderInit() {
    pinMode(ENCODER_PIN_A, INPUT);
    pinMode(ENCODER_PIN_B, INPUT);
    pinMode(ENCODER_BUTTON_PIN, INPUT);
    
    attachInterrupt(digitalPinToInterrupt(ENCODER_PIN_A), isrRotationWrapper, FALLING);
    attachInterrupt(digitalPinToInterrupt(ENCODER_BUTTON_PIN), buttonPressedWrapper, FALLING);
}

// Static wrapper for rotation ISR
void RotaryEncoder::isrRotationWrapper() {
    if (instance) {
        instance->RotationISR();
    }
}

// Static wrapper for button ISR
void RotaryEncoder::buttonPressedWrapper() {
    if (instance) {
        instance->buttonPressed();
    }
}

void RotaryEncoder::RotationISR() {
    _pinB = digitalRead(ENCODER_PIN_B);
    if (_pinB == HIGH) {
        _count++;
    } else {
        _count--;
    }
}

void RotaryEncoder::buttonPressed() {
    _buttonPressed = true;
}

int RotaryEncoder::getRotationCount() {
    return _count;
}

bool RotaryEncoder::isButtonPressed() {
    if (_buttonPressed) {
        _buttonPressed = false;
        return true;
    }
    return false;
}

void RotaryEncoder::resetRotationCount() {
    _count = 0;
}

