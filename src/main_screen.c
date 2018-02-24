#include "../include/color.h"
#include "../include/main_screen.h"
#include "../include/text.h"

void loop(CPG_Screen* screen) {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            screen->code = CPG_QUIT;
            return;
        }
    }

    CPG_Text t = {"Testing...", 50, 50, 1};

    CPG_Display_Clear(screen->display, CPG_BLACK);
    CPG_Display_SetColor(screen->display, CPG_BLUE);
    CPG_Display_DrawText(screen->display, &t, 1);
    CPG_Display_Refresh(screen->display);
    SDL_Delay(16);
}

CPG_Screen* CPG_MainScreen_Init(CPG_Display* display) {
    return CPG_Screen_Init(display, loop);
}
