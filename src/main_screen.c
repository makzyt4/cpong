#include "../include/color.h"
#include "../include/main_screen.h"
#include "../include/text.h"

#define MENUS_FONT_SIZE 3

int8_t selectionIndex = 0;

void loop(CPG_Screen* screen) {
    CPG_Text menus[] = {
        (CPG_Text){
            "New game", 
            CPG_SCREEN_WIDTH / 2 - 96, 
            CPG_SCREEN_HEIGHT / 2 - 64,
            MENUS_FONT_SIZE},
        (CPG_Text){
            "Options", 
            CPG_SCREEN_WIDTH / 2 - 96, 
            CPG_SCREEN_HEIGHT / 2 - 34,
            MENUS_FONT_SIZE},
        (CPG_Text){
            "Quit", 
            CPG_SCREEN_WIDTH / 2 - 96, 
            CPG_SCREEN_HEIGHT / 2 - 4,
            MENUS_FONT_SIZE}
    };
    const uint8_t MENUS_SIZE = sizeof(menus) / sizeof(menus[0]);

    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_UP:
                        if (selectionIndex == 0) {
                            selectionIndex = MENUS_SIZE - 1;
                        } else {
                            selectionIndex--;
                        }
                        break;
                    case SDLK_DOWN:
                        if (selectionIndex == MENUS_SIZE - 1) {
                            selectionIndex = 0;
                        } else {
                            selectionIndex++;
                        }
                        break;
                    case SDLK_RETURN:
                        if (selectionIndex == MENUS_SIZE - 1) {
                            screen->code = CPG_QUIT;
                        }
                }
                break;
            case SDL_QUIT:
                screen->code = CPG_QUIT;
                return;
        }
    }

    CPG_Display_Clear(screen->display, CPG_BLACK);

    uint8_t i;
    for (i = 0; i < MENUS_SIZE; i++) {
        CPG_Color color = (selectionIndex == i) ? CPG_WHITE : CPG_GRAY;
        CPG_Display_SetColor(screen->display, color);
        CPG_Display_DrawText(screen->display, &menus[i]);
    }

    CPG_Display_Refresh(screen->display);
    SDL_Delay(16);
}

CPG_Screen* CPG_MainScreen_Init(CPG_Display* display) {
    return CPG_Screen_Init(display, loop);
}
