#pragma once

#include <Arduino.h>
#include <vector>

// Helper to build a monochrome bitmap for a 5x7 font text string scaled by fontScale.
// Output bitmap layout: (fontScale*7) rows x computedWidth columns, row-major.
// Width formula matches existing logic: len ? (len*6*fontScale - fontScale) : 1
// Each glyph = 5 columns + 1 column space (scaled). Trailing space removed.
void buildTextBitmap(const String &text, uint8_t fontScale, std::vector<uint8_t> &outBitmap, uint16_t &outWidth);
