#ifndef DISPLAY_H
#define DISPLAY_H

#include "AbstractDevice.h"

class Display : public AbstractDevice {
public:
    void initialize() override;
    void update() override;
    void showText(const char* text);
};

#endif