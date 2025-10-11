#ifndef FONT_H
#define FONT_H

#include <stdint.h>
#include "glyphmap.h"

// Структура для опису шрифту повністю
typedef struct {
    const char* name;                    // Ім'я шрифту
    int char_width;                     // Ширина символу в пікселях
    int char_height;                    // Висота символу в пікселях
    int char_bytes;                     // Розмір гліфа (байт)
    const GlyphPointerMap* glyph_map;  // Масив гліфів Unicode -> glyph data
    int glyph_count;                   // Кількість гліфів у масиві
} Font;

#endif // FONT_H
