#include "StaticTextDisplay.h"

StaticTextDisplay::StaticTextDisplay(StaticText& staticText) : staticText(staticText) {}

void StaticTextDisplay::showText(const String& text, uint8_t r, uint8_t g, uint8_t b, uint8_t fontScale) {
    lastText = text;
    lastR = r; lastG = g; lastB = b; lastFontScale = fontScale;
    visible = true;
    staticText.setText(text);
    staticText.setColor(r, g, b);
    staticText.setFontScale(fontScale);
    staticText.setCentered(true);
    staticText.setAntiFlicker(true);
    staticText.render(true);
}

void StaticTextDisplay::loop() {
    if (blinkEnabled) {
        unsigned long now = millis();
        if (now - lastBlink >= blinkInterval) {
            lastBlink = now;
            visible = !visible;
            if (visible) {
                staticText.setText(lastText);
                staticText.setColor(lastR, lastG, lastB);
                staticText.setFontScale(lastFontScale);
                staticText.setCentered(true);
                staticText.setAntiFlicker(true);
                staticText.render(true);
            } else {
                staticText.setText("");
                staticText.render(true);
            }
        }
    }
}

void StaticTextDisplay::setBlink(bool enable, unsigned long intervalMs) {
    blinkEnabled = enable;
    blinkInterval = intervalMs;
    lastBlink = millis();
    visible = true;
}
