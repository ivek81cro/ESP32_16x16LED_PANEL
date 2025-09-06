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
#define LED_BRIGHTNESS 255
#endif

#define NUM_PIXELS (MATRIX_WIDTH * MATRIX_HEIGHT)

Adafruit_NeoPixel strip(NUM_PIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);
ScrollingText scroller(strip);
StaticText staticText(strip);
TextDisplayMode textDisplay(staticText, scroller);

unsigned long lastTimeUpdate = 0;
char timeStr[16];
bool useScroll = false; // promijeni na true za scroll prikaz
static int lastLen = 0;

void setup() {
  Serial.begin(115200);
  delay(50);
  Serial.println("Starting 32x16 scrolling text demo...");
  strip.setBrightness(LED_BRIGHTNESS);
  strip.clear();
  strip.show();
  // Primjer: prikaz statičnog teksta
  textDisplay.showText("Sljedeci natjecatelj: Zeljko Marinovic, 111", useScroll, 0, 255, 0, 2); // static prikaz
  // Primjer: prikaz scroll teksta
  // textDisplay.showText("HELLO WORLD", true, 255, 0, 0, 1); // scroll prikaz
}
void loop() {
  unsigned long now = millis();
  if (!useScroll) {
    if (now - lastTimeUpdate > 10) {
      unsigned long ms = now % 1000;
      unsigned long totalSec = now / 1000;
      unsigned long min = totalSec / 60;
      unsigned long sec = totalSec % 60;
      snprintf(timeStr, sizeof(timeStr), "%02lu:%02lu:%03lu", min, sec, ms);
      int curLen = strlen(timeStr);
      // Prikaz statičnog vremena
      textDisplay.showText(timeStr, false, 0, 255, 0, 1);
      lastLen = curLen;
      lastTimeUpdate = now;
    }
  } else {
    // Prikaz scroll teksta
    textDisplay.loop();
  }
}