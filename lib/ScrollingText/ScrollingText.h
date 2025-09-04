#pragma once
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <vector>
#include <ctype.h>
#include "MatrixMapping.h"
#include "SimpleFont5x7.h"

class ScrollingText {
 public:
  ScrollingText(Adafruit_NeoPixel &strip) : strip(strip) {}


  void setText(const String &text) { this->text = text; rebuildBitmap(); }
  void setColor(uint8_t r, uint8_t g, uint8_t b) { color = strip.Color(r,g,b); }
  void setSpeed(uint16_t ms) { stepDelay = ms; }
  void setFontScale(uint8_t scale) { fontScale = scale < 1 ? 1 : scale; rebuildBitmap(); }

  void reset() { offsetX = MATRIX_WIDTH; lastStep = 0; }

  void step() {
    unsigned long now = millis();
    if (now - lastStep < stepDelay) return;
    lastStep = now;

    // Clear frame
    for (uint16_t y = 0; y < MATRIX_HEIGHT; y++) {
      for (uint16_t x = 0; x < MATRIX_WIDTH; x++) {
        strip.setPixelColor(displayToIndex(x, y), 0);
      }
    }

    // Draw visible window of the bitmap at current offsetX
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

 private:
  Adafruit_NeoPixel &strip;
  String text;
  uint32_t color = 0xFFFFFF;
  uint16_t stepDelay = 50;
  long offsetX = MATRIX_WIDTH;
  unsigned long lastStep = 0;
  uint8_t fontScale = 1;

  // Prepared bitmap: (fontScale*7) rows x bmpWidth columns
  std::vector<uint8_t> bitmap;
  uint16_t bmpWidth = 0;

  void rebuildBitmap() {
    // Compute total width (each glyph 5 cols + 1 space) scaled
    bmpWidth = max<uint16_t>(1, text.length() ? (text.length()*6*fontScale - fontScale) : 1);
    bitmap.assign(fontScale * 7 * bmpWidth, 0);
    uint16_t cursor = 0;
    for (size_t i = 0; i < text.length(); i++) {
      const uint8_t* glyph = glyph5x7(toupper(text[i]));
      for (int col = 0; col < 5; col++) {
        for (uint8_t sx = 0; sx < fontScale; sx++) {
          if (cursor + col*fontScale + sx >= bmpWidth) break;
          uint8_t bits = glyph[col];
          for (int row = 0; row < 7; row++) {
            for (uint8_t sy = 0; sy < fontScale; sy++) {
              if (bits & (1 << row)) {
                bitmap[(row*fontScale + sy) * bmpWidth + (cursor + col*fontScale + sx)] = 1;
              }
            }
          }
        }
      }
      cursor += 6 * fontScale; // 5*scale + 1*scale space
    }
    offsetX = MATRIX_WIDTH;
  }
};
