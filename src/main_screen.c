#include "../include/color.h"
#include "../include/main_screen.h"
#include "../include/text.h"

int8_t selectionIndex = 0;

void CPG_MainScreen_Loop(CPG_Screen* screen) {
    CPG_Text logo = {
        "C Pong",
        CPG_SCREEN_WIDTH / 2 - 186, 
        CPG_SCREEN_HEIGHT / 2 - 164,
        CPG_LOGO_SIZE
    };
    CPG_Text menus[] = {
        (CPG_Text){
            "New game", 
            CPG_SCREEN_WIDTH / 2 - 96, 
            CPG_SCREEN_HEIGHT / 2 - 64,
            CPG_MENUS_FONTSIZE},
        (CPG_Text){
            "Help", 
            CPG_SCREEN_WIDTH / 2 - 96, 
            CPG_SCREEN_HEIGHT / 2 - 34,
            CPG_MENUS_FONTSIZE},
        (CPG_Text){
            "Quit", 
            CPG_SCREEN_WIDTH / 2 - 96, 
            CPG_SCREEN_HEIGHT / 2 - 4,
            CPG_MENUS_FONTSIZE}
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
                        switch (selectionIndex) {
                            case 0:
                                screen->code = CPG_GAME;
                                break;
                            case 1:
                                screen->code = CPG_HELP;
                                break;
                            case 2:
                                screen->code = CPG_QUIT;
                                break;
                        }
                }
                break;
            case SDL_QUIT:
                screen->code = CPG_QUIT;
                return;
        }
    }

    CPG_Display_Clear(screen->display, CPG_BLACK);
    CPG_Display_SetColor(screen->display, CPG_SILVER);
    CPG_Display_DrawText(screen->display, &logo);

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
    return CPG_Screen_Init(display, CPG_MainScreen_Loop);
}
