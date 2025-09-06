#pragma once
#include "ITextDisplay.h"
#include "StaticText.h"


class StaticTextDisplay : public ITextDisplay {
public:
    StaticTextDisplay(StaticText& staticText);
    void showText(const String& text, uint8_t r, uint8_t g, uint8_t b, uint8_t fontScale = 1) override;
    void loop() override;
    void setBlink(bool enable, unsigned long intervalMs = 500);
private:
    StaticText& staticText;
    bool blinkEnabled = false;
    unsigned long blinkInterval = 500;
    unsigned long lastBlink = 0;
    bool visible = true;
    String lastText = "";
    uint8_t lastR = 0, lastG = 0, lastB = 0, lastFontScale = 1;
};
