#include "StaticText.h"

void StaticText::rebuild() {
  const size_t len = text.length();
  bmpWidth = len ? (len * 6 * fontScale - fontScale) : 1;
  const uint16_t bmpHeight = fontScale * 7;
  bitmap.assign(bmpWidth * bmpHeight, 0);
  uint16_t cursor = 0;
  for (size_t i = 0; i < len; i++) {
    const uint8_t* glyph = glyph5x7(toupper(text[i]));
    for (int col = 0; col < 5; col++) {
      for (uint8_t sx = 0; sx < fontScale; sx++) {
        if (cursor + col * fontScale + sx >= bmpWidth) break;
        uint8_t bits = glyph[col];
        for (int row = 0; row < 7; row++) {
          for (uint8_t sy = 0; sy < fontScale; sy++) {
            if (bits & (1 << row)) {
              bitmap[(row * fontScale + sy) * bmpWidth + (cursor + col * fontScale + sx)] = 1;
            }
          }
        }
      }
    }
    cursor += 6 * fontScale;
  }
  dirty = false;
}

void StaticText::draw(bool clear) {
  const uint16_t bmpHeight = fontScale * 7;
  if (clear) {
    for (uint16_t y = 0; y < MATRIX_HEIGHT; y++) {
      for (uint16_t x = 0; x < MATRIX_WIDTH; x++) {
        strip.setPixelColor(displayToIndex(x, y), 0);
      }
    }
  }
  int x0 = centered ? (int)((MATRIX_WIDTH - bmpWidth) / 2) : originX;
  int y0 = centered ? (int)((MATRIX_HEIGHT - bmpHeight) / 2) : originY;
  for (uint16_t y = 0; y < bmpHeight; y++) {
    int dy = y0 + (int)y;
    if (dy < 0 || dy >= MATRIX_HEIGHT) continue;
    for (uint16_t x = 0; x < bmpWidth; x++) {
      int dx = x0 + (int)x;
      if (dx < 0 || dx >= MATRIX_WIDTH) continue;
      if (bitmap[y * bmpWidth + x]) {
        strip.setPixelColor(displayToIndex((uint8_t)dx, (uint8_t)dy), color);
      }
    }
  }
  strip.show();
}

void StaticText::render(bool clear) {
  if (dirty) rebuild();
  if (antiFlicker && !clear) {
    drawDiff();
  } else {
    draw(clear);
  }
}

void StaticText::drawDiff() {
  const uint16_t bmpHeight = fontScale * 7;
  int x0 = centered ? (int)((MATRIX_WIDTH - bmpWidth) / 2) : originX;
  int y0 = centered ? (int)((MATRIX_HEIGHT - bmpHeight) / 2) : originY;

  // If no previous, fall back to full draw without clear
  if (!prevValid) {
    draw(false);
  } else {
    // Erase pixels that were on but are now off
    for (uint16_t y = 0; y < prevH; y++) {
      int dy = prevY0 + (int)y;
      if (dy < 0 || dy >= MATRIX_HEIGHT) continue;
      for (uint16_t x = 0; x < prevW; x++) {
        int dx = prevX0 + (int)x;
        if (dx < 0 || dx >= MATRIX_WIDTH) continue;
        uint8_t wasOn = prevBitmap[y * prevW + x];
        // If outside new bounds or now off, turn off
        uint8_t nowOn = 0;
        int ny = y - (prevY0 - y0);
        int nx = x - (prevX0 - x0);
        if (ny >= 0 && ny < (int)bmpHeight && nx >= 0 && nx < (int)bmpWidth) {
          nowOn = bitmap[ny * bmpWidth + nx];
        }
        if (wasOn && !nowOn) {
          strip.setPixelColor(displayToIndex((uint8_t)dx, (uint8_t)dy), 0);
        }
      }
    }
    // Draw pixels that are on now
    for (uint16_t y = 0; y < bmpHeight; y++) {
      int dy = y0 + (int)y;
      if (dy < 0 || dy >= MATRIX_HEIGHT) continue;
      for (uint16_t x = 0; x < bmpWidth; x++) {
        int dx = x0 + (int)x;
        if (dx < 0 || dx >= MATRIX_WIDTH) continue;
        uint8_t nowOn = bitmap[y * bmpWidth + x];
        // Check if it was on before at that physical position
        uint8_t wasOn = 0;
        int py = y + (y0 - prevY0);
        int px = x + (x0 - prevX0);
        if (py >= 0 && py < (int)prevH && px >= 0 && px < (int)prevW) {
          wasOn = prevBitmap[py * prevW + px];
        }
        if (nowOn && !wasOn) {
          strip.setPixelColor(displayToIndex((uint8_t)dx, (uint8_t)dy), color);
        }
      }
    }
    strip.show();
  }

  // Save current as previous
  prevW = bmpWidth;
  prevH = bmpHeight;
  prevX0 = x0;
  prevY0 = y0;
  prevBitmap = bitmap;
  prevValid = true;
}
