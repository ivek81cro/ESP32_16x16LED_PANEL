// 16x16 WS2812 panel on ESP32-C3, data on GPIO 21, serpentine order starting bottom-right
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

// Panel configuration
static const uint8_t PIN_LED = 21;        // Data pin
static const uint16_t PANEL_W = 16;
static const uint16_t PANEL_H = 32;
static const uint16_t NUM_LEDS = PANEL_W * PANEL_H; // 256
static const uint8_t LED_BRIGHTNESS = 64; // brightness level (0-255)

// Animation configuration
static const uint16_t STEP_DELAY_MS = 40; // speed; lower is faster

Adafruit_NeoPixel strip(NUM_LEDS, PIN_LED, NEO_GRB + NEO_KHZ800);

// Map logical (x,y) to 1D index with serpentine (boustrophedon) layout
// Origin (0,0) is bottom-left; first row wired right->left starting at bottom-right per user
static inline uint16_t xyToIndex(uint16_t x, uint16_t y) {
  // y: 0 bottom ... H-1 top
  // For even-numbered rows from bottom (y even), wiring goes right->left
  // For odd-numbered rows, wiring goes left->right
  // But the physical chain starts at bottom-right as index 0.
  // We'll compute index such that (x=15,y=0) -> 0, then snake across.
  uint16_t base = y * PANEL_W;
  bool evenRowFromBottom = (y % 2 == 0);
  if (evenRowFromBottom) {
    // right -> left
    return base + (PANEL_W - 1 - x);
  } else {
    // left -> right
    return base + x;
  }
}

// 16x16 bitmap for a smiley face (1 = yellow, 0 = transparent)
static const uint8_t smiley[16][16] = {
  {0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0},
  {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,1,1,0,0,1,1,1,1,1,1,0,0,1,1,1},
  {1,1,1,0,0,1,1,1,1,1,1,0,0,1,1,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,1,1,1,1,1,1,1,1,1,1,1,1,0,1},
  {1,1,0,1,1,1,1,1,1,1,1,1,1,0,1,1},
  {1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1},
  {1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1},
  {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
  {0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0},
};

// Yellow color
#define SMILEY_COLOR strip.Color(255, 255, 0)

void setup() {
  strip.begin();
  strip.clear();
  strip.setBrightness(LED_BRIGHTNESS); // adjust if panel too bright
  strip.show();
}

void loop() {
  static int yOffset = 0;
  static int direction = 1; // 1 = up, -1 = down

  strip.clear();

  // Draw the smiley at current yOffset, rotated 90 degrees clockwise
  for (uint8_t yRot = 0; yRot < 16; ++yRot) {
    int panelY = yRot + yOffset;
    if (panelY < 0 || panelY >= PANEL_H) continue;
    for (uint8_t xRot = 0; xRot < 16; ++xRot) {
      // For 90° CW: srcY = 15 - xRot, srcX = yRot
      uint8_t srcY = 15 - xRot;
      uint8_t srcX = yRot;
      if (smiley[srcY][srcX]) {
        uint16_t idx = xyToIndex(xRot, panelY);
        strip.setPixelColor(idx, SMILEY_COLOR);
      }
    }
  }

  strip.show();

  // Bounce smiley up and down
  yOffset += direction;
  if (yOffset > (PANEL_H - 16)) {
    yOffset = PANEL_H - 16;
    direction = -1;
  } else if (yOffset < 0) {
    yOffset = 0;
    direction = 1;
  }

  delay(STEP_DELAY_MS);
}