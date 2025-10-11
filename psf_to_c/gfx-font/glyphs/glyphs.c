#include "glyphs.h"
#include <stdio.h>

// Припускається, що виклик utf8_decode замінено зовнішнім оголошенням

int utf8_decode(const char* str, uint32_t* out_codepoint) {
    unsigned char c = (unsigned char)str[0];
    if (c < 0x80) {
        *out_codepoint = c;
        return 1;
    } else if ((c & 0xE0) == 0xC0) {
        *out_codepoint = ((str[0] & 0x1F) << 6) | (str[1] & 0x3F);
        return 2;
    } else if ((c & 0xF0) == 0xE0) {
        *out_codepoint = ((str[0] & 0x0F) << 12) | ((str[1] & 0x3F) << 6) | (str[2] & 0x3F);
        return 3;
    } else if ((c & 0xF8) == 0xF0) {
        *out_codepoint = ((str[0] & 0x07) << 18) | ((str[1] & 0x3F) << 12) |
        ((str[2] & 0x3F) << 6) | (str[3] & 0x3F);
        return 4;
    }
    *out_codepoint = 0;
    return 1;
}

const GlyphPointerMap* Font_FindGlyph(const Font* font, uint32_t unicode) {
    for (int i = 0; i < font->glyph_count; i++) {
        if (font->glyph_map[i].unicode == unicode) {
            return &font->glyph_map[i];
        }
    }
    return NULL;
}

void DrawGlyph(const uint8_t* glyph, int charsize, int width, int height,
               uint16_t x, uint16_t y, uint32_t color)
{
    int bytes_per_row = (width + 7) / 8;

    for (int row = 0; row < height; row++) {
        for (int byte = 0; byte < bytes_per_row; byte++) {
            uint8_t bits = glyph[row * bytes_per_row + byte];
            for (int bit = 0; bit < 8; bit++) {
                int px = byte * 8 + bit;
                if (px >= width)
                    break;
                if (bits & (0x80 >> bit)) {
                    DrawPixel(x + px, y + row, color);
                }
            }
        }
    }
}

void DrawGlyphScaled(const uint8_t* glyph, int width, int height, int bytes_per_glyph,
                     int x, int y, int scale, uint32_t color,
                     void (*DrawPixelFunc)(uint16_t, uint16_t, uint32_t))
{
    int bytes_per_row = (width + 7) / 8;

    for (int row = 0; row < height; row++) {
        for (int byte = 0; byte < bytes_per_row; byte++) {
            uint8_t bits = glyph[row * bytes_per_row + byte];
            for (int bit = 0; bit < 8; bit++) {
                int px = byte * 8 + bit;
                if (px >= width) break;
                if (bits & (0x80 >> bit)) {
                    int draw_x = x + px * scale;
                    int draw_y = y + row * scale;
                    for (int dx = 0; dx < scale; dx++) {
                        for (int dy = 0; dy < scale; dy++) {
                            DrawPixelFunc(draw_x + dx, draw_y + dy, color);
                        }
                    }
                }
            }
        }
    }
}

void Font_DrawChar(const Font* font, uint32_t codepoint,
                   uint16_t x, uint16_t y, uint32_t color)
{
    const GlyphPointerMap* glyph = Font_FindGlyph(font, codepoint);
    if (!glyph) return;
    DrawGlyph(glyph->glyph, font->char_bytes, font->char_width, font->char_height,
              x, y, color);
}

void Font_DrawTextScaled(const Font* font, const char* text,
                         int x, int y, int spacing, int scale, uint32_t color,
                         void (*DrawPixelFunc)(uint16_t, uint16_t, uint32_t)) {
    int xpos = x;
    int ypos = y;
    while (*text) {
        if (*text == '\n'){
            xpos = x;
            ypos += (font->char_height * scale) + spacing;
            text++;
            continue;
        }
        uint32_t codepoint = 0;
        int bytes = utf8_decode(text, &codepoint);
        const GlyphPointerMap* glyph = Font_FindGlyph(font, codepoint);
        if (!glyph) glyph = Font_FindGlyph(font, 32);
        if (glyph) {
            DrawGlyphScaled(glyph->glyph, font->char_width, font->char_height, font->char_bytes,
                            xpos, ypos, scale, color, DrawPixelFunc);
        }
        xpos += (font->char_width * scale) + spacing;
        text += bytes;
    }
}


