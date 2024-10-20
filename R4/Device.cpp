#include "Device.h"

Device::Device() : O2(), CO2()
{
    // 초기화 작업
    _x1 = _P1 = 0.0;
    _x2 = _P2 = 0.0;
    _x3 = _P3 = 0.0;
}

Device::~Device()
{

    // 정리 작업 (필요 시)
}

bool Device::init()
{
    bool oxygenSensorInit = O2.begin();
    bool co2SensorInit = CO2.begin();
    return oxygenSensorInit && co2SensorInit;
}

void Device::fastCalibrate()
{
    O2.calibrate();
    CO2.();
}

float Device::getRER()
{
    float oxygenConcentration = O2.readOxygenConcentration();
    float co2Concentration = CO2.readCO2Concentration();
    return co2Concentration / oxygenConcentration;
}

float Device::getMAXRER()
{
    float maxRER = 0.0;
    for (int i = 0; i < 25; i++)
    {
        float currentRER = getRER();
        if (currentRER > maxRER)
        {
            maxRER = currentRER;
        }
    }
    return maxRER;
}

void Device::KF_Alg()
{
    // 칼만 필터 알고리즘 구현
}

void Device::LPF()
{
    // 저역 필터 알고리즘 구현
}
