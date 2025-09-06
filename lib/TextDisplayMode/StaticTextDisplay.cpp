#include "StaticTextDisplay.h"

StaticTextDisplay::StaticTextDisplay(StaticText& staticText) : staticText(staticText) {}

void StaticTextDisplay::showText(const String& text, uint8_t r, uint8_t g, uint8_t b, uint8_t fontScale) {
    staticText.setText(text);
    staticText.setColor(r, g, b);
    staticText.setFontScale(fontScale);
    staticText.setCentered(true);
    staticText.setAntiFlicker(true);
    staticText.render(true);
}

void StaticTextDisplay::loop() {
    // Nothing needed for static text
}
