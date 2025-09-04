#pragma once

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <vector>
#include <ctype.h>
#include "MatrixMapping.h"
#include "SimpleFont5x7.h"
#include <TextBitmap.h>

class StaticText {
public:
  explicit StaticText(Adafruit_NeoPixel &strip) : strip(strip) {}

  void setText(const String &t) { text = t; dirty = true; }
  void setFontScale(uint8_t s) { fontScale = s < 1 ? 1 : s; dirty = true; }
  void setColor(uint8_t r, uint8_t g, uint8_t b) { color = strip.Color(r, g, b); }
  void setCentered(bool c) { centered = c; }
  void setOrigin(int16_t x, int16_t y) { originX = x; originY = y; centered = false; }
  void setAntiFlicker(bool on) { antiFlicker = on; }

  uint16_t width() const { return bmpWidth; }
  uint16_t height() const { return (uint16_t)(fontScale * 7); }

  // Render current text to the matrix; optionally clear first.
  void render(bool clear = true);

private:
  Adafruit_NeoPixel &strip;
  String text;
  uint32_t color = 0xFFFFFF;
  uint8_t fontScale = 1;
  bool centered = true;
  int16_t originX = 0, originY = 0;

  bool dirty = true;
  std::vector<uint8_t> bitmap; // (fontScale*7) rows x bmpWidth cols, row-major
  uint16_t bmpWidth = 0;
  bool antiFlicker = true;

  // Previous frame state for diff rendering
  std::vector<uint8_t> prevBitmap;
  uint16_t prevW = 0;
  uint16_t prevH = 0;
  int16_t prevX0 = 0;
  int16_t prevY0 = 0;
  bool prevValid = false;

  void rebuild();
  void draw(bool clear);
  void drawDiff();
};
