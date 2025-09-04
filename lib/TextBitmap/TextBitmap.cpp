#include "TextBitmap.h"
#include "SimpleFont5x7.h"
#include <ctype.h>

void buildTextBitmap(const String &text, uint8_t fontScale, std::vector<uint8_t> &outBitmap, uint16_t &outWidth) {
  if (fontScale < 1) fontScale = 1; // safety
  const size_t len = text.length();
  outWidth = len ? (len * 6 * fontScale - fontScale) : 1;
  const uint16_t height = fontScale * 7;
  outBitmap.assign(outWidth * height, 0);
  uint16_t cursor = 0;
  for (size_t i = 0; i < len; i++) {
  const uint8_t *glyph = glyph5x7(toupper(text[i])); // 5 stupaca, bit0 = top pixel
    for (int col = 0; col < 5; col++) {
      for (uint8_t sx = 0; sx < fontScale; sx++) {
        uint16_t tx = cursor + col * fontScale + sx;
        if (tx >= outWidth) break;
        uint8_t bits = glyph[col];
        for (int row = 0; row < 7; row++) {
          if (bits & (1 << row)) {
            for (uint8_t sy = 0; sy < fontScale; sy++) {
              uint16_t ty = row * fontScale + sy;
              outBitmap[ty * outWidth + tx] = 1;
            }
          }
        }
      }
    }
    cursor += 6 * fontScale; // advance incl. one scaled space
  }
}
