// Simple 16x16 LED matrix test: light pixels from index 0 to last
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "MatrixMapping.h"
#include "ScrollingText.h"
#include "StaticText.h"


// You can override these via -D flags in platformio.ini if needed
#ifndef LED_PIN
#define LED_PIN 21 // Default data pin; set to your actual LED data pin
#endif

// PANEL CONFIG: Change PANELS_X to add more 16x16 segments to the right
#ifndef PANELS_X
#define PANELS_X 3 // Broj panela horizontalno (npr. 2 = 32x16, 3 = 48x16)
#endif
#ifndef PANELS_Y
#define PANELS_Y 1 // Broj panela vertikalno
#endif

#define PANEL_WIDTH 16
#define PANEL_HEIGHT 16
#define MATRIX_WIDTH (PANELS_X * PANEL_WIDTH)
#define MATRIX_HEIGHT (PANELS_Y * PANEL_HEIGHT)
#ifndef LED_BRIGHTNESS
#define LED_BRIGHTNESS 255 // 0-255; keep low for safety when testing
#endif

#define NUM_PIXELS (MATRIX_WIDTH * MATRIX_HEIGHT)

Adafruit_NeoPixel strip(NUM_PIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);
ScrollingText scroller(strip);
StaticText staticText(strip);

// Using ScrollingText/MatrixMapping libs

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
  staticText.setColor(255,0,0);
  staticText.setFontScale(1); // 10x14
  staticText.setCentered(true);
  staticText.setAntiFlicker(true);
  staticText.render(true);
}

unsigned long lastTimeUpdate = 0;
char timeStr[16];

void loop() {
  unsigned long now = millis();
  // Update time string every 100ms
  if (now - lastTimeUpdate > 100) {
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