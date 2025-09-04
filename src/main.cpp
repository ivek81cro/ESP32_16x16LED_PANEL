
#include <Arduino.h>
#include <FastLED.h>

#define NUM_PANELS 2
#define PANEL_WIDTH 16
#define PANEL_HEIGHT 16
#define NUM_LEDS (NUM_PANELS * PANEL_WIDTH * PANEL_HEIGHT)
#define DATA_PIN 21

CRGB leds[NUM_LEDS];

// Map (x, y, panel) to LED index in serpentine order
int XY(int x, int y, int panel) {
  // Serpentine: even rows left->right, odd rows right->left
  int row = y;
  int col = (row % 2 == 0) ? x : (PANEL_WIDTH - 1 - x);
  int panel_offset = panel * PANEL_WIDTH * PANEL_HEIGHT;
  return panel_offset + row * PANEL_WIDTH + col;
}

// Map a linear scan index (column-wise serpentine: up-down) to (panel, x, y)
void scanIndexToCoordColumnSerpentine(int scanIndex, int &panel, int &x, int &y) {
  int panelSize = PANEL_WIDTH * PANEL_HEIGHT; // 256
  panel = scanIndex / panelSize;
  int offsetInPanel = scanIndex % panelSize;
  // Column-major order within a panel
  x = offsetInPanel / PANEL_HEIGHT;               // 0..15 columns
  int posInColumn = offsetInPanel % PANEL_HEIGHT; // 0..15 within column
  bool downwards = (x % 2 == 0);                  // even column: top->bottom
  y = downwards ? posInColumn : (PANEL_HEIGHT - 1 - posInColumn);
}

void setup() {
  FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(255);
  FastLED.clear();
  FastLED.show();
}

// Snake animation variables
int snake_length = 50;
int snake_head = 0;

void loop() {
  FastLED.clear();
  // Draw snake
  for (int i = 0; i < snake_length; i++) {
  int pos = (snake_head - i + NUM_LEDS) % NUM_LEDS;
  int panel, x, y;
  scanIndexToCoordColumnSerpentine(pos, panel, x, y);
    int led_idx = XY(x, y, panel);
    // Svaka LED zmije ima drugu boju, boje se pomiču s glavom
    uint8_t hue = (snake_head * 4 + i * 8) % 255;
    leds[led_idx] = CHSV(hue, 255, 255);
  }
  FastLED.show();
  delay(30);
  snake_head = (snake_head + 1) % NUM_LEDS;
}