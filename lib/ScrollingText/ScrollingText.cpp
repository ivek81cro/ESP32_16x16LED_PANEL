#include "ScrollingText.h"

ScrollingText::ScrollingText(Adafruit_NeoPixel &strip) : strip(strip) {}

void ScrollingText::setText(const String &text) { this->text = text; rebuildBitmap(); }

void ScrollingText::setColor(uint8_t r, uint8_t g, uint8_t b) { color = strip.Color(r,g,b); }

void ScrollingText::setSpeed(uint16_t ms) { stepDelay = ms; }

void ScrollingText::setFontScale(uint8_t scale) { fontScale = scale < 1 ? 1 : scale; rebuildBitmap(); }

void ScrollingText::reset() { offsetX = MATRIX_WIDTH; lastStep = 0; }

void ScrollingText::step() {
  unsigned long now = millis();
  if (now - lastStep < stepDelay) return;
  lastStep = now;

  // Clear frame
  for (uint16_t y = 0; y < MATRIX_HEIGHT; y++) {
    for (uint16_t x = 0; x < MATRIX_WIDTH; x++) {
      strip.setPixelColor(displayToIndex(x, y), 0);
    }
  }

  // Iscrtaj vidljivi prozor bitmape na trenutnom offsetX (dy je centriran vertikalno)
  for (uint16_t y = 0; y < fontScale * 7 && y < MATRIX_HEIGHT; y++) {
    int dy = (MATRIX_HEIGHT - fontScale * 7) / 2 + y; // vertically centered
    for (uint16_t x = 0; x < MATRIX_WIDTH; x++) {
      int bx = x - offsetX;
      if (bx >= 0 && bx < (int)bmpWidth) {
        if (bitmap[y * bmpWidth + bx]) {
          strip.setPixelColor(displayToIndex(x, dy), color);
        }
      }
    }
  }

  strip.show();

  if (offsetX > -((int)bmpWidth)) {
    offsetX--; // move left
  } else {
    offsetX = MATRIX_WIDTH; // restart
  }
}

void ScrollingText::rebuildBitmap() {
  buildTextBitmap(text, fontScale, bitmap, bmpWidth); // Regeneriraj cijelu traku teksta.
  offsetX = MATRIX_WIDTH; // Resetiraj na početni položaj (izvan desnog ruba).
}
