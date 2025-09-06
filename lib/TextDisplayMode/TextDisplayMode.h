#pragma once
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "StaticText.h"
#include "ScrollingText.h"

class TextDisplayMode {
public:
    TextDisplayMode(StaticText& staticText, ScrollingText& scrollingText);
    void showText(const String& text, bool scroll, uint8_t r, uint8_t g, uint8_t b, uint8_t fontScale = 1);
    void loop();
private:
    StaticText& staticText;
    ScrollingText& scrollingText;
    bool currentScroll = false;
    String currentText = "";
    uint8_t currentFontScale = 1;
    uint32_t currentColor = 0xFFFFFF;
};
