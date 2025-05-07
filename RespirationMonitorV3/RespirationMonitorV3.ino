#include "RotaryEncoder.h"
#include "RME.h"

RME rme;
RotaryEncoder rotaryEncoder;

void setup()
{
    Serial.begin(9600);
    rme.init();
    rotaryEncoder.RotaryEncoderInit();

    pinMode(motorA1, OUTPUT);
    pinMode(motorA2, OUTPUT);
    pinMode(motorB1, OUTPUT);
    pinMode(motorB2, OUTPUT);
    digitalWrite(motorA1, LOW);
    digitalWrite(motorA2, LOW);
    digitalWrite(motorB1, LOW);
    digitalWrite(motorB2, LOW);
}

void loop()
{
    float oxygenConcentration = rme.readOxygenConcentration();
    float co2Concentration = rme.readCO2Concentration();
    float breathingRate = rme.calculateBreathingRate();

    Serial.print(rotaryEncoder.getRotationCount());

    if (rotaryEncoder.isButtonPressed())
    {
        Serial.println("Button Pressed!");
        rotaryEncoder.resetRotationCount();
        
    }
    MotorRun();
    delay(10);
    // FIXME: 모터 드라이버 전압 문제, 정격은 3.0이나 1.8V 로 들어감
    // TODO: add MENU Class AND MOTOR control code
}

void MotorRun()
{
    digitalWrite( motorA1 , HIGH); // 오른쪽 흡입
    digitalWrite( motorA2 , LOW);
    // digitalWrite( motorB1 , LOW); // 오른쪽?
    // digitalWrite( motorB2 , HIGH);
    digitalWrite(motorB1, HIGH);
    digitalWrite(motorB2, LOW);
    // delay(2000);

    // digitalWrite( motorA1 , LOW); // 오른쪽 배기
    // digitalWrite( motorA2 , HIGH);
    // digitalWrite( motorB1 , HIGH);
    // digitalWrite( motorB2 , LOW);
    // digitalWrite( motorB1 , LOW);
    // digitalWrite( motorB2 , HIGH);
    delay(5000);

    digitalWrite(motorA1, LOW);
    digitalWrite(motorA2, LOW);
    digitalWrite(motorB1, LOW);
    digitalWrite(motorB2, LOW);

    delay(1000);
}