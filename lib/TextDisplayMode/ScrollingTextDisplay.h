#pragma once
#include "ITextDisplay.h"
#include "ScrollingText.h"

class ScrollingTextDisplay : public ITextDisplay {
public:
    ScrollingTextDisplay(ScrollingText& scrollingText);
    void showText(const String& text, uint8_t r, uint8_t g, uint8_t b, uint8_t fontScale = 1) override;
    void loop() override;
private:
    ScrollingText& scrollingText;
};
