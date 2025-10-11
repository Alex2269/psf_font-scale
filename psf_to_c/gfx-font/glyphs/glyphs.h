#ifndef GLYPHS_H
#define GLYPHS_H

#include <stdint.h>
#include "font.h"

extern void DrawPixel(uint16_t x, uint16_t y, uint32_t color);

int utf8_decode(const char* str, uint32_t* out_codepoint);

const GlyphPointerMap* Font_FindGlyph(const Font* font, uint32_t unicode);

void DrawGlyph(const uint8_t* glyph, int charsize, int width, int height,
               uint16_t x, uint16_t y, uint32_t color);

void DrawGlyphScaled(const uint8_t* glyph, int width, int height, int bytes_per_glyph,
                     int x, int y, int scale, uint32_t color,
                     void (*DrawPixelFunc)(uint16_t, uint16_t, uint32_t));

void Font_DrawChar(const Font* font, uint32_t codepoint,
                   uint16_t x, uint16_t y, uint32_t color);

void Font_DrawTextScaled(const Font* font, const char* text,
                         int x, int y, int spacing, int scale, uint32_t color,
                         void (*DrawPixelFunc)(uint16_t, uint16_t, uint32_t));

#endif // GLYPHS_H
