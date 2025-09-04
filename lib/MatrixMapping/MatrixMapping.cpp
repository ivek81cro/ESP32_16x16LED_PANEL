#include "MatrixMapping.h"

static inline uint16_t panelSerpentineIndex(uint8_t local_x, uint8_t local_y) {
  if ((local_y & 1) == 0) {
    return local_y * PANEL_WIDTH + local_x;
  } else {
    return local_y * PANEL_WIDTH + (PANEL_WIDTH - 1 - local_x);
  }
}

uint16_t displayToIndex(uint8_t x, uint8_t y) {
#if FLIP_Y
  y = (MATRIX_HEIGHT - 1) - y;
#endif
  uint8_t panel_x = x / PANEL_WIDTH;
  uint8_t panel_y = y / PANEL_HEIGHT;
  uint8_t local_x = x % PANEL_WIDTH;
  uint8_t local_y = y % PANEL_HEIGHT;

  uint16_t panel_linear = panel_y * PANELS_X + panel_x;
  uint16_t base = panel_linear * (PANEL_WIDTH * PANEL_HEIGHT);
  return base + panelSerpentineIndex(local_x, local_y);
}
