#include "../include/color.h"
#include "../include/main_screen.h"
#include "../include/text.h"

#define MENUS_FONT_SIZE 3

void CPG_GameScreen_Loop(CPG_Screen* screen) {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                screen->code = CPG_QUIT;
                return;
        }
    }

    CPG_Text t = {"Text", 50, 50, 1};
    SDL_Rect r = {50, 50, 50, 50};

    CPG_Display_Clear(screen->display, CPG_BLACK);
    CPG_Display_SetColor(screen->display, CPG_RED);
    CPG_Display_DrawRect(screen->display, &r);
    CPG_Display_SetColor(screen->display, CPG_WHITE);
    CPG_Display_DrawText(screen->display, &t);
    CPG_Display_Refresh(screen->display);
    SDL_Delay(16);
}

CPG_Screen* CPG_GameScreen_Init(CPG_Display* display) {
    return CPG_Screen_Init(display, CPG_GameScreen_Loop);
}
