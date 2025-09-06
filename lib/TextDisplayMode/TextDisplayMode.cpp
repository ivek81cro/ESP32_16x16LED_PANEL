#include "TextDisplayMode.h"

TextDisplayMode::TextDisplayMode(StaticText& staticText, ScrollingText& scrollingText)
    : staticText(staticText), scrollingText(scrollingText) {}

void TextDisplayMode::showText(const String& text, bool scroll, uint8_t r, uint8_t g, uint8_t b, uint8_t fontScale) {
    currentScroll = scroll;
    currentText = text;
    currentFontScale = fontScale;
    currentColor = Adafruit_NeoPixel::Color(r, g, b);
    if (scroll) {
        scrollingText.setText(text);
        scrollingText.setColor(r, g, b);
        scrollingText.setFontScale(fontScale);
        scrollingText.reset();
    } else {
        staticText.setText(text);
        staticText.setColor(r, g, b);
        staticText.setFontScale(fontScale);
        staticText.setCentered(true);
        staticText.setAntiFlicker(true);
        staticText.render(true);
    }
}

void TextDisplayMode::loop() {
    if (currentScroll) {
        scrollingText.step();
    }
    // StaticText se automatski ažurira u glavnoj petlji
}
