// Simple 16x16 LED matrix test: light pixels from index 0 to last
/**
 * @file main.cpp
 * @brief Primjer: statički prikaz vremena (mm:ss:ms) na višepanelnoj NeoPixel matrici (serpentin mapping).
 *
 */

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "MatrixMapping.h" // koristi prethodno definirane makroe
#include "ScrollingText.h"
#include "StaticText.h"
#include "TextDisplayMode.h"

#ifndef LED_PIN
#define LED_PIN 21
#endif

#ifndef LED_BRIGHTNESS
#define LED_BRIGHTNESS 64
#endif

#define NUM_PIXELS (MATRIX_WIDTH * MATRIX_HEIGHT)

Adafruit_NeoPixel strip(NUM_PIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);
ScrollingText scroller(strip);
StaticText staticText(strip);
StaticTextDisplay staticDisplay(staticText);
ScrollingTextDisplay scrollDisplay(scroller);
TextDisplayMode textDisplay(staticDisplay, scrollDisplay);

unsigned long lastTimeUpdate = 0;
char timeStr[16];
bool showTimer = true; // promijeni na true za prikaz tajmera
static int lastLen = 0;

void setup() {
  Serial.begin(115200);
  delay(50);
  Serial.println("Starting 32x16 scrolling text demo...");
  strip.setBrightness(LED_BRIGHTNESS);
  strip.clear();
  strip.show();
  // Primjer: prikaz statičnog teksta
  textDisplay.showText("next 111", false, 0, 255, 0, 1); // statični tekst
  staticDisplay.setBlink(true, 500); // omogući blinkanje svakih 500ms
  // Primjer: prikaz scroll teksta
  // textDisplay.showText("HELLO WORLD", true, 255, 0, 0, 1); // scroll prikaz
}
void loop() {
  unsigned long now = millis();
  if (showTimer) {
    if (now - lastTimeUpdate > 10) {
      unsigned long ms = now % 1000;
      unsigned long totalSec = now / 1000;
      unsigned long min = totalSec / 60;
      unsigned long sec = totalSec % 60;
      snprintf(timeStr, sizeof(timeStr), "%02lu:%02lu:%03lu", min, sec, ms);
      int curLen = strlen(timeStr);
      // Prikaz tajmera
      textDisplay.showText(timeStr, false, 0, 255, 0, 1);
      lastLen = curLen;
      lastTimeUpdate = now;
    }
  } else {
    // Prikaz statičnog teksta (ili scroll)
    textDisplay.loop();
  }
}