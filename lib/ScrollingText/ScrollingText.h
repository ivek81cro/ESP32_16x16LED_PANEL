#pragma once
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <vector>
#include <ctype.h>
#include "MatrixMapping.h"
#include "SimpleFont5x7.h"

class ScrollingText {
 public:
  explicit ScrollingText(Adafruit_NeoPixel &strip);

  void setText(const String &text);
  void setColor(uint8_t r, uint8_t g, uint8_t b);
  void setSpeed(uint16_t ms);
  void setFontScale(uint8_t scale);

  void reset();
  void step();

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

  void rebuildBitmap();
};
