#pragma once

#include <Arduino.h>
#include <vector>

/**
 * @brief Izgradi monokromatski bitmap teksta korištenjem 5x7 fonta, skaliranog faktorom fontScale.
 *
 * Layout memorije: (fontScale * 7) redova × outWidth stupaca, red-major.
 * Širina: len ? (len * 6 * fontScale - fontScale) : 1  (5 stupaca + 1 razmak po znaku, bez završnog razmaka).
 * Svaka ćelija = 0 (piksel off) ili 1 (piksel on).
 *
 * @param text Ulazni tekst (ASCII 32..90 podržano; ostalo mapirano na space).
 * @param fontScale Faktor skaliranja (>=1).
 * @param outBitmap Referenca na vektor koji će biti popunjen podacima.
 * @param outWidth Vraća izračunatu širinu u pikselima.
 */
void buildTextBitmap(const String &text, uint8_t fontScale, std::vector<uint8_t> &outBitmap, uint16_t &outWidth);
