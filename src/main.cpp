// Simple 16x16 LED matrix test: light pixels from index 0 to last
/**
 * @file main.cpp
 * @brief Primjer: statički prikaz vremena (mm:ss:ms) na višepanelnoj NeoPixel matrici (serpentin mapping).
 *
 */

#ifndef LED_PIN
#define LED_PIN 21
#endif

#ifndef LED_BRIGHTNESS
#define LED_BRIGHTNESS 255
#endif

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "MatrixMapping.h" // koristi prethodno definirane makroe
#include "ScrollingText.h"
#include "StaticText.h"

#define NUM_PIXELS (MATRIX_WIDTH * MATRIX_HEIGHT)

Adafruit_NeoPixel strip(NUM_PIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);
ScrollingText scroller(strip);
StaticText staticText(strip);

// Demo koristi StaticText (anti-flicker) za prikaz brojača vremena.

void setup() {
  Serial.begin(115200);
  delay(50);
  Serial.println("Starting 32x16 scrolling text demo...");
  Serial.print("Pixels: ");
  Serial.println(NUM_PIXELS);
  Serial.print("Pin: ");
  Serial.println(LED_PIN);

  strip.begin();
  strip.setBrightness(LED_BRIGHTNESS);
  strip.clear();
  strip.show();

  staticText.setText("00:00:000");
  staticText.setColor(0,255,0);
  staticText.setFontScale(1); // Skaliranje fonta (1 => 5x7, 2 => 10x14 ...)
  staticText.setCentered(true);
  staticText.setAntiFlicker(true);
  staticText.render(true);
}

unsigned long lastTimeUpdate = 0;
char timeStr[16];

void loop() {
  unsigned long now = millis();
  // Ažuriraj prikaz svakih 100 ms (differences only -> manji flicker)
  if (now - lastTimeUpdate > 10) {
    unsigned long ms = now % 1000;
    unsigned long totalSec = now / 1000;
    unsigned long min = totalSec / 60;
    unsigned long sec = totalSec % 60;
    snprintf(timeStr, sizeof(timeStr), "%02lu:%02lu:%03lu", min, sec, ms);
  staticText.setText(timeStr);
  // Render without full clear to avoid flicker
  staticText.render(false);
    lastTimeUpdate = now;
  }
}