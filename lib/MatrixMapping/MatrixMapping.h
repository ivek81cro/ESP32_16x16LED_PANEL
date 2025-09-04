#pragma once

#include <Arduino.h>

// Panel and display configuration (override via build_flags if needed)
#ifndef PANEL_WIDTH
#define PANEL_WIDTH 16
#endif
#ifndef PANEL_HEIGHT
#define PANEL_HEIGHT 16
#endif
#ifndef PANELS_X
#define PANELS_X 4
#endif
#ifndef PANELS_Y
#define PANELS_Y 1
#endif

#ifndef FLIP_Y
#define FLIP_Y 1 // 1 = flip vertically if panel mounted upside-down
#endif

#define MATRIX_WIDTH (PANEL_WIDTH * PANELS_X)
#define MATRIX_HEIGHT (PANEL_HEIGHT * PANELS_Y)

// Map display coordinates (x,y) to physical LED index for chained serpentine 16x16 panels
uint16_t displayToIndex(uint8_t x, uint8_t y);
