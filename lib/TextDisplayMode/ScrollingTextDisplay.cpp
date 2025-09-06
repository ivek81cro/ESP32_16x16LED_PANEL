#include "ScrollingTextDisplay.h"

ScrollingTextDisplay::ScrollingTextDisplay(ScrollingText& scrollingText) : scrollingText(scrollingText) {}

void ScrollingTextDisplay::showText(const String& text, uint8_t r, uint8_t g, uint8_t b, uint8_t fontScale) {
    scrollingText.setText(text);
    scrollingText.setColor(r, g, b);
    scrollingText.setFontScale(fontScale);
    scrollingText.reset();
}

void ScrollingTextDisplay::loop() {
    scrollingText.step();
}
