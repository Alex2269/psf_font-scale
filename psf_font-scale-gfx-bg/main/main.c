// main.c
#include "main.h"

PSF_Font psfFont12;    // Глобальна змінна для PSF шрифту
PSF_Font psfFont20;    // Інший PSF шрифт
PSF_Font psfFont28;
PSF_Font psfFont32;

int main(void) {
    const int screenWidth = 400;
    const int screenHeight = 150;

    gfx_open(screenWidth,screenHeight,"PSF_Font");
    Display_Set_WIDTH(screenWidth);
    Display_Set_HEIGHT(screenHeight);
    gfx_color(128,127,255);

    // Завантаження PSF шрифту (шлях до вашого файлу)
    psfFont12 = LoadPSFFont("fonts/Uni3-Terminus12x6.psf");
    psfFont20 = LoadPSFFont("fonts/Uni3-Terminus20x10.psf");
    psfFont28 = LoadPSFFont("fonts/Uni3-Terminus28x14.psf");
    psfFont32 = LoadPSFFont("fonts/Uni3-Terminus32x16.psf");

    int scale = 1; // масштаб 1x
    int spacing = 2; // простір між символами px

    // DrawPSFTextScaledWithInvertedBackground(psfFont28, 20, 10, "Текст UTF-8", spacing, scale, YELLOW, 6);
    // DrawPSFTextScaledWithInvertedBackground(psfFont12, 240,10, "Малий Текст", spacing, scale, CYAN, 6);

    // DrawPSFTextScaledWithInvertedBackground(psfFont28, 20, 52, "Текст UTF-8", spacing, scale, GREEN, 6);
    // DrawPSFTextScaledWithInvertedBackground(psfFont28, 20, 94, "Текст UTF-8", spacing, scale, BLUE, 6);

    DrawPSFTextWithInvertedBackground(psfFont28, 20, 10, "Текст UTF-8", spacing, YELLOW, 6);
    DrawPSFTextWithInvertedBackground(psfFont12, 240,10, "Малий Текст", spacing, CYAN, 6);

    DrawPSFTextWithInvertedBackground(psfFont28, 20, 52, "Текст UTF-8", spacing, GREEN, 6);
    DrawPSFTextWithInvertedBackground(psfFont28, 20, 94, "Текст UTF-8", spacing, BLUE, 6);

    while(1) {
        // DrawPSFTextScaled(psfFont28, 20, 10, "Текст UTF-8", spacing, scale, WHITE);
        // DrawPSFText(psfFont28, 20, 50, "Текст UTF-8", spacing, GREEN);
        // DrawPSFText(psfFont12, 20, 90, "Малий Текст UTF-8", 1, YELLOW);
        // DrawPSFTextScaled(psfFont12, 20, 110, "Масштабований Текст", spacing, scale*2, YELLOW);
        gfx_flush();
        usleep(100);
    }

    // Після виходу з циклу звільняємо пам'ять шрифту
    UnloadPSFFont(psfFont12);
    UnloadPSFFont(psfFont20);
    UnloadPSFFont(psfFont28);
    UnloadPSFFont(psfFont32);

    return 0;
}


