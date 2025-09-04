#pragma once
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <vector>
#include <ctype.h>
#include "MatrixMapping.h"
#include "SimpleFont5x7.h"
#include <TextBitmap.h>

/**
 * @class ScrollingText
 * @brief Horizontalno pomiče tekst kroz matricu; svaki frame briše display i iscrtava vidljivi prozor.
 * Upotreba:
 *   ScrollingText sc(strip); sc.setText("HELLO"); u loop(): sc.step();
 */
class ScrollingText {
 public:
  explicit ScrollingText(Adafruit_NeoPixel &strip);

  void setText(const String &text);          // Postavi novi tekst i rebuild bitmap.
  void setColor(uint8_t r, uint8_t g, uint8_t b); // RGB boja teksta.
  void setSpeed(uint16_t ms);                // Kašnjenje (ms) između pomaka 1 px.
  void setFontScale(uint8_t scale);          // Skaliranje fonta (>=1).

  void reset(); // Vrati offset na start (desno izvan ekrana).
  void step();  // Pozivati u loop(); radi vremensko upravljanje i pomak.

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
