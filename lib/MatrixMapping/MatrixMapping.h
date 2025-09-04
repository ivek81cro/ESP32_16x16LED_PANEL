/**
 * @file MatrixMapping.h
 * @brief Pretvaranje logičkih koordinata (x,y) u linearni indeks LED pikselâ za niz serijski spojenih
 *        16x16 (ili generički W x H) NeoPixel panela u serpentin (boustrophedon) rasporedu.
 *
 * Koncept:
 *  - Panely su numerirani s lijeva na desno, odozgo nadolje (row-major po panelima).
 *  - Unutar svakog panela redovi (y) idu odozgo prema dolje.
 *  - Unutar panela svaki parni red (y % 2 == 0) ide lijevo→desno, a svaki neparni desno→lijevo (serpentin).
 *  - Opcionalno se može invertirati globalni Y (FLIP_Y) ako je cijela matrica fizički okrenuta.
 *
 * Konfiguracija:
 *  - Makroe je moguće preglasati u build_flags (PlatformIO: build_flags = -DPANELS_X=3 ...)
 *  - Ako se želi izbjeći warning redefinition, postavite makroe prije #include "MatrixMapping.h" u svom .cpp.
 */
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

// 1 = invert global Y koordinatu (korisno kad je panel naopako montiran).
#ifndef FLIP_Y
#define FLIP_Y 1
#endif

#define MATRIX_WIDTH (PANEL_WIDTH * PANELS_X)
#define MATRIX_HEIGHT (PANEL_HEIGHT * PANELS_Y)

/**
 * @brief Mapira logičku koordinatu (x,y) u linearni indeks LED-a.
 * @param x [0, MATRIX_WIDTH-1]
 * @param y [0, MATRIX_HEIGHT-1]
 * @return 0-based indeks unutar ukupnog niza piksela.
 */
uint16_t displayToIndex(uint8_t x, uint8_t y);
