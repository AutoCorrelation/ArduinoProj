#include "Display.h"
#include <Arduino.h>

void Display::initialize() {
    Serial.println("Display initialized");
}

void Display::update() {
    // Update display content
}

void Display::showText(const char* text) {
    Serial.println(text);
}