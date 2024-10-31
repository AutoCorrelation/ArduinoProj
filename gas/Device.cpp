#include "Device.h"

Device::Device() : O2(), CO2() {
    _x1 = _P1 = 0.0;
    _x2 = _P2 = 0.0;
    _x3 = _P3 = 0.0;
}

Device::~Device() {
    // Cleanup if necessary
}

bool Device::init() {
    bool oxygenSensorInit = O2.begin();
    bool co2SensorInit = CO2.begin();
    return oxygenSensorInit && co2SensorInit;
}

void Device::fastCalibrate() {
    O2.calibrate();
    CO2.enableAutomaticSelfCalibration();
}

float Device::getRER() {
    float oxygenConcentration = O2.readOxygenConcentration();
    float co2Concentration = CO2.readCO2Concentration();
    return co2Concentration / oxygenConcentration;
}

float Device::getMAXRER() {
    float maxRER = 0.0;
    for (int i = 0; i < 25; i++) {
        float currentRER = getRER();
        if (currentRER > maxRER) {
            maxRER = currentRER;
        }
    }
    return maxRER;
}

void Device::KF_Alg() {
    // Implement Kalman Filter algorithm
}

void Device::LPF() {
    const float alpha = 0.1;
    static float filteredValue = 0.0;
    float currentRER = getRER();
    filteredValue = alpha * currentRER + (1 - alpha) * filteredValue;
}

void Device::sleep() {
    
}

void Device::wakeUp() {
    
}

void Device::setDeviceMode(DeviceMode mode)
{
    switch (mode)
    {
    case DeviceMode::SLEEP:
        sleepMode();
        break;
    case DeviceMode::WAKEUP:
        wakeUp();
        break;
    }
}