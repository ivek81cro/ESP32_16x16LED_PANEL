
#pragma once
#include <Arduino.h>
#include "ITextDisplay.h"
#include "StaticTextDisplay.h"
#include "ScrollingTextDisplay.h"

class TextDisplayMode {
public:
    TextDisplayMode(StaticTextDisplay& staticDisplay, ScrollingTextDisplay& scrollDisplay);
    void showText(const String& text, bool scroll, uint8_t r, uint8_t g, uint8_t b, uint8_t fontScale = 1);
    void loop();
private:
    ITextDisplay* activeDisplay = nullptr;
    StaticTextDisplay& staticDisplay;
    ScrollingTextDisplay& scrollDisplay;
    bool currentScroll = false;
};
