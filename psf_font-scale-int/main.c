// main.c
#include "main.h"

PSF_Font psfFont;      // Глобальна змінна для PSF шрифту
PSF_Font psfFont12;    // Інший PSF шрифт

int fontSize = 24;
int LineSpacing = 0;

int main(void) {
    const int screenWidth = 400;
    const int screenHeight = 150;

    int osc_width = screenWidth;
    int osc_height = screenHeight - 75;

    // Встановлюємо прапорець для мультисемплінгу (покращення якості графіки)
    SetConfigFlags(FLAG_MSAA_4X_HINT);

    InitWindow(screenWidth, screenHeight, "Raylib Oscilloscope with Trigger and Scaling");

    // Завантаження PSF шрифту (шлях до вашого файлу)
    psfFont = LoadPSFFont("fonts/Uni3-TerminusBold32x16.psf");
    psfFont12 = LoadPSFFont("fonts/Uni3-Terminus12x6.psf");

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        // frameTime += GetFrameTime();
        // if (frameTime * 1000.0f >= oscData.refresh_rate_ms) {
        //     read_usb_device(&oscData);
        //     update_trigger_indices(&oscData);
        //     frameTime = 0.0f;
        // }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawRectangle(0, 0, osc_width, osc_height, BLACK);

        // DrawPSFText(psfFont, 20, 20, "Текст UTF-8", 0, WHITE);
        DrawPSFTextScaled(psfFont12, 20, 20, "Текст UTF-8", 0, 2, WHITE); // масштаб 2x

        DrawPSFText(psfFont, 20, osc_height + 20,
                            "Текст UTF-8", 0, BLACK);

        DrawPSFText(psfFont12, 20, osc_height + 50,
                            "Малий Текст UTF-8", 0, BLACK);

        EndDrawing();
    }

    // Після виходу з циклу звільняємо пам'ять шрифту
    UnloadPSFFont(psfFont);

    CloseWindow();

    return 0;
}


