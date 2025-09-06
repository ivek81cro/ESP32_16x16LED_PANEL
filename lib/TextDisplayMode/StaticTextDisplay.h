#pragma once
#include "ITextDisplay.h"
#include "StaticText.h"

class StaticTextDisplay : public ITextDisplay {
public:
    StaticTextDisplay(StaticText& staticText);
    void showText(const String& text, uint8_t r, uint8_t g, uint8_t b, uint8_t fontScale = 1) override;
    void loop() override;
private:
    StaticText& staticText;
};
