#include "MotorController.h"

MotorController::MotorController() { }

void MotorController::init() {
    pinMode(motorA1, OUTPUT);
    pinMode(motorA2, OUTPUT);
    pinMode(motorB1, OUTPUT);
    pinMode(motorB2, OUTPUT);
    stop(); // ensure motors are stopped on startup
}

void MotorController::run() {
    digitalWrite(motorA1, HIGH); // right intake
    digitalWrite(motorA2, LOW);
    digitalWrite(motorB1, HIGH);
    digitalWrite(motorB2, LOW);
    delay(5000);
}

void MotorController::stop() {
    digitalWrite(motorA1, LOW);
    digitalWrite(motorA2, LOW);
    digitalWrite(motorB1, LOW);
    digitalWrite(motorB2, LOW);
    delay(1000);
}