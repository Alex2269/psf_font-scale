// main.c

#include "main.h"
#include "glyphs.h"

int main(void) {
    const int screenWidth = 600;
    const int screenHeight = 240;
    // Ініціалізація графіки, кольорів тощо
    gfx_open(screenWidth,screenHeight,"PSF_Font");
    Display_Set_WIDTH(screenWidth);
    Display_Set_HEIGHT(screenHeight);
    gfx_color(128,127,255);


    // Опис шрифту як структури Font
    extern const Font Terminus12x6_font;
    extern const Font TerminusBold18x10_font;
    // Опис шрифту як структури Font
    extern const Font TerminusBold32x16_font;

    int spacing = 2;
    int scale = 1;
    // Приклад виклику малювання тексту з масштабуванням
    Font_DrawTextScaled(&Terminus12x6_font, "Hello Привіт", 20, 10, spacing, scale*1, GREEN, DrawPixel);
    Font_DrawTextScaled(&Terminus12x6_font, "Hello Привіт", 20, 25, spacing, scale*2, GREEN, DrawPixel);
    Font_DrawTextScaled(&Terminus12x6_font, "Hello Привіт", 20, 50, spacing, scale*3, GREEN, DrawPixel);
    Font_DrawTextScaled(&TerminusBold18x10_font, "Hello Привіт", 20, 90, spacing, scale, YELLOW, DrawPixel);
    Font_DrawTextScaled(&TerminusBold32x16_font, "Hello Привіт", 20, 110, spacing, scale, YELLOW, DrawPixel);

    while(1) {
        gfx_flush();
        usleep(1000);
    }

    return 0;
}


