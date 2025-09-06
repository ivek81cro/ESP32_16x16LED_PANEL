
#include "TextDisplayMode.h"

TextDisplayMode::TextDisplayMode(StaticTextDisplay& staticDisplay, ScrollingTextDisplay& scrollDisplay)
    : staticDisplay(staticDisplay), scrollDisplay(scrollDisplay) {}

void TextDisplayMode::showText(const String& text, bool scroll, uint8_t r, uint8_t g, uint8_t b, uint8_t fontScale) {
    currentScroll = scroll;
    if (scroll) {
        activeDisplay = &scrollDisplay;
    } else {
        activeDisplay = &staticDisplay;
    }
    activeDisplay->showText(text, r, g, b, fontScale);
}

void TextDisplayMode::loop() {
    if (activeDisplay) {
        activeDisplay->loop();
    }
}
