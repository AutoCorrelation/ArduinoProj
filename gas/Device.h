#ifndef _DEVICE_H_
#define _DEVICE_H_

#include "DFRobot_OxygenSensor.h"
#include "SparkFun_STC3x_Arduino_Library.h"
#include "Arduino.h"

class Device
{
public:
    Device();
    ~Device();

    bool init();
    void fastCalibrate();
    float getRER();
    float getMAXRER();
    void sleep();
    void wakeUp();

private:
    void KF_Alg();
    void LPF();
    float _x1, _P1; // k-1 step
    float _x2, _P2; // k hat (estimation)
    float _x3, _P3; // k    (prediction)
    float buf[25];
    float M;

    DFRobot_OxygenSensor O2;
    STC3x CO2;
};

#endif
