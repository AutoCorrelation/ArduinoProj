#ifndef ABSTRACT_DEVICE_H
#define ABSTRACT_DEVICE_H

#include "./config/Config.h"

class AbstractDevice {
public:
    virtual void initialize() = 0; // Pure virtual function for initialization
    virtual void update() = 0;     // Pure virtual function for periodic updates
    virtual ~AbstractDevice() {}   // Virtual destructor
};

#endif