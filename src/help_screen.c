#include "../include/color.h"
#include "../include/help_screen.h"
#include "../include/text.h"

void CPG_HelpScreen_Loop(CPG_Screen* screen) {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_KEYDOWN:
                screen->code = CPG_MAIN_MENU;
                break;
            case SDL_QUIT:
                screen->code = CPG_QUIT;
                return;
        }
    }
    
    CPG_Text bigText = { "Help", 100, 80, 5 };
    CPG_Text text = {
        "Two players are using pads to bounce\n"
        "the ball. When the ball reaches left\n"
        "or right border of screen then the\n"
        "opposite player earns a point. Game\n"
        "end when one of players scores 15\n"
        "points.\n\n"
        "Press any key to exit.",
        100, 130, 2
    };


    CPG_Display_Clear(screen->display, CPG_BLACK);
    CPG_Display_SetColor(screen->display, CPG_SILVER);
    CPG_Display_DrawText(screen->display, &bigText);
    CPG_Display_SetColor(screen->display, CPG_WHITE);
    CPG_Display_DrawText(screen->display, &text);

    CPG_Display_Refresh(screen->display);
    SDL_Delay(16);
}

CPG_Screen* CPG_HelpScreen_Init(CPG_Display* display) {
    return CPG_Screen_Init(display, CPG_HelpScreen_Loop);
}
