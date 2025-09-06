#pragma once
#include <Arduino.h>

class ITextDisplay {
public:
    virtual void showText(const String& text, uint8_t r, uint8_t g, uint8_t b, uint8_t fontScale = 1) = 0;
    virtual void loop() = 0;
    virtual ~ITextDisplay() {}
};
