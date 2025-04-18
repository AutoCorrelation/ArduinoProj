#include "RotaryEncoder.h"

RotaryEncoder::RotaryEncoder() {
    RotaryEncoderInit();
}

void RotaryEncoder::RotaryEncoderInit() {
    pinMode(ENCODER_PIN_A, INPUT);
    pinMode(ENCODER_PIN_B, INPUT);
    pinMode(ENCODER_BUTTON_PIN, INPUT);

    attachInterrupt(digitalPinToInterrupt(ENCODER_PIN_A),RotationISR, FALLING);
    attachInterrupt(digitalPinToInterrupt(ENCODER_BUTTON_PIN), buttonPressed, FALLING);
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

    