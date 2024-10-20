#ifndef _DEVICE_H_
#define _DEVICE_H_

#include "DFRobot_OxygenSensor.h"
#include "SparkFun_STC3x_Arduino_Library.h"

class Device // : public DFRobot_OxygenSensor, public STC3x
{

public:
    Device();
    ~Device();

    /**
     * @fn init
     * @brief initialize Device
     * @return None
     */
    bool init();

    void fastCalibrate();

    float getRER();
    float getMAXRER();

private:
    void KF_Alg();
    float _x1, _P1; // k-1 step
    float _x2, _P2; // k hat (estimation)
    float _x3, _P3; // k    (prediction)
    float buf[25];
    void LPF();
    float M;

    DFRobot_OxygenSensor O2;
    STC3x CO2;
};

#endif
