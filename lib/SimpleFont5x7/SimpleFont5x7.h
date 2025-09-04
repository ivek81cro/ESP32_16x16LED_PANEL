#pragma once
#include <Arduino.h>

// 5x7 font data for ASCII 32..90 (space to 'Z')
// Each glyph is 5 bytes (columns), LSB = top pixel
extern const uint8_t FONT5x7[59][5];

inline const uint8_t* glyph5x7(char c) {
  if (c < 32 || c > 90) c = ' ';
  return FONT5x7[c - 32];
}
